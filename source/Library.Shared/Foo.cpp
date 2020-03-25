#include "pch.h"
#include "Foo.h"



namespace FIEAGameEngine
{
	Foo::Foo(int data) : mData(data)
	{

	}

	int Foo::Data() const
	{
		return mData;
	}
}

