#pragma once

#include "result.hpp"
#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class FileIOs
    {
    public:
        void set_file(std::shared_ptr<AbstractFileIO>
            abstract_file_io
        );

        template <typename Type> Type& get_file(
            const std::string& file_name
        );

        void set_file(
            const std::vector<std::shared_ptr<AbstractFileIO>>&
                abstract_file_ios
        );

        static FileIOs& get_instance();

        void setup(
            Result<void>& result
        );

        void set_file(
            Result<void>& result,
            std::shared_ptr<AbstractFileIO> abstract_file_io
        );

        template <typename Type>
        void get_file(
            Result<Type&>& result,
            const std::string& file_name
        );

        void set_file(
            Result<void>& result,
            const std::vector<std::shared_ptr<AbstractFileIO>>& abstract_file_ios
        );

        static void get_instance(
            Result<FileIOs*>& result
        );

    protected:
        FileIOs() = default;

        virtual ~FileIOs() = default;

        FileIOs(const FileIOs&) = delete;

        FileIOs(FileIOs&&) noexcept = default;

        FileIOs& operator = (const FileIOs&) = delete;

        FileIOs& operator = (FileIOs&&) noexcept = default;

        mutable std::mutex _mutex;
        std::unordered_map<std::string, std::shared_ptr<AbstractFileIO>>
            _instances;
    };

    template <typename Type> Type& FileIOs::get_file(
        const std::string& name
    )
    {
        try
        {
            std::lock_guard lock(_mutex);

            auto it = _instances.find(name);
            if (it == _instances.end())
            {
                return {};
            }

            auto derived_pointer = std::dynamic_pointer_cast<Type>(it->second);
            if (!derived_pointer)
            {
                return {};
            }

            return *derived_pointer;
        }
        catch (...)
        {
            return {};
        }
    }


    template <typename Type>
    void FileIOs::get_file(
        Result<Type&>& result,
        const std::string& file_name
    )
    {
        std::lock_guard lock(_mutex);

        auto it = _instances.find(file_name);
        if (it == _instances.end())
        {
            result.set_is_failure();
            return;
        }

        auto derived_pointer = std::dynamic_pointer_cast<Type>(
            it->second
        );
        if (!derived_pointer)
        {
            result.set_is_failure();
            return;
        }

        result.set_to_good_status_with_value(*derived_pointer);
    }

    inline static FileIOs& FILE_IOS = FileIOs::get_instance();
}

