#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class ExcelFileIO : public AbstractFileIO
    {
    public:
        ~ExcelFileIO();
        ExcelFileIO() = default;
        ExcelFileIO(const std::string_view&);
        ExcelFileIO(const ExcelFileIO&) = delete;
        ExcelFileIO(ExcelFileIO&&) noexcept = default;
        ExcelFileIO& operator = (const ExcelFileIO&) = delete;
        ExcelFileIO& operator = (ExcelFileIO&&) noexcept = default;
        ExcelFileIO(const std::string_view&, const std::string_view&);

    };
}
#pragma once
