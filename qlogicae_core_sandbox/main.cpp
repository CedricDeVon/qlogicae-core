#include "pch.hpp"

#include "main.hpp"

int main(int argc, char** argv)
{
    try
    {
        for (int i = 0; i < 1000; ++i)
        {
            QLogicaeCore::LOGGER.handle_exception_async(
                "QLogicaeCore::RocksDBDatabase::commit_transaction()",
                "Sample"
            );
        }

        // QLogicaeCore::UTILITIES.BOOST_ASIO_POOL.join();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what() << "\n";
    }

    bool exit_code;
    std::cin >> exit_code;

    return 0;
}

namespace QLogicaeCoreSandbox
{

}
