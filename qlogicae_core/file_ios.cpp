#include "pch.hpp"

#include "file_ios.hpp"

namespace QLogicaeCore
{
	FileIOs& FileIOs::get_instance()
	{
		static FileIOs singleton;

		return singleton;
	}

	void FileIOs::setup(
		Result<void>& result
	)
	{
		result.set_to_success();
	}

	void FileIOs::set_file(std::shared_ptr<AbstractFileIO> instances)
	{
		try
		{
			_instances[instances->get_name()] = std::move(instances);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at FileIOs::set_file(): " + exception.what());
		}
	}

	void FileIOs::set_file(
		const std::vector<std::shared_ptr<AbstractFileIO>>& instances)
	{
		try
		{
			unsigned int index;
			size_t size = instances.size();
			std::shared_ptr<AbstractFileIO> get_instance;
			for (index = 0; index < size; ++index)
			{
				get_instance = instances[index];
				_instances[get_instance->get_name()] = std::move(get_instance);
			}
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(std::string() + "Exception at FileIOs::set_file(): " + exception.what());
		}
	}

	void FileIOs::set_file(
		Result<void>& result,
		std::shared_ptr<AbstractFileIO> instances
	)
	{
		_instances[instances->get_name()] = std::move(instances);
	}

	void FileIOs::set_file(
		Result<void>& result,
		const std::vector<std::shared_ptr<AbstractFileIO>>& instances
	)
	{
		unsigned int index;
		size_t size = instances.size();
		std::shared_ptr<AbstractFileIO> get_instance;
		for (index = 0; index < size; ++index)
		{
			get_instance = instances[index];
			_instances[get_instance->get_name()] = std::move(get_instance);
		}
	}

	void FileIOs::get_instance(
		Result<FileIOs*>& result
	)
	{
		static FileIOs instance;

		result.set_to_success(&instance);
	}
}

