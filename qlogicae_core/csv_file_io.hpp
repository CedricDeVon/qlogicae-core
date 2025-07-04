#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class CsvFileIO : public AbstractFileIO
    {
    public:
        ~CsvFileIO();
        CsvFileIO() = default;
        CsvFileIO(const std::string_view&);
        CsvFileIO(const CsvFileIO&) = delete;
        CsvFileIO(CsvFileIO&&) noexcept = default;
        CsvFileIO(const std::string_view&, const std::string_view&);

        bool is_corrupted();
        size_t get_row_count();
        size_t get_column_count();
        std::vector<std::string> get_headers();
        bool has_row(const unsigned int&) const;
        std::string get_row(const unsigned int&);
        void set_delimiter(const unsigned char&);
        bool is_header_found(const std::string_view&);
        void set_quote_character(const unsigned char&);
        bool has_column(const std::string_view&) const;
        std::string get_column(const std::string_view&);
        bool is_valid_index(const unsigned int&, const unsigned int&);
        void set_label_params(const unsigned int&, const unsigned int&);
        std::string get_cell(const std::string_view&, const unsigned int&);
        std::vector<std::map<std::string, std::string>> get_all_rows_as_map();
        std::map<std::string, std::string> get_row_as_map(const unsigned int&);

        bool save();
        bool open();
        bool close();
        bool clear();
        std::string read();
        std::string export_to_json(); 
        bool write(const std::string_view&);
        bool append(const std::string_view&);
        bool remove_row(const unsigned int&);
        static std::string trim(std::string_view);
        bool import_from_json(const std::string&);
        bool remove_column(const std::string_view&);
        bool validate_headers(const std::vector<std::string>&);
        bool insert_row(const unsigned int&, const std::vector<std::string>&);
        bool update_row(const unsigned int&, const std::vector<std::string>&);
        bool update_column(const std::string_view&, const std::vector<std::string>&);
        bool update_cell(const std::string_view&, const unsigned int&, const std::string&);
        bool insert_column(const unsigned int&, const std::vector<std::string>&, const std::string&);

        std::future<size_t> get_row_count_async();
        std::future<size_t> get_column_count_async();
        std::future<std::vector<std::string>> get_headers_async();
        std::future<std::string> get_row_async(const unsigned int&);
        std::future<bool> is_header_found_async(const std::string_view&);
        std::future<std::string> get_column_async(const std::string_view&);
        std::future<std::string> get_cell_async(const std::string_view&, const unsigned int&);
        std::future<std::vector<std::map<std::string, std::string>>> get_all_rows_as_map_async();
        std::future<std::map<std::string, std::string>> get_row_as_map_async(const unsigned int&);

        std::future<bool> open_async();
        std::future<bool> save_async();
        std::future<bool> close_async();
        std::future<std::string> read_async();
        std::future<std::string> export_to_json_async();
        std::future<bool> write_async(const std::string_view&);
        std::future<bool> append_async(const std::string_view&);
        std::future<bool> remove_row_async(const unsigned int&);
        std::future<bool> import_from_json_async(const std::string&);
        std::future<bool> remove_column_async(const std::string_view&);
        std::future<bool> insert_row_async(const unsigned int&, const std::vector<std::string>&);
        std::future<bool> update_row_async(const unsigned int&, const std::vector<std::string>&);
        std::future<bool> update_column_async(const std::string_view&, const std::vector<std::string>&);
        std::future<bool> update_cell_async(const std::string_view&, const unsigned int&, const std::string&);
        std::future<bool> insert_column_async(const unsigned int&, const std::vector<std::string>&, const std::string&);

    protected:
        bool _corrupted = false;
        std::recursive_mutex _mutex;
        rapidcsv::LabelParams _label_params{ 0, -1 };
        rapidcsv::SeparatorParams _separator_params{ ',' };
        std::optional<rapidcsv::Document> _temporary_csv_document_1;
    };
}
