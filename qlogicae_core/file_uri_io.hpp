#pragma once

#include "result.hpp"
#include "utilities.hpp"
#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class FileUriIO :
        public AbstractFileIO
    {
    public:
        ~FileUriIO();

        FileUriIO() = default;

        FileUriIO(const FileUriIO& file_uri_io) = delete;

        FileUriIO(FileUriIO&& file_uri_io) noexcept = default;

        FileUriIO(const std::string& file_path);

        FileUriIO& operator=(const FileUriIO& file_uri_io) = delete;

        FileUriIO& operator=(FileUriIO&& file_uri_io) noexcept = default;

        FileUriIO(
            const std::string& file_path,
            const std::string& mimetype
        );

        FileUriIO(
            const std::string& file_path,
            const std::string& mimetype,
            const std::string& name
        );

        void setup(
            Result<void>& result,
            const std::string& file_path
        );

        void setup(
            Result<void>& result,
            const std::string& file_path,
            const std::string& mimetype
        );

        void setup(
            Result<void>& result,
            const std::string& file_path,
            const std::string& mimetype,
            const std::string& name
        );

        std::string generate_data_uri() const;

        std::future<std::string> generate_data_uri_async() const;

    private:
        std::string _mimetype { UTILITIES.DEFAULT_FILE_URI_IO_MIMETYPE.data()};
    };
}
