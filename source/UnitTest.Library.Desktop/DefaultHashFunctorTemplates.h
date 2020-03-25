#pragma once

/// <summary>
/// 
/// </summary>

#include "pch.h"
#include "Foo.h"
#include "DefaultHashFunctor.h"

namespace FIEAGameEngine
{
	template<>
	struct DefaultHashFunctor<UnitTests::Foo>
	{
		size_t operator() (UnitTests::Foo const & key) const
		{
			return key.Data();
		}
	};
}