#pragma once

#include "qlogicae/cor1/sandbox/includes/application.hpp"

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

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_SANDBOX_NAMESPACE_NAME
{

}

class TestSubject1
{
public:
	bool execute()
	{
		return true;
	}

	static TestSubject1& get_this()
	{
		static TestSubject1 instance;

		return instance;
	}
};

class TestSubject2
{
public:
	bool execute()
	{
		return true;
	}

	static TestSubject2& get_this()
	{
		static TestSubject2 instance;

		return instance;
	}
};



enum class TestSubjects
{
	TestSubject1,

	TestSubject2
};



class TestSubject3
{
public:
	bool execute(const TestSubjects& type)
	{
		switch (type)
		{
		case (TestSubjects::TestSubject1):
		{
			return TestSubject1::get_this().execute();
		}
		case (TestSubjects::TestSubject2):
		{
			return TestSubject2::get_this().execute();
		}
		default:
		{
			return TestSubject1::get_this().execute();
		}
		}
	}

	static TestSubject3& get_this()
	{
		static TestSubject3 instance;

		return instance;
	}
};