#include "pch.h"
#include "AttributedFoo.h"

using namespace FIEAGameEngine;
using namespace std;
using namespace std::string_literals;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedFoo)


	AttributedFoo::AttributedFoo() : Attributed(TypeIdClass())
	{

	}

	std::string AttributedFoo::ToString() const
	{
		return "AttributedFoo";
	}

	const Vector<Attributed::Signature> AttributedFoo::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{"ExternalInteger", Datum::DatumType::Integer, 1, offsetof(AttributedFoo, ExternalInteger) },
			{ "ExternalFloat", Datum::DatumType::Float, 1, offsetof(AttributedFoo, ExternalFloat) },
			{ "ExternalString", Datum::DatumType::String, 1, offsetof(AttributedFoo, ExternalString) },
			{ "ExternalVector", Datum::DatumType::Vector4, 1, offsetof(AttributedFoo, ExternalVector) },
			{ "ExternalMatrix", Datum::DatumType::Matrix4x4, 1, offsetof(AttributedFoo, ExternalMatrix) },
			{ "ExternalIntegerArray", Datum::DatumType::Integer, ArraySize, offsetof(AttributedFoo, ExternalIntegerArray) },
			{ "ExternalFloatArray", Datum::DatumType::Float, ArraySize, offsetof(AttributedFoo, ExternalFloatArray) },
			{ "ExternalStringArray", Datum::DatumType::String, ArraySize, offsetof(AttributedFoo, ExternalStringArray) },
			{ "ExternalVectorArray", Datum::DatumType::Vector4, ArraySize, offsetof(AttributedFoo, ExternalVectorArray) },
			{ "ExternalMatrixArray", Datum::DatumType::Matrix4x4, ArraySize, offsetof(AttributedFoo, ExternalMatrixArray) },
			{ "NestedScope", Datum::DatumType::Scope, 0, 0 },
			{ "NestedScopeArray", Datum::DatumType::Scope, ArraySize, 0 }
		};
	}

}