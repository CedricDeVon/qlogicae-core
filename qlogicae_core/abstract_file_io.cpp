#include "pch.hpp"

#include "abstract_file_io.hpp"

namespace QLogicaeCore
{
	AbstractFileIO::AbstractFileIO(
		const std::string& file_path) :
			_file_path(file_path)
	{

	}

	AbstractFileIO::AbstractFileIO(
		const std::string& name,
		const std::string& file_path) :
			_name(name),
			_file_path(file_path)
	{

	}

	std::string AbstractFileIO::get_name() const
	{
		return _name;
	}

	std::string AbstractFileIO::get_file_path() const
	{
		return _file_path;
	}

	std::size_t AbstractFileIO::get_line_count() const
	{
		std::ifstream file(_file_path);
		
		if (!file.is_open())
		{
			return 0;
		}

		std::size_t count = 0;
		std::string line;

		while (std::getline(file, line))
		{
			++count;
		}

		return count;
	}

	void AbstractFileIO::set_file_path(
		const std::string& file_path
	)
	{
		_file_path = file_path;
	}


	void AbstractFileIO::get_name(
		Result<std::string>& result
	) const
	{
		result.set_to_success(_name);
	}

	void AbstractFileIO::get_file_path(
		Result<std::string>& result
	) const
	{
		result.set_to_success(_file_path);
	}

	void AbstractFileIO::get_line_count(
		Result<std::size_t>& result
	) const
	{
		std::ifstream file(_file_path);

		if (!file.is_open())
		{
			result.set_to_success(0);
		}

		std::size_t count = 0;
		std::string line;

		while (std::getline(file, line))
		{
			++count;
		}

		result.set_to_success(count);
	}

	void AbstractFileIO::set_file_path(
		Result<bool>& result,
		const std::string& file_path
	)
	{
		_file_path = file_path;
		result.set_is_successful(true);
	}
}