#include "pch.h"
#include "Foo.h"

namespace UnitTests
{
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

	int Foo::Data() const
	{
		return *mData;
	}

	void Foo::SetData(int data)
	{
		*mData = data;
	}
}