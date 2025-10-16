#include "pch.hpp"

#include "file_uri_io.hpp"
#include "abstract_file_io.hpp" 

namespace QLogicaeCore
{
    FileUriIO::~FileUriIO()
    {

    }

    FileUriIO::FileUriIO(
        const std::string& file_path
    ) :
        AbstractFileIO(file_path)
    {

    }

    FileUriIO::FileUriIO(
        const std::string& file_path,
        const std::string& mimetype
    ) :
        AbstractFileIO(file_path),
        _mimetype(mimetype)
    {

    }

    FileUriIO::FileUriIO(
        const std::string& file_path,
        const std::string& mimetype,
        const std::string& name
    ) :
        AbstractFileIO(name, file_path),
        _mimetype(mimetype)
    {

    }

    std::string FileUriIO::generate_data_uri() const
    {
        try
        {
            std::scoped_lock lock(_mutex);

            if (_file_path.empty() ||
                !std::filesystem::exists(_file_path) ||
                std::filesystem::is_directory(_file_path))
            {
                throw std::runtime_error(
                    std::string() +
                    "Exception at FileUriIO::generate_data_uri(): File does not exist"
                );
            }

            std::ifstream input_file(
                _file_path, std::ios::binary);

            if (!input_file)
            {
                return "";
            }

            std::ostringstream output_buffer;
            output_buffer << input_file.rdbuf();
            std::string raw_data = output_buffer.str();

            return std::string() +
                "data:" +
                _mimetype.data() +
                ";base64," +
                "AKLOMP_ENCODED(" +
                raw_data +
                ")";
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() +
                "Exception at FileUriIO::generate_data_uri(): " +
                exception.what()
            );
        }
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

    void FileUriIO::generate_data_uri(
        Result<std::string>& result
    ) const
    {
        std::scoped_lock lock(_mutex);

        if (_file_path.empty() ||
            !std::filesystem::exists(_file_path) ||
            std::filesystem::is_directory(_file_path))
        {
            return result.set_to_bad_status_without_value(
                "File not found"
            );
        }

        std::ifstream input_file(
            _file_path,
            std::ios::binary
        );

        if (!input_file)
        {
            return result.set_to_bad_status_without_value(
                "Parsing failed"
            );
        }

        std::ostringstream output_buffer;
        output_buffer << input_file.rdbuf();
        std::string raw_data = output_buffer.str();

        result.set_to_good_status_with_value(
            std::string() +
            "data:" +
            _mimetype.data() +
            ";base64," +
            "AKLOMP_ENCODED(" +
            raw_data +
            ")"
        );
    }

    void FileUriIO::generate_data_uri_async(
        Result<std::future<std::string>>& result
    ) const
    {
        result.set_to_good_status_with_value(std::async(
            std::launch::async,
            [this]() -> std::string
            {
                Result<std::string> result;

                generate_data_uri(result);

                return result.get_value();
            })
        );
    }

    void FileUriIO::setup(
        Result<void>& result,
        const std::string& file_path
    )
    {
        _file_path = file_path;

        result.set_to_good_status_without_value();
    }

    void FileUriIO::setup(
        Result<void>& result,
        const std::string& file_path,
        const std::string& mimetype
    )
    {
        _file_path = file_path;
        _mimetype = mimetype;

        result.set_to_good_status_without_value();
    }

    void FileUriIO::setup(
        Result<void>& result,
        const std::string& file_path,
        const std::string& mimetype,
        const std::string& name
    )
    {
        _file_path = file_path;
        _mimetype = mimetype;
        _name = name;

        result.set_to_good_status_without_value();
    }
}
