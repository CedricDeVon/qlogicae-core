#pragma once

#include "qlogicae_cpp_core_benchmark/includes/application.hpp"

#include "qlogicae_cpp_core/includes/all.hpp"

#include <nanobench.h>

#include <random>
#include <iostream>
#include <windows.h>

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

namespace QLogicaeCppCoreBenchmark
{

}
