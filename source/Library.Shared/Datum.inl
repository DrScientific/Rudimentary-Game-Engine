/// <summary>
/// The inl file containing the definition of templated Datum functions declared in Datum.h.
/// </summary>

#include "Datum.h"
#include "RTTI.h"
#pragma warning(push)
#pragma warning(disable: 4201)
#include "glm/glm.hpp"
#include "glm/gtx/string_cast.hpp"
#pragma warning(pop)

using namespace glm;
using namespace std;
using namespace FIEAGameEngine;

namespace FIEAGameEngine
{
#pragma region Get
	template<typename T>
	inline T Datum::Get(size_t const &) const
	{
		throw exception(unsupportedDataTypeExceptionText.c_str());
	}

	template<>
	inline int Datum::Get<int>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::Integer)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tInt[index];
	}

	template<>
	inline float Datum::Get<float>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::Float)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tFloat[index];
	}

	template<>
	inline vec4 Datum::Get<vec4>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::Vector4)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tVec4[index];
	}

	template<>
	inline mat4x4 Datum::Get<mat4x4>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::Matrix4x4)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tMat4x4[index];
	}

	template<>
	inline Scope* Datum::Get<Scope*>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::Scope)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tScope[index];
	}

	template<>
	inline string Datum::Get<string>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::String)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tString[index];
	}

	template<>
	inline RTTI* Datum::Get<RTTI*>(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		if (mType != DatumType::RTTIPtr)
		{
			throw exception(operationTypeMismatchExceptionText.c_str());
		}
		return mArray.tRTTIPtr[index];
	}
#pragma endregion

#pragma region Front
	template<typename T>
	inline T Datum::Front() const
	{
		throw exception(unsupportedDataTypeExceptionText.c_str());
	}

	template<>
	inline int Datum::Front<int>() const
	{
		return Get<int>(0);
	}

	template<>
	inline float Datum::Front<float>() const
	{
		return Get<float>(0);
	}

	template<>
	inline vec4 Datum::Front<vec4>() const
	{
		return Get<vec4>(0);
	}

	template<>
	inline mat4x4 Datum::Front<mat4x4>() const
	{
		return Get<mat4x4>(0);
	}

	template<>
	inline Scope* Datum::Front<Scope*>() const
	{
		return Get<Scope*>(0);
	}

	template<>
	inline string Datum::Front<string>() const
	{
		return Get<string>(0);
	}

	template<>
	inline RTTI* Datum::Front<RTTI*>() const
	{
		return Get<RTTI*>(0);
	}
#pragma endregion

#pragma region Back
	template<typename T>
	inline T Datum::Back() const
	{
		throw exception(unsupportedDataTypeExceptionText.c_str());
	}

	template<>
	inline int Datum::Back<int>() const
	{
		return Get<int>(mSize - 1);
	}

	template<>
	inline float Datum::Back<float>() const
	{
		return Get<float>(mSize - 1);
	}

	template<>
	inline vec4 Datum::Back<vec4>() const
	{
		return Get<vec4>(mSize - 1);
	}

	template<>
	inline mat4x4 Datum::Back<mat4x4>() const
	{
		return Get<mat4x4>(mSize - 1);
	}

	template<>
	inline Scope* Datum::Back<Scope*>() const
	{
		return Get<Scope*>(mSize - 1);
	}

	template<>
	inline string Datum::Back<string>() const
	{
		return Get<string>(mSize - 1);
	}

	template<>
	inline RTTI* Datum::Back<RTTI*>() const
	{
		return Get<RTTI*>(mSize - 1);
	}
#pragma endregion
}