#pragma once

#include "pch.h"

#include "file_ios.hpp"

namespace QLogicaeCore
{
	FileIOs& FileIOs::instance()
	{
		static FileIOs singleton;

		return singleton;
	}

	void FileIOs::set_file(std::shared_ptr<AbstractFileIO> instance)
	{
		try
		{
			_instances[instance->get_name()] = std::move(instance);
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
			std::shared_ptr<AbstractFileIO> instance;
			for (index = 0; index < size; ++index)
			{
				instance = instances[index];
				_instances[instance->get_name()] = std::move(instance);
			}
		}
		catch (...)
		{
			throw std::runtime_error("runtime_error");
		}
	}
}
