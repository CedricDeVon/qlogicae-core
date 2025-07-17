#pragma once

#include "pch.h"

#include "file_ios.hpp"

namespace QLogicaeCore
{
	FileIOs& FileIOs::get_instance()
	{
		static FileIOs singleton;

		return singleton;
	}

	void FileIOs::set_file(std::shared_ptr<AbstractFileIO> get_instance)
	{
		try
		{
			_instances[get_instance->get_name()] = std::move(get_instance);
		}
		catch (...)
		{
			throw std::runtime_error("runtime_error");
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
		catch (...)
		{
			throw std::runtime_error("runtime_error");
		}
	}
}
