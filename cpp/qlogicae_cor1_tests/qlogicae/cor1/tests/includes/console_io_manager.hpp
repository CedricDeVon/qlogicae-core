#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		ConsoleIoManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
		ConsoleIoManagerTest:
		public ::testing::Test
	{
	public:
		ConsoleIoManagerTest()
		{
			original_cin_buffer =
				std::cin.rdbuf();
			original_cout_buffer =
				std::cout.rdbuf();
		}

		~ConsoleIoManagerTest()
		{
			std::cin.rdbuf(
				original_cin_buffer
			);
			std::cout.rdbuf(
				original_cout_buffer
			);
		}

		void
			SetUp() override
		{
			manager.construct();
			manager.reset();
		}

		void
			TearDown() override
		{
			manager.destruct();
			manager.reset();
		}

		ConsoleIoManager
			manager;

		std::streambuf*
			original_cin_buffer;

		std::streambuf*
			original_cout_buffer;
	};

	class
		ConsoleIoManagerPrintParameterizedTest:
		public ConsoleIoManagerTest,
		public ::testing::WithParamInterface<std::string>
	{
	};
}

#endif
