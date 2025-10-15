#include "pch.hpp"

#include "csv_file_io.hpp"

namespace QLogicaeCore
{
    CsvFileIO::~CsvFileIO() = default;

    CsvFileIO::CsvFileIO(const std::string& path) :
        AbstractFileIO(path)
    {
        
    }

    CsvFileIO::CsvFileIO(
        const std::string& path,
        const std::string& content) :
            AbstractFileIO(path, content)
    {

    }

    std::string CsvFileIO::trim(std::string value)
    {
        try
        {
            auto start = value.find_first_not_of(" \t\n\r");
            auto end = value.find_last_not_of(" \t\n\r");

            return (start == std::string::npos) ? "" :
                std::string(value.substr(start, end - start + 1));
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::open(): " + exception.what());
        }
    }

    bool QLogicaeCore::CsvFileIO::clear()
    {
        try
        {
            std::lock_guard<std::recursive_mutex> lock(_mutex);

            if (!_temporary_csv_document_1.has_value())
            {
                return false;
            }

            const size_t row_count =
                _temporary_csv_document_1->GetRowCount();
            for (size_t index = 0; index < row_count; ++index)
            {
                _temporary_csv_document_1->RemoveRow(0);
            }

            return true;
        }
        catch (const std::exception& exception)
        {
            _corrupted = true;

            throw std::runtime_error(std::string() + "Exception at CsvFileIO::close(): " + exception.what());
        }
    }

    bool CsvFileIO::open()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (_file_path.empty())
            {
                return false;
            }

            fast_io::native_file_loader loader(_file_path);
            std::string buffer(loader.cbegin(), loader.cend());

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
        catch (const std::exception& exception)
        {
            _corrupted = true;
            _temporary_csv_document_1.reset();

            throw std::runtime_error(std::string() + "Exception at CsvFileIO::open(): " + exception.what());
        }
    }

    bool CsvFileIO::close()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            _temporary_csv_document_1.reset();

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::close(): " + exception.what());
        }
    }

    size_t CsvFileIO::get_row_count()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return 0;
            }

            return _temporary_csv_document_1->GetRowCount();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_row_count(): " + exception.what());
        }
    }

    size_t CsvFileIO::get_column_count()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return 0;
            }

            return _temporary_csv_document_1->GetColumnCount();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_column_count(): " + exception.what());
        }
    }

    std::vector<std::string> CsvFileIO::get_headers()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return {};
            }

            return _temporary_csv_document_1->GetColumnNames();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_headers(): " + exception.what());
        }
    }

    std::string CsvFileIO::get_row(const unsigned int& index)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return "";
            }

            const auto row =
                _temporary_csv_document_1->GetRow<std::string>(index);
            std::string text = "";
            size_t index, row_size = row.size();
            for (index = 0; index < row_size; ++index)
            {
                text += absl::StrCat(row[index]) + (index + 1 < row_size ? "," : "");
            }

            return text;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_row(): " + exception.what());
        }
    }

    bool CsvFileIO::is_header_found(const std::string& header)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1.has_value())
            {
                return false;
            }

            const auto trimmed = trim(header);
            const auto headers = _temporary_csv_document_1->GetColumnNames();
            return std::any_of(
                headers.begin(), headers.end(), [&](const std::string& heading
                    )
                {
                    return trim(heading) == trimmed;
                });
        }
        catch (...)
        {
            return false;
        }
    }

    std::string CsvFileIO::get_column(const std::string& name)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return "";
            }

            const auto column =
                _temporary_csv_document_1->GetColumn<std::string>(
                    std::string(name)
                );
            std::string text = "";
            size_t index, row_size = column.size();
            for (index = 0; index < row_size; ++index)
            {
                text += absl::StrCat(column[index]) + (index + 1 < row_size ? "," : "");
            }

            return text;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_column(): " + exception.what());
        }
    }

    std::string CsvFileIO::get_cell(
        const std::string& header_name,
        const unsigned int& row_index
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return "";
            }

            return _temporary_csv_document_1->GetCell<std::string>(
                std::string(header_name), row_index
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_cell(): " + exception.what());
        }
    }

    bool CsvFileIO::save()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1)
            {
                return false;
            }

            _temporary_csv_document_1->Save();

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::save(): " + exception.what());
        }
    }

    std::string CsvFileIO::read()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            fast_io::native_file_loader loader(_file_path);

            return std::string(loader.cbegin(), loader.cend());
        }
        catch (const std::exception& exception)
        {
            _corrupted = true;

            throw std::runtime_error(std::string() + "Exception at CsvFileIO::read(): " + exception.what());
        }
    }

    bool CsvFileIO::write(const std::string& content)
    {
        try
        {
            fast_io::obuf_file out(_file_path, fast_io::open_mode::out);
            fast_io::io::print(out, content);

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::write(): " + exception.what());
        }
    }

    bool CsvFileIO::write(
        const std::vector<std::string>& headers,
        const std::vector<std::vector<std::string>>& rows)
    {
        try
        {
            fast_io::obuf_file out(_file_path, fast_io::open_mode::out);

            std::string content;
            size_t index, size = headers.size();
            for (index = 0; index < size; ++index)
            {
                content += headers[index];
                if (index != size - 1)
                {
                    content += ",";
                }
            }
            content += "\n";

            for (const auto& row : rows)
            {
                size = row.size();
                for (index = 0; index < size; ++index)
                {
                    content += row[index];
                    if (index != size - 1)
                    {
                        content += ",";
                    }
                }
                content += "\n";
            }
            fast_io::io::print(out, content);

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::write(): " + exception.what());
        }
    }

    bool CsvFileIO::append(const std::string& content)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (_file_path.empty() || content.empty())
            {
                return false;
            }

            fast_io::obuf_file out(_file_path, fast_io::open_mode::app);
            fast_io::io::print(out, content);

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::append(): " + exception.what());
        }
    }

    void CsvFileIO::set_delimiter(const unsigned char& character)
    {
        try
        {
            _separator_params.mSeparator = static_cast<char>(character);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::set_delimiter(): " + exception.what());
        }
    }

    void CsvFileIO::set_quote_character(const unsigned char& character)
    {
        try
        {
            _separator_params.mQuoteChar = static_cast<char>(character);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::set_quote_character(): " + exception.what());
        }
    }

    void CsvFileIO::set_label_params(
        const unsigned int& column,
        const unsigned int& row)
    {
        try
        {
            _label_params = rapidcsv::LabelParams(
                static_cast<int>(column), static_cast<int>(row));
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::set_label_params(): " + exception.what());
        }
    }

    bool QLogicaeCore::CsvFileIO::validate_headers(
        const std::vector<std::string>& expected)
    {
        try
        {
            std::lock_guard<std::recursive_mutex> lock(_mutex);

            if (!_temporary_csv_document_1.has_value())
            {
                return false;
            }

            return _temporary_csv_document_1->GetColumnNames() == expected;
        }
        catch (const std::exception& exception)
        {
            _corrupted = true;

            throw std::runtime_error(std::string() + "Exception at CsvFileIO::validate_headers(): " + exception.what());
        }
    }

    bool CsvFileIO::is_valid_index(
        const unsigned int& row,
        const unsigned int& column)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1.has_value())
            {
                return false;
            }

            return row < _temporary_csv_document_1->GetRowCount() &&
                column < _temporary_csv_document_1->GetColumnCount();
        }
        catch (...)
        {
            return false;
        }
    }

    std::map<std::string, std::string> CsvFileIO::get_row_as_map(
        const unsigned int& index)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1.has_value())
            {
                return {};
            }

            std::map<std::string, std::string> result;
            const auto& headers = _temporary_csv_document_1->GetColumnNames();
            const auto row =
                _temporary_csv_document_1->GetRow<std::string>(index);
            size_t index, headers_size = headers.size(), row_size = row.size();
            for (index = 0; index < headers_size && index < row_size; ++index)
            {
                result[headers[index]] = row[index];
            }
            return result;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_row_as_map(): " + exception.what());
        }
    }

    std::vector<std::map<std::string, std::string>> CsvFileIO
        ::get_all_rows_as_map()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1.has_value())
            {
                return {};
            }

            std::vector<std::map<std::string, std::string>> rows;
            const auto& headers = _temporary_csv_document_1->GetColumnNames();
            size_t row_index,
                column_index,
                row_size = _temporary_csv_document_1->GetRowCount(),
                headers_size = headers.size(),
                column_size;
            for (row_index = 0;
                row_index < row_size;
                ++row_index)
            {
                const auto row =
                    _temporary_csv_document_1->GetRow<std::string>(row_index);
                column_size = row.size();
                std::map<std::string, std::string> values;
                for (column_index = 0;
                    column_index < headers_size && column_index < column_size;
                    ++column_index)
                {
                    values[headers[column_index]] = row[column_index];
                }
                rows.push_back(std::move(values));
            }

            return rows;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::get_all_rows_as_map(): " + exception.what());
        }
    }

    bool CsvFileIO::is_corrupted()
    {
        try
        {
            std::scoped_lock lock(_mutex);

            return _corrupted;
        }
        catch (...)
        {
            return false;
        }
    }

    std::string CsvFileIO::export_to_json()
    {
        try
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

            size_t row_index, column_index, min_count;
            for (row_index = 0; row_index < row_count; ++row_index)
            {
                writer.StartObject();

                const auto row = doc.GetRow<std::string>(row_index);
                min_count = std::min(col_count, row.size());
                for (column_index = 0; column_index < min_count; ++column_index)
                {
                    writer.Key(headers[column_index].c_str());
                    writer.String(row[column_index].c_str());
                }

                writer.EndObject();
            }
            writer.EndArray();

            return buffer.GetString();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::export_to_json(): " + exception.what());
        }
    }

    bool CsvFileIO::import_from_json(const std::string& json_string)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            rapidjson::Document document;
            if (document.Parse(json_string.c_str()).HasParseError() || !document.IsArray())
            {
                return false;
            }

            if (document.Empty())
            {
                return false;
            }

            std::string content;
            const rapidjson::Value& firstObj = document[0];
            if (!firstObj.IsObject())
            {
                return false;
            }

            for (auto iterable = firstObj.MemberBegin();
                iterable != firstObj.MemberEnd();
                ++iterable)
            {
                content += absl::StrCat(iterable->name.GetString(), ",");
            }
            content += "\n";

            for (const auto& row : document.GetArray())
            {
                if (!row.IsObject())
                {
                    return false;
                }
                for (auto iterable = firstObj.MemberBegin();
                    iterable != firstObj.MemberEnd();
                    ++iterable)
                {
                    const char* key = iterable->name.GetString();
                    if (row.HasMember(key) && row[key].IsString())
                    {
                        content += absl::StrCat(row[key].GetString());
                    }
                    content += ",";
                }
                content += "\n";
            }

            return write(content) && open();
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::import_from_json(): " + exception.what());
        }
    }

    bool CsvFileIO::has_column(const std::string& name) const
    {
        try
        {
            if (!_temporary_csv_document_1)
            {
                return false;
            }

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
        try
        {
            if (!_temporary_csv_document_1.has_value())
            {
                return false;
            }

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
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::remove_row(): " + exception.what());
        }
    }

    bool CsvFileIO::insert_row(
        const unsigned int& index,
        const std::vector<std::string>& row
    )
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::insert_row(): " + exception.what());
        }
    }

    bool CsvFileIO::update_row(
        const unsigned int& index,
        const std::vector<std::string>& row
    )
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::update_row(): " + exception.what());
        }
    }

    bool CsvFileIO::remove_column(const std::string& name)
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1 || !has_column(name))
            {
                return false;
            }
            _temporary_csv_document_1->RemoveColumn(std::string(name));

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::remove_column(): " + exception.what());
        }
    }

    bool CsvFileIO::update_column(
        const std::string& name,
        const std::vector<std::string>& column
    )
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (!_temporary_csv_document_1 ||
                column.size() != _temporary_csv_document_1->GetRowCount())
            {
                return false;
            }
            if (!has_column(name))
            {
                return false;
            }
            _temporary_csv_document_1->SetColumn(std::string(name), column);

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::update_column(): " + exception.what());
        }
    }

    bool CsvFileIO::update_cell(
        const std::string& name,
        const unsigned int& row, const std::string& value
    )
    {
        try
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
                std::string(name), row, value
            );

            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::update_cell(): " + exception.what());
        }
    }

    bool CsvFileIO::insert_column(
        const unsigned int& index,
        const std::vector<std::string>& values,
        const std::string& name)
    {
        try
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
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at CsvFileIO::insert_column(): " + exception.what());
        }
    }

    std::future<bool> CsvFileIO::append_async(
        const std::string& content)
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
        const unsigned int& row)
    {
        return std::async(std::launch::async, [this, row]()
        {
            return this->get_row(row);
        });
    }

    std::future<bool> CsvFileIO::is_header_found_async(
        const std::string& header)
    {
        return std::async(std::launch::async, [this, header]()
        {
            return this->is_header_found(header);
        });
    }

    std::future<std::string> CsvFileIO::get_column_async(
        const std::string& header)
    {
        return std::async(std::launch::async, [this, header]()
        {
            return this->get_column(header);
        });
    }

    std::future<std::string> CsvFileIO::get_cell_async(
        const std::string& header, const unsigned int& row)
    {
        return std::async(std::launch::async, [this, header, row]()
        {
            return this->get_cell(header, row);
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

    std::future<bool> CsvFileIO::write_async(const std::string& content)
    {
        return std::async(std::launch::async, [this, content]()
        {
            return this->write(content);
        });
    }

    std::future<bool> CsvFileIO::remove_row_async(const unsigned int& index)
    {
        return std::async(std::launch::async, [this, index]()
        {
            return this->remove_row(index);
        });
    }

    std::future<bool> CsvFileIO::remove_column_async(const std::string& header)
    {
        return std::async(std::launch::async, [this, header]()
        {
            return this->remove_column(header);
        });
    }

    std::future<bool> CsvFileIO::insert_row_async(
        const unsigned int& index, const std::vector<std::string>& row)
    {
        return std::async(std::launch::async, [this, index, row]()
        {
            return this->insert_row(index, row);
        });
    }

    std::future<bool> CsvFileIO::update_row_async(
        const unsigned int& index, const std::vector<std::string>& row)
    {
        return std::async(std::launch::async, [this, index, row]()
        {
            return this->update_row(index, row);
        });
    }

    std::future<bool> CsvFileIO::update_column_async(
        const std::string& row, const std::vector<std::string>& column)
    {
        return std::async(std::launch::async, [this, row, column]()
        {
            return this->update_column(row, column);
        });
    }

    std::future<bool> CsvFileIO::update_cell_async(
        const std::string& column,
        const unsigned int& row_index,
        const std::string& value)
    {
        return std::async(std::launch::async, [this, column, row_index, value]()
        {
            return this->update_cell(column, row_index, value);
        });
    }

    std::future<bool> CsvFileIO::insert_column_async(
        const unsigned int& index,
        const std::vector<std::string>& values,
        const std::string& column)
    {
        return std::async(std::launch::async, [this, index, values, column]()
        {
            return this->insert_column(index, values, column);
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

