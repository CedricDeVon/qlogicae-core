#pragma once

#include "result.hpp"

namespace QLogicaeCore
{
    class AbstractFileIO
    {
    public:
        AbstractFileIO() = default;

        virtual ~AbstractFileIO() = default;

        AbstractFileIO(
            const std::string& file_path
        );

        AbstractFileIO(
            const AbstractFileIO& abstract_file_io
        ) = delete;

        AbstractFileIO(
            AbstractFileIO&& abstract_file_io
        ) noexcept = default;

        AbstractFileIO& operator = (
            const AbstractFileIO& abstract_file_io
        ) = delete;

        AbstractFileIO& operator = (
            AbstractFileIO&& abstract_file_io
        ) noexcept = default;

        AbstractFileIO(
            const std::string& name,
            const std::string& file_path
        );
        
        std::string get_name() const;

        std::string get_file_path() const;

        std::size_t get_line_count() const;

        void set_file_path(
            const std::string& file_path
        );
        
        void get_name(
            Result<std::string>& result
        ) const;

        void get_file_path(
            Result<std::string>& result
        ) const;

        void get_line_count(
            Result<std::size_t>& result
        ) const;

        void set_file_path(
            Result<bool>& result,
            const std::string& file_path
        );

    protected:
        std::string _file_path;

        std::string _name;

        mutable std::mutex _mutex;
    };
}


