#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		RocksDbDatabaseManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class RocksDbDatabaseManagerTest:
		public ::testing::Test
	{
	public:
		RocksDbDatabaseManager manager;

		std::string database_path;

		RocksDbDatabaseManagerTest()
		{
			this->database_path =
				std::string("qlogicae_test_db_") +
				std::to_string(
					std::chrono::steady_clock::
					now().time_since_epoch().count()
				);

			manager.configurations.file_path = this->database_path;
		}

		void SetUp() override
		{
			if(std::filesystem::exists(this->database_path))
			{
				std::filesystem::remove_all(
					this->database_path
				);
			}
			this->manager.open();
		}

		void TearDown() override
		{
			this->manager.close();
			if(std::filesystem::exists(this->database_path))
			{
				std::filesystem::remove_all(
					this->database_path
				);
			}
		}
	};

	class RocksDbDatabaseManagerTestParameterized:
		public ::testing::TestWithParam<bool>
	{
	public:
		RocksDbDatabaseManager manager;
	};
}

#endif
