#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class FileIOs
    {
    public:
        void set_file(std::shared_ptr<AbstractFileIO>);
        template <typename Type> Type& get_file(const std::string&);
        void set_file(const std::vector<std::shared_ptr<AbstractFileIO>>&);

        static FileIOs& instance();

    protected:
        FileIOs() = default;
        virtual ~FileIOs() = default;
        FileIOs(const FileIOs&) = delete;
        FileIOs(FileIOs&&) noexcept = default;
        FileIOs& operator = (const FileIOs&) = delete;
        FileIOs& operator = (FileIOs&&) noexcept = default;

        mutable std::mutex _mutex;
        std::unordered_map<std::string, std::shared_ptr<AbstractFileIO>> _instances;
    };

    template <typename Type> Type& FileIOs::get_file(const std::string& name)
    {
        try
        {
            std::lock_guard lock(_mutex);

            auto it = _instances.find(name);
            if (it == _instances.end())
            {
                return {};
            }

            auto derived_ptr = std::dynamic_pointer_cast<Type>(it->second);
            if (!derived_ptr)
            {
                return {};
            }

            return *derived_ptr;
        }
        catch (...)
        {
            return {};
        }
    }
}
