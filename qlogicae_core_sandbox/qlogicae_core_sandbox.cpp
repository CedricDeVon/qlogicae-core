#pragma once

#include "pch.h"

int main()
{   
    QLogicaeCore::Application& QLOGICAE_APPLICATION =
        QLogicaeCore::Application::get_instance();

    std::cout << QLogicaeCore::UTILITIES.FULL_APPLICATION_QLOGICAE_PUBLIC_APPLICATION_CONFIGURATIONS_ENVIRONMENT_FILE_PATH;
    std::cout << "Enter to exit\n";

    bool ea;

    std::cin >> ea;

    return 0;
}
