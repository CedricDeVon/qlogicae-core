#include "pch.hpp"

#include "main.hpp"

int main(int argc, char** argv)
{		
	QLogicaeCppCore::Utilities* a;
	QLogicaeCppCore::Result<QLogicaeCppCore::Utilities*> r;

	QLogicaeCppCore::INSTANCE_MANAGER.get_instance(r);
	r.get_value(a);

	std::cout << QLogicaeCppCore::FUNCTION_WRAPPER.call_safely<int>(a, &QLogicaeCppCore::Utilities::sum, 1, 2) << "\n";

	std::cout << &QLogicaeCppCore::InstanceManager::get_instance<QLogicaeCppCore::InstanceManager>() << "\n";
	std::cout << &QLogicaeCppCore::InstanceManager::get_instance<QLogicaeCppCore::InstanceManager>() << "\n";
	std::cout << &QLogicaeCppCore::InstanceManager::get_instance<QLogicaeCppCore::InstanceManager>() << "\n";
	std::cout << &QLogicaeCppCore::InstanceManager::get_instance<QLogicaeCppCore::InstanceManager>() << "\n";
	std::cout << &QLogicaeCppCore::InstanceManager::get_instance<QLogicaeCppCore::InstanceManager>() << "\n";
	std::cout << &QLogicaeCppCore::InstanceManager::get_instance<QLogicaeCppCore::InstanceManager>() << "\n";

	bool exit_code;
	std::cin >> exit_code;

    return 0;
}

namespace QLogicaeCppCoreSandbox
{

}
