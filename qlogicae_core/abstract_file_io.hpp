#pragma once

#include "pch.h"

#include "globals.hpp"

namespace QLogicaeCore
{
    class AbstractFileIO
    {
    public:
        AbstractFileIO() = default;
        virtual ~AbstractFileIO() = default;
        AbstractFileIO(const std::string_view&);
        AbstractFileIO(const AbstractFileIO&) = delete;
        AbstractFileIO(AbstractFileIO&&) noexcept = default;
        AbstractFileIO& operator = (const AbstractFileIO&) = delete;
        AbstractFileIO& operator = (AbstractFileIO&&) noexcept = default;
        AbstractFileIO(const std::string_view&, const std::string_view&);
        
        std::string get_name() const;
        std::string get_file_path() const;
        void set_file_path(const std::string_view&);

    protected:
        std::string _file_path;
        const std::string _name;
        mutable std::mutex _mutex;
    };
}


