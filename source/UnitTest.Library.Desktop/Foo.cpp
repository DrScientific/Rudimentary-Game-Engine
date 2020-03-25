#pragma once

/// <summary>
/// The file containing all of the defintions of the Foo class.
/// </summary>

#include "pch.h"
#include "Foo.h"

namespace UnitTests
{
	/// <summary>
	/// Default constructor.
	/// 
	/// </summary>
	Foo::Foo() : mData(0)
	{
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="data"></param>
	Foo::Foo(int data) : mData(data)
	{

	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	Foo& Foo::operator=(const Foo& rhs)
	{
		mData = rhs.Data();
		return *this;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	bool Foo::operator==(const Foo & rhs) const
	{
		return Data() == rhs.Data();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	bool Foo::operator!=(const Foo & rhs) const
	{
		return !(*this == rhs);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int Foo::Data() const
	{
		return mData;
	}

}

