#pragma once

#include "qlogicae_cpp_core_sandbox/includes/application.hpp"

#include "qlogicae_cpp_core/includes/all.hpp"

int main(int, char**);

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int
)
{
    return main(__argc, __argv);
}

namespace QLogicaeCppCoreSandbox
{

}
