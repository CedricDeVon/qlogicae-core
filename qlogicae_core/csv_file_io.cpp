#pragma once

#include "pch.h"

#include "csv_file_io.hpp"

namespace QLogicaeCore {

    CsvFileIO::~CsvFileIO() = default;

    CsvFileIO::CsvFileIO(const std::string_view& path) :
        AbstractFileIO(path)
    {
        open();
    }

    CsvFileIO::CsvFileIO(
        const std::string_view& path,
        const std::string_view& content) :
        AbstractFileIO(path, content)
    {
        open();
    }

    std::string CsvFileIO::trim(std::string_view str)
    {
        auto start = str.find_first_not_of(" \t\n\r");
        auto end = str.find_last_not_of(" \t\n\r");

        return (start == std::string_view::npos) ? "" :
            std::string(str.substr(start, end - start + 1));
    }

    bool QLogicaeCore::CsvFileIO::clear()
    {
        std::lock_guard<std::recursive_mutex> lock(_mutex);

        if (!_temporary_csv_document_1.has_value())
        {
            return false;
        }

        try
        {
            const size_t row_count =
                _temporary_csv_document_1->GetRowCount();
            for (size_t i = 0; i < row_count; ++i)
            {
                _temporary_csv_document_1->RemoveRow(0); 
            }

            return true;
        }
        catch (...)
        {
            _corrupted = true;

            return false;
        }
    }


    bool CsvFileIO::open()
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty())
        {
            return false;
        }

        try
        {
            fast_io::native_file_loader loader(_file_path);
            std::string_view buffer(loader.cbegin(), loader.cend());

            if (std::any_of(buffer.begin(), buffer.end(), [](char c)
                {
                    return static_cast<unsigned char>(c) < 0x09 ||
                        static_cast<unsigned char>(c) > 0x7F;
                }))
            {
                _corrupted = true;

                return false;
            }

            _temporary_csv_document_1.emplace(
                _file_path,
                _label_params,
                _separator_params
            );

            _corrupted = false;

            return true;
        }
        catch (...)
        {
            _corrupted = true;
            _temporary_csv_document_1.reset();
            return false;
        }
    }

    bool CsvFileIO::close()
    {
        std::scoped_lock lock(_mutex);
        _temporary_csv_document_1.reset();

        return true;
    }

    size_t CsvFileIO::get_row_count()
    {
        std::scoped_lock lock(_mutex);

        return _temporary_csv_document_1->GetRowCount();
    }

    size_t CsvFileIO::get_column_count()
    {
        std::scoped_lock lock(_mutex);

        return _temporary_csv_document_1->GetColumnCount();
    }

    std::vector<std::string> CsvFileIO::get_headers()
    {
        std::scoped_lock lock(_mutex);

        return _temporary_csv_document_1->GetColumnNames();
    }

    std::string CsvFileIO::get_row(const unsigned int& index)
    {
        std::scoped_lock lock(_mutex);

        const auto row =
            _temporary_csv_document_1->GetRow<std::string>(index);
        std::ostringstream oss;
        for (size_t i = 0; i < row.size(); ++i)
        {
            oss << row[i] << (i + 1 < row.size() ? "," : "");
        }

        return oss.str();
    }

    bool CsvFileIO::is_header_found(const std::string_view& header)
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1.has_value())
        {
            return false;
        }

        const auto trimmed = trim(header);
        const auto headers = _temporary_csv_document_1->GetColumnNames();
        return std::any_of(
            headers.begin(), headers.end(), [&](const std::string& h
        )
        {
            return trim(h) == trimmed;
        });
    }

    std::string CsvFileIO::get_column(const std::string_view& name)
    {
        std::scoped_lock lock(_mutex);

        const auto column =
            _temporary_csv_document_1->GetColumn<std::string>(
                std::string(name)
            );
        std::ostringstream oss;
        for (size_t i = 0; i < column.size(); ++i)
            oss << column[i] << (i + 1 < column.size() ? "," : "");
        return oss.str();
    }

    std::string CsvFileIO::get_cell(
        const std::string_view& col,
        const unsigned int& row
    )
    {
        std::scoped_lock lock(_mutex);
        return _temporary_csv_document_1->GetCell<std::string>(
            std::string(col), row
        );
    }

    bool CsvFileIO::save()
    {   
        std::scoped_lock lock(_mutex);

        try
        {
            _temporary_csv_document_1->Save();
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    std::string CsvFileIO::read()
    {
        std::scoped_lock lock(_mutex);
        try
        {
            fast_io::native_file_loader loader(_file_path);

            return std::string(loader.cbegin(), loader.cend());
        }
        catch (...)
        {
            _corrupted = true;
            return "";
        }
    }

    bool CsvFileIO::write(const std::string_view& content)
    {
        try
        {
            fast_io::obuf_file out(_file_path, fast_io::open_mode::out);
            fast_io::io::print(out, content);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool CsvFileIO::append(const std::string_view& content)
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty() || content.empty())
        {
            return false;
        }

        try
        {
            fast_io::obuf_file out(_file_path, fast_io::open_mode::app);
            fast_io::io::print(out, content);

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    void CsvFileIO::set_delimiter(const unsigned char& ch)
    {
        _separator_params.mSeparator = static_cast<char>(ch);
    }

    void CsvFileIO::set_quote_character(const unsigned char& ch)
    {
        _separator_params.mQuoteChar = static_cast<char>(ch);
    }

    void CsvFileIO::set_label_params(
        const unsigned int& col,
        const unsigned int& row)
    {
        _label_params = rapidcsv::LabelParams(
            static_cast<int>(col), static_cast<int>(row));
    }

    bool QLogicaeCore::CsvFileIO::validate_headers(
        const std::vector<std::string>& expected)
    {
        std::lock_guard<std::recursive_mutex> lock(_mutex);

        if (!_temporary_csv_document_1.has_value())
            return false;

        try
        {
            const auto actual = _temporary_csv_document_1->GetColumnNames();
            return actual == expected;  
        }
        catch (...)
        {
            _corrupted = true;
            return false;
        }
    }

    bool CsvFileIO::is_valid_index(
        const unsigned int& row,
        const unsigned int& col)
    {
        std::scoped_lock lock(_mutex);

        return row < _temporary_csv_document_1->GetRowCount() &&
            col < _temporary_csv_document_1->GetColumnCount();
    }

    std::map<std::string, std::string> CsvFileIO::get_row_as_map(
        const unsigned int& index)
    {
        std::scoped_lock lock(_mutex);

        std::map<std::string, std::string> result;
        const auto& headers = _temporary_csv_document_1->GetColumnNames();
        const auto row =
            _temporary_csv_document_1->GetRow<std::string>(index);
        for (size_t i = 0; i < headers.size() && i < row.size(); ++i)
        {
            result[headers[i]] = row[i];
        }
        return result;
    }

    std::vector<std::map<std::string, std::string>> CsvFileIO
        ::get_all_rows_as_map()
    {
        std::scoped_lock lock(_mutex);

        std::vector<std::map<std::string, std::string>> rows;
        const auto& headers = _temporary_csv_document_1->GetColumnNames();
        for (unsigned int i = 0;
            i < _temporary_csv_document_1->GetRowCount();
            ++i)
        {
            const auto row =
                _temporary_csv_document_1->GetRow<std::string>(i);
            std::map<std::string, std::string> m;
            for (size_t j = 0; j < headers.size() && j < row.size(); ++j)
            {
                m[headers[j]] = row[j];
            }
            rows.push_back(std::move(m));
        }

        return rows;
    }

    bool CsvFileIO::is_corrupted()
    {
        std::scoped_lock lock(_mutex);

        return _corrupted;
    }

    std::string CsvFileIO::export_to_json()
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1.has_value())
        {
            return "[]";
        }

        const auto& doc = _temporary_csv_document_1.value();
        const auto& headers = doc.GetColumnNames();
        const size_t row_count = doc.GetRowCount();
        const size_t col_count = headers.size();

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

        writer.StartArray();

        for (size_t i = 0; i < row_count; ++i)
        {
            writer.StartObject();

            const auto row = doc.GetRow<std::string>(i);
            const size_t min_count = std::min(col_count, row.size());

            for (size_t j = 0; j < min_count; ++j)
            {
                writer.Key(headers[j].c_str());
                writer.String(row[j].c_str());
            }

            writer.EndObject();
        }

        writer.EndArray();
        return buffer.GetString();
    }

    bool CsvFileIO::import_from_json(const std::string& json_str)
    {
        std::scoped_lock lock(_mutex);

        rapidjson::Document doc;
        if (doc.Parse(json_str.c_str()).HasParseError() || !doc.IsArray())
        {
            return false;
        }

        if (doc.Empty())
        {
            return false;
        }

        std::ostringstream oss;
        const rapidjson::Value& firstObj = doc[0];
        if (!firstObj.IsObject()) return false;

        for (auto itr = firstObj.MemberBegin();
            itr != firstObj.MemberEnd();
            ++itr)
        {
            oss << itr->name.GetString() << ",";
        }
        oss << "\n";

        for (const auto& row : doc.GetArray())
        {
            if (!row.IsObject())
            {
                return false;
            }
            for (auto itr = firstObj.MemberBegin();
                itr != firstObj.MemberEnd();
                ++itr)
            {
                const char* key = itr->name.GetString();
                if (row.HasMember(key) && row[key].IsString())
                {
                    oss << row[key].GetString();
                }
                oss << ",";
            }
            oss << "\n";
        }

        return write(oss.str()) && open();
    }

    bool CsvFileIO::has_column(const std::string_view& name) const
    {
        try
        {
            _temporary_csv_document_1->GetColumn<std::string>(
                std::string(name)
            );

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool CsvFileIO::has_row(const unsigned int& index) const
    {
        try {
            _temporary_csv_document_1->GetRow<std::string>(index);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool CsvFileIO::remove_row(const unsigned int& index)
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 || index >=
            _temporary_csv_document_1->GetRowCount())
        {
            return false;
        }
        if (!has_row(index))
        {
            return false;
        }

        _temporary_csv_document_1->RemoveRow(index);

        return true;
    }

    bool CsvFileIO::insert_row(
        const unsigned int& index,
        const std::vector<std::string>& row
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 || row.size() !=
            _temporary_csv_document_1->GetColumnCount())
        {
            return false;
        }
        if (index > _temporary_csv_document_1->GetRowCount())
        {
            return false;
        }

        _temporary_csv_document_1->InsertRow(index, row);

        return true;
    }

    bool CsvFileIO::update_row(
        const unsigned int& index,
        const std::vector<std::string>& row
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 ||
            index >= _temporary_csv_document_1->GetRowCount())
        {
            return false;
        }
        if (row.size() != _temporary_csv_document_1->GetColumnCount())
        {
            return false;
        }
        if (!has_row(index))
        {
            return false;
        }

        _temporary_csv_document_1->SetRow(index, row);

        return true;
    }

    bool CsvFileIO::remove_column(const std::string_view& name)
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 || !has_column(name))
        {
            return false;
        }
        _temporary_csv_document_1->RemoveColumn(std::string(name));

        return true;
    }

    bool CsvFileIO::update_column(
        const std::string_view& name,
        const std::vector<std::string>& col
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 ||
            col.size() != _temporary_csv_document_1->GetRowCount())
        {
            return false;
        }
        if (!has_column(name))
        {
            return false;
        }
        _temporary_csv_document_1->SetColumn(std::string(name), col);

        return true;
    }

    bool CsvFileIO::update_cell(
        const std::string_view& name,
        const unsigned int& row, const std::string& val
    )
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 ||
            row >= _temporary_csv_document_1->GetRowCount())
        {
            return false;
        }
        if (!has_column(name))
        {
            return false;
        }
        _temporary_csv_document_1->SetCell<std::string>(
            std::string(name), row, val
        );

        return true;
    }

    bool CsvFileIO::insert_column(
        const unsigned int& index,
        const std::vector<std::string>& values,
        const std::string& name)
    {
        std::scoped_lock lock(_mutex);

        if (!_temporary_csv_document_1 ||
            values.size() != _temporary_csv_document_1->GetRowCount())
        {
            return false;
        }
        if (index > _temporary_csv_document_1->GetColumnCount())
        {
            return false;
        }
        if (has_column(name))
        {
            return false;
        }

        _temporary_csv_document_1->InsertColumn(index, values, name);

        return true;
    }

    std::future<bool> CsvFileIO::append_async(
        const std::string_view& content)
    {
        return std::async(std::launch::async, [this, content]()
        {
            return this->append(content);
        });
    }

    std::future<size_t> CsvFileIO::get_row_count_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->get_row_count();
        });
    }

    std::future<size_t> CsvFileIO::get_column_count_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->get_column_count();
        });
    }

    std::future<std::vector<std::string>> CsvFileIO::get_headers_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->get_headers();
        });
    }

    std::future<std::string> CsvFileIO::get_row_async(
        const unsigned int& r)
    {
        return std::async(std::launch::async, [this, r]()
        {
            return this->get_row(r);
        });
    }

    std::future<bool> CsvFileIO::is_header_found_async(
        const std::string_view& h)
    {
        return std::async(std::launch::async, [this, h]()
        {
            return this->is_header_found(h);
        });
    }

    std::future<std::string> CsvFileIO::get_column_async(
        const std::string_view& n)
    {
        return std::async(std::launch::async, [this, n]()
        {
            return this->get_column(n);
        });
    }

    std::future<std::string> CsvFileIO::get_cell_async(
        const std::string_view& h, const unsigned int& r)
    {
        return std::async(std::launch::async, [this, h, r]()
        {
            return this->get_cell(h, r);
        });
    }

    std::future<bool> CsvFileIO::save_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->save();
        });
    }

    std::future<std::string> CsvFileIO::read_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->read();
        });
    }

    std::future<bool> CsvFileIO::write_async(const std::string_view& d)
    {
        return std::async(std::launch::async, [this, d]()
        {
            return this->write(d);
        });
    }

    std::future<bool> CsvFileIO::remove_row_async(const unsigned int& i)
    {
        return std::async(std::launch::async, [this, i]()
        {
            return this->remove_row(i);
        });
    }

    std::future<bool> CsvFileIO::remove_column_async(const std::string_view& n)
    {
        return std::async(std::launch::async, [this, n]()
        {
            return this->remove_column(n);
        });
    }

    std::future<bool> CsvFileIO::insert_row_async(
        const unsigned int& i, const std::vector<std::string>& r)
    {
        return std::async(std::launch::async, [this, i, r]()
        {
            return this->insert_row(i, r);
        });
    }

    std::future<bool> CsvFileIO::update_row_async(
        const unsigned int& i, const std::vector<std::string>& r)
    {
        return std::async(std::launch::async, [this, i, r]()
        {
            return this->update_row(i, r);
        });
    }

    std::future<bool> CsvFileIO::update_column_async(
        const std::string_view& n, const std::vector<std::string>& c)
    {
        return std::async(std::launch::async, [this, n, c]()
        {
            return this->update_column(n, c);
        });
    }

    std::future<bool> CsvFileIO::update_cell_async(
        const std::string_view& n,
        const unsigned int& r,
        const std::string& v)
    {
        return std::async(std::launch::async, [this, n, r, v]()
        {
            return this->update_cell(n, r, v);
        });
    }

    std::future<bool> CsvFileIO::insert_column_async(
        const unsigned int& i,
        const std::vector<std::string>& v,
        const std::string& n)
    {
        return std::async(std::launch::async, [this, i, v, n]()
        {
            return this->insert_column(i, v, n);
        });
    }

    std::future<bool> QLogicaeCore::CsvFileIO::open_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->open();
        });
    }

    std::future<bool> QLogicaeCore::CsvFileIO::close_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->close();
        });
    }

    std::future<std::map<std::string, std::string>> QLogicaeCore::CsvFileIO
        ::get_row_as_map_async(const unsigned int& index)
    {
        return std::async(std::launch::async, [this, index]()
        {
            return this->get_row_as_map(index);
        });
    }

    std::future<std::vector<std::map<std::string, std::string>>>
        QLogicaeCore::CsvFileIO::get_all_rows_as_map_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->get_all_rows_as_map();
        });
    }

    std::future<std::string> QLogicaeCore::CsvFileIO::export_to_json_async()
    {
        return std::async(std::launch::async, [this]()
        {
            return this->export_to_json();
        });
    }

    std::future<bool> QLogicaeCore::CsvFileIO::import_from_json_async(
        const std::string& json)
    {
        return std::async(std::launch::async, [this, json]()
        {
            return this->import_from_json(json);
        });
    }
}
