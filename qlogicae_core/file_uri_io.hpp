#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class FileUriIO : public AbstractFileIO
    {
    public:
        ~FileUriIO();
        FileUriIO() = default;
        FileUriIO(const FileUriIO&) = delete;
        FileUriIO(FileUriIO&&) noexcept = default;
        FileUriIO(const std::string_view& file_path);
        FileUriIO& operator=(const FileUriIO&) = delete;
        FileUriIO& operator=(FileUriIO&&) noexcept = default;
        FileUriIO(const std::string_view& file_path,
            const std::string_view& mimetype);
        FileUriIO(const std::string_view& file_path,
            const std::string_view& mimetype,
            const std::string_view& name);

        std::string generate_data_uri() const;
        std::future<std::string> generate_data_uri_async() const;

    private:
        std::string_view _mimetype { "application/octet-stream" };
    };
}
