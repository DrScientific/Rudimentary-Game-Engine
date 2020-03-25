#include "pch.h"
#include "Foo.h"
#include <string>

using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;

namespace UnitTests
{
	RTTI_DEFINITIONS(Foo);


	Foo::Foo(int data) :
		mData(new int(data))
	{
	}

	Foo::Foo(const Foo& rhs) :
		mData(new int(*rhs.mData))
	{
	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			*mData = *rhs.mData;
		}

		return *this;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		return *mData == *rhs.mData;
	}

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}

	bool Foo::Equals(RTTI const * rhs) const
	{
		Foo* other = rhs->As<Foo>();
		return (other != nullptr ? *this == *other : false);
	}

	std::string Foo::ToString() const
	{;
		return (mData != nullptr ? to_string(*mData ) : "nullptr");
	}

	int Foo::Data() const
	{
		return *mData;
	}

	void Foo::SetData(int data)
	{
		*mData = data;
	}
}