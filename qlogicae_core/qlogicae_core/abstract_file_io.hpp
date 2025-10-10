#pragma once

namespace QLogicaeCore
{
    class AbstractFileIO
    {
    public:

        AbstractFileIO() = default;

        virtual ~AbstractFileIO() = default;

        AbstractFileIO(
            const std::string_view& file_path
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
            const std::string_view& name,
            const std::string_view& file_path
        );
        
        std::string get_name() const;

        std::string get_file_path() const;

        std::size_t get_line_count() const;

        void set_file_path(
            const std::string_view& file_path
        );

    protected:
        std::string _file_path;

        const std::string _name;

        mutable std::mutex _mutex;
    };
}


