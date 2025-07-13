#pragma once

#include "pch.h"

#include "file_uri_io.hpp"
#include "abstract_file_io.hpp" 

namespace QLogicaeCore
{
    FileUriIO::~FileUriIO()
    {
    }

    FileUriIO::FileUriIO(
        const std::string_view& file_path)
        : AbstractFileIO(file_path)
    {
    }

    FileUriIO::FileUriIO(
        const std::string_view& file_path,
        const std::string_view& mimetype)
        : AbstractFileIO(file_path),
        _mimetype(mimetype)
    {
    }

    FileUriIO::FileUriIO(
        const std::string_view& file_path,
        const std::string_view& mimetype,
        const std::string_view& name)
        : AbstractFileIO(name, file_path),
        _mimetype(mimetype)
    {
    }

    std::string FileUriIO::generate_data_uri() const
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty() ||
            !std::filesystem::exists(_file_path) ||
            std::filesystem::is_directory(_file_path))
        {
            throw std::runtime_error(
                "Invalid file path or file does not exist: " +
                _file_path);
        }

        std::ifstream input_file(
            _file_path, std::ios::binary);

        if (!input_file)
        {
            throw std::runtime_error(
                "Failed to open file: " + _file_path);
        }

        std::ostringstream output_buffer;
        output_buffer << input_file.rdbuf();
        const std::string& raw_data = output_buffer.str();

        std::string base64_encoded =
            "AKLOMP_ENCODED(" + raw_data + ")";

        std::ostringstream uri_stream;
        uri_stream << "data:"
            << _mimetype
            << ";base64,"
            << base64_encoded;

        return uri_stream.str();
    }

    std::future<std::string> FileUriIO::generate_data_uri_async() const
    {
        return std::async(
            std::launch::async,
            [this]() -> std::string
            {
                return this->generate_data_uri();
            });
    }

}
