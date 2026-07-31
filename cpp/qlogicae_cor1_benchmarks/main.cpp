#include "pch.hpp"

// #include "main.hpp"
// #include "qlogicae_cpp_core/includes/singleton_manager.hpp"
// #include "qlogicae_cpp_core/includes/runtime_benchmarker.hpp"

int main(int argc, char** argv)
{
	// MapVsConstEnumAndStringReturn::execute();

	return 0;
}

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_BENCHMARKS_NAMESPACE_NAME
{

}

/*

namespace
	MapVsConstEnumAndStringReturn
{

	Conclusion:
	- use either 'switch-case' or 'if-then', return constants

	| relative |               ns/op |                op/s |    err% |     total | benchmark
	|---------:|--------------------:|--------------------:|--------:|----------:|:----------
	|   100.0% |                4.82 |      207,577,732.44 |    0.3% |      5.85 | `MapVsConstEnumAndStringReturn__from_enum_to_string_via_const__1`
	|   100.3% |                4.80 |      208,122,565.54 |    0.1% |      5.82 | `MapVsConstEnumAndStringReturn__from_string_to_enum_via_const__1`
	|    85.7% |                5.62 |      177,979,595.17 |    0.5% |      6.82 | `MapVsConstEnumAndStringReturn__from_enum_to_string_via_map__1`
	|    23.5% |               20.47 |       48,841,032.15 |    0.1% |     24.88 | `MapVsConstEnumAndStringReturn__from_string_to_enum_via_map__1`

	|   100.0% |            4,804.18 |          208,152.27 |    0.1% |      5.82 | `MapVsConstEnumAndStringReturn__from_enum_to_string_via_const__1000`
	|   100.0% |            4,804.07 |          208,156.94 |    0.1% |      5.81 | `MapVsConstEnumAndStringReturn__from_string_to_enum_via_const__1000`
	|    84.4% |            5,692.03 |          175,684.33 |    0.3% |      6.86 | `MapVsConstEnumAndStringReturn__from_enum_to_string_via_map__1000`
	|    23.5% |           20,454.87 |           48,888.11 |    0.1% |     24.76 | `MapVsConstEnumAndStringReturn__from_string_to_enum_via_map__1000`

	|   100.0% |      479,727,800.00 |                2.08 |    0.1% |      5.28 | `MapVsConstEnumAndStringReturn__from_enum_to_string_via_const__100000000`
	|   100.1% |      479,363,600.00 |                2.09 |    0.0% |      5.27 | `MapVsConstEnumAndStringReturn__from_string_to_enum_via_const__100000000`
	|    83.0% |      578,044,500.00 |                1.73 |    1.2% |      6.33 | `MapVsConstEnumAndStringReturn__from_enum_to_string_via_map__100000000`
	|    23.4% |    2,046,642,900.00 |                0.49 |    0.2% |     22.66 | `MapVsConstEnumAndStringReturn__from_string_to_enum_via_map__100000000`

	About
	- Timestamp Created: 7:44 AM, February 9, 2026

	enum class EnumSubject1 :
		uint8_t
	{
		TYPE_1,

		TYPE_2,

		TYPE_3,

		TYPE_4,

		TYPE_5,

		NONE
	};

	class ClassSubject1
	{
	public:
		std::unordered_map<std::string, EnumSubject1>
			string_enum_collection =
				{
					{ "TYPE_1", EnumSubject1::TYPE_1 },
					{ "TYPE_5", EnumSubject1::TYPE_5 },
					{ "NONE", EnumSubject1::NONE }
				};

		std::unordered_map<EnumSubject1, std::string>
			enum_string_collection =
				{
					{ EnumSubject1::TYPE_1, "TYPE_1" },
					{ EnumSubject1::TYPE_5, "TYPE_5" },
					{ EnumSubject1::NONE, "NONE" }
				};

		static ClassSubject1
			singleton;

		std::string
			from_enum_to_string_via_map(
				const EnumSubject1&
					value
			)
		{
			return
				enum_string_collection[value];
		}

		EnumSubject1
			from_string_to_enum_via_map(
				const std::string&
					value
			)
		{
			return
				string_enum_collection[value];
		}

		std::string
			from_enum_to_string_via_const(
				const EnumSubject1&
					value
			)
		{
			switch (value)
			{
				case (EnumSubject1::TYPE_1):
				{
					return
						"TYPE_1";
				}
				case (EnumSubject1::TYPE_2):
				{
					return
						"TYPE_2";
				}
				case (EnumSubject1::TYPE_3):
				{
					return
						"TYPE_3";
				}
				case (EnumSubject1::TYPE_4):
				{
					return
						"TYPE_4";
				}
				case (EnumSubject1::TYPE_5):
				{
					return
						"TYPE_5";
				}
				default:
				{
					return
						"NONE";
				}
			};
		}

		EnumSubject1
			from_string_to_enum_via_const(
				const std::string&
					value
			)
		{
			if (value == "TYPE_1")
			{
				return
					EnumSubject1::TYPE_1;
			}
			else if (value == "TYPE_2")
			{
				return
					EnumSubject1::TYPE_2;
			}
			else if (value == "TYPE_3")
			{
				return
					EnumSubject1::TYPE_3;
			}
			else if (value == "TYPE_4")
			{
				return
					EnumSubject1::TYPE_4;
			}
			else if (value == "TYPE_5")
			{
				return
					EnumSubject1::TYPE_5;
			}
			else
			{
				return
					EnumSubject1::NONE;
			}
		}
	};

	ClassSubject1
		ClassSubject1
			::singleton;

	void execute()
	{
		QLOGICAE_COR_V1__BASE__HPP_CPP__COR_NAMESPACE_NAME::RuntimeBenchmarkerTestSuite test_suite
		{
			.name = "MapVsConstEnumAndStringReturn",
			.epoch_iteration_pairs =
			{
				{
					.epochs = 100000000,
					.iterations = 1
				},
				{
					.epochs = 100000,
					.iterations = 1000
				},
				{
					.epochs = 1,
					.iterations = 100000000
				},
			},
			.test_cases =
			{
				{
					.name = "from_enum_to_string_via_const",
					.callback = []() { ClassSubject1::singleton.from_enum_to_string_via_const(EnumSubject1::TYPE_5); }
				},
				{
					.name = "from_string_to_enum_via_const",
					.callback = []() { ClassSubject1::singleton.from_string_to_enum_via_const("TYPE_5"); }
				},
				{
					.name = "from_enum_to_string_via_map",
					.callback = []() { ClassSubject1::singleton.from_enum_to_string_via_map(EnumSubject1::TYPE_5); }
				},
				{
					.name = "from_string_to_enum_via_map",
					.callback = []() { ClassSubject1::singleton.from_string_to_enum_via_map("TYPE_5"); }
				},
			}
		};

		QLOGICAE_COR_V1__BASE__HPP_CPP__COR_NAMESPACE_NAME::RuntimeBenchmarker::singleton.execute(
			test_suite
		);

		bool exit_code;
		std::cin >> exit_code;
	}
}


ConfigurationsManager::singleton.setup<AbstractConfigurations>(
	AbstractConfigurations
	{
		.is_enabled = false
	}
);

std::cout << AbstractConfigurations::default_configurations.is_enabled << "\n";

AbstractConfigurations a;

	ImplementationConfigurations i;

	std::cout << a.is_enabled << " " << i.is_enabled << "\n";


class ConfigurationsManager
{
public:
	static ConfigurationsManager
		singleton;

	template <typename Type> void
		setup(
			const Type& configurations = {}
		);
};

ConfigurationsManager
	ConfigurationsManager::singleton;


template <typename Type>
void ConfigurationsManager::setup(
	const Type& configurations
)
{
	Type::default_configurations = configurations;
}



struct AbstractConfigurations
{
	bool is_enabled =
		default_configurations.is_enabled;

	static AbstractConfigurations
		default_configurations;
};

AbstractConfigurations
	AbstractConfigurations::default_configurations =
	{
		.is_enabled = true
	};


struct ImplementationConfigurations :
	AbstractConfigurations
{
	bool is_enabled =
		default_configurations.is_enabled;

	static ImplementationConfigurations
		default_configurations;
};

ImplementationConfigurations
	ImplementationConfigurations::default_configurations =
	{
		.is_enabled = false
	};

struct AbstractConfigurations
{
	bool is_enabled =
		default_configurations.is_enabled;

	static AbstractConfigurations
		default_configurations;
};

AbstractConfigurations
	AbstractConfigurations::default_configurations;


	AbstractConfigurations a;

	AbstractConfigurations::setup(a);

*/
