#pragma once

#include "result.hpp"
#include "xml_file_io.hpp"
#include "csv_file_io.hpp"
#include "file_uri_io.hpp"
#include "text_file_io.hpp"
#include "json_file_io.hpp"
#include "toml_file_io.hpp"
#include "binary_file_io.hpp"
#include "abstract_application.hpp"

namespace QLogicaeCore
{
    class ApplicationFileIO :
        public AbstractApplication
    {
    public:                
        bool setup();

        void setup(
            Result<void>& result
        );

        std::future<bool> setup_async();

        void setup_async(
            Result<std::future<void>>& result
        );

        static ApplicationFileIO& get_instance();

        static void get_instance(
            Result<ApplicationFileIO*>& result
        );

    protected:
        ApplicationFileIO();

        ~ApplicationFileIO();

        ApplicationFileIO(
            const ApplicationFileIO& instance
        ) = default;

        ApplicationFileIO(
            ApplicationFileIO&& instance
        ) noexcept = delete;

        ApplicationFileIO& operator = (
            ApplicationFileIO&& instance
        ) = default;

        ApplicationFileIO& operator = (
            const ApplicationFileIO& instance
        ) = delete;
    };

    inline static ApplicationFileIO& QLOGICAE_APPLICATION_FILE_IO =
        ApplicationFileIO::get_instance();
}

