#pragma once

#include "pch.h"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
    class BinaryFileIO : public AbstractFileIO
    {
    public:
        ~BinaryFileIO();
        BinaryFileIO() = default;
        BinaryFileIO(const std::string_view&);
        BinaryFileIO(const BinaryFileIO&) = delete;
        BinaryFileIO(BinaryFileIO&&) noexcept = default;
        BinaryFileIO& operator = (const BinaryFileIO&) = delete;
        BinaryFileIO& operator = (BinaryFileIO&&) noexcept = default;
        BinaryFileIO(const std::string_view&, const std::string_view&);


        bool open(const FileMode&);
        bool close(const FileMode&);
        bool is_open(const FileMode&);
        std::vector<std::byte> read();
        bool write(const std::span<const std::byte>&);
        bool append(const std::span<const std::byte>&);

        std::future<bool> open_async(const FileMode&);
        std::future<bool> close_async(const FileMode&);
        std::future<std::vector<std::byte>> read_async();
        std::future<bool> write_async(const std::span<const std::byte>&);
        std::future<bool> append_async(const std::span<const std::byte>&);

    protected:
        std::optional<fast_io::obuf_file> _write_file;
        std::optional<fast_io::obuf_file> _append_file;
        std::optional<fast_io::native_file_loader> _read_file;
    };
}
