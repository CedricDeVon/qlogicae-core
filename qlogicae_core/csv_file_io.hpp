#pragma once

#include "abstract_file_io.hpp"

#include <rapidcsv.h>

#include <string>
#include <vector>
#include <optional>

namespace QLogicaeCore
{
    class CsvFileIO :
        public AbstractFileIO
    {
    public:
        ~CsvFileIO();

        CsvFileIO() = default;

        CsvFileIO(
            const std::string_view& file_path
        );

        CsvFileIO(
            const CsvFileIO& csv_file_io
        ) = delete;

        CsvFileIO(
            CsvFileIO&& csv_file_io
        ) noexcept = default;

        CsvFileIO(
            const std::string_view& name,
            const std::string_view& file_path
        );

        bool is_corrupted();

        size_t get_row_count();

        size_t get_column_count();

        std::vector<std::string> get_headers();

        bool has_row(
            const unsigned int& row_index
        ) const;

        std::string get_row(
            const unsigned int& row_index
        );

        void set_delimiter(
            const unsigned char& value
        );

        bool is_header_found(
            const std::string_view& name
        );

        void set_quote_character(
            const unsigned char& value
        );

        bool has_column(
            const std::string_view& name
        ) const;

        std::string get_column(
            const std::string_view& name
        );

        bool is_valid_index(
            const unsigned int& column_index,
            const unsigned int& row_index
        );

        void set_label_params(
            const unsigned int& column_index,
            const unsigned int& row_index
        );

        std::string get_cell(
            const std::string_view&,
            const unsigned int& row_index
        );

        std::map<std::string, std::string> get_row_as_map(
            const unsigned int& row_index
        );

        std::vector<std::map<std::string, std::string>>
            get_all_rows_as_map();

        bool save();

        bool open();

        bool close();

        bool clear();

        std::string read();

        std::string export_to_json(); 

        bool write(const std::string_view& text);

        bool write(
            const std::vector<std::string>& headers,
            const std::vector<std::vector<std::string>>& rows
        ); // TODO

        bool append(
            const std::string_view& text
        );

        bool remove_row(
            const unsigned int& name
        );

        static std::string trim(
            std::string_view text
        );

        bool import_from_json(
            const std::string& file_path
        );

        bool remove_column(
            const std::string_view& name
        );

        bool validate_headers(
            const std::vector<std::string>& headers
        );

        bool insert_row(
            const unsigned int& index,
            const std::vector<std::string>& values
        );

        bool update_row(
            const unsigned int& index,
            const std::vector<std::string>& values
        );

        bool update_column(
            const std::string_view& header,
            const std::vector<std::string>& values
        );

        bool update_cell(
            const std::string_view& header,
            const unsigned int& row_index,
            const std::string& value
        );

        bool insert_column(
            const unsigned int& row_index,
            const std::vector<std::string>&,
            const std::string& values
        );

        std::future<size_t> get_row_count_async();

        std::future<size_t> get_column_count_async();

        std::future<std::vector<std::string>> get_headers_async();

        std::future<std::string> get_row_async(
            const unsigned int& index
        );

        std::future<bool> is_header_found_async(
            const std::string_view& name
        );

        std::future<std::string> get_column_async(
            const std::string_view& name
        );

        std::future<std::string> get_cell_async(
            const std::string_view& column_name,
            const unsigned int& row_index
        );

        std::future<std::vector<std::map<std::string, std::string>>>
            get_all_rows_as_map_async();

        std::future<std::map<std::string, std::string>> get_row_as_map_async(
            const unsigned int& index
        );

        std::future<bool> open_async();

        std::future<bool> save_async();

        std::future<bool> close_async();

        std::future<std::string> read_async();

        std::future<std::string> export_to_json_async();

        std::future<bool> write_async(
            const std::string_view& text
        );

        std::future<bool> append_async(
            const std::string_view& text
        );

        std::future<bool> remove_row_async(
            const unsigned int& index
        );

        std::future<bool> import_from_json_async(
            const std::string& file_path
        );

        std::future<bool> remove_column_async(
            const std::string_view& name
        );

        std::future<bool> insert_row_async(
            const unsigned int& index,
            const std::vector<std::string>& values
        );

        std::future<bool> update_row_async(
            const unsigned int& index,
            const std::vector<std::string>& values
        );

        std::future<bool> update_column_async(
            const std::string_view& name,
            const std::vector<std::string>& values
        );

        std::future<bool> update_cell_async(
            const std::string_view& column_name,
            const unsigned int& row_index,
            const std::string& value
        );

        std::future<bool> insert_column_async(
            const unsigned int& row_index,
            const std::vector<
                std::string>&,
            const std::string& values
        );

    protected:
        bool _corrupted = false;
        std::recursive_mutex _mutex;
        rapidcsv::LabelParams _label_params{ 0, -1 };
        rapidcsv::SeparatorParams _separator_params{ ',' };
        std::optional<rapidcsv::Document> _temporary_csv_document_1;
    };
}
