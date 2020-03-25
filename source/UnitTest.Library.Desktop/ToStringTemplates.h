#pragma once

/// <summary>
/// Converts Foo to a wide string to allow for Assert::ExpectedException<std::exception>() calls.
/// </summary>

#include "pch.h"
#include "Foo.h"
#include "SList.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}
}