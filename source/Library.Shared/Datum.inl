/// <summary>
/// The inl file containing the definition of templated Datum functions declared in Datum.h.
/// </summary>

#include "Datum.h"
#include "Scope.h"

using namespace glm;
using namespace std;
using namespace FIEAGameEngine;

#pragma region Get
template<typename T>
inline T Datum::Get(size_t const & index) const
{
	throw exception(unsupportedDataTypeExceptionText.c_str());
	index;
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
	if (mType != DatumType::Table)
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

#pragma region ResizeTemplated
template<typename T>
inline void Datum::ResizeTemplated(T * & templatedPtr, size_t newSize)
{
	if (mIsInternal)
	{
		if (newSize > mCapacity)
		{
			Reserve(newSize);
			while (newSize > mSize)
			{
				PushBackTemplated<T>(templatedPtr, T());
			}
		}
		else if (newSize > mSize)
		{
			while (newSize > mSize)
			{
				PushBackTemplated<T>(templatedPtr, T());
			}
		}
		else if (newSize < mSize)
		{
			RemoveRange(newSize, mSize);
		}
	}
	else
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
}
#pragma endregion

#pragma region Clear
template<typename T>
inline void Datum::ClearTemplated(T * & templatedPtr)
{
	if (mIsInternal)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			templatedPtr[i].~T();
		}
		mSize = 0;
	}
	else
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
}
#pragma endregion

#pragma region SetFromStringTemplated
template<typename T>
void Datum::SetFromStringTemplated(string const & value, size_t const & index)
{
	throw exception(unsupportedDataTypeExceptionText.c_str());
	value;
	index;
}

template<>
void Datum::SetFromStringTemplated<int>(string const & value, size_t const & index)
{
	Set(stoi(value), index);
}

template<>
void Datum::SetFromStringTemplated<float>(string const & value, size_t const & index)
{
	Set(stof(value), index);
}

template<>
void Datum::SetFromStringTemplated<vec4>(string const & value, size_t const & index)
{

	float vec4Array[4];
	sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &vec4Array[0], &vec4Array[1], &vec4Array[2], &vec4Array[3]);
	vec4 readInVec = vec4(vec4Array[0], vec4Array[1], vec4Array[2], vec4Array[3]);
	Set(readInVec, index);
}

template<>
void Datum::SetFromStringTemplated<mat4x4>(string const & value, size_t const & index)
{
	float mat4x4Array[16];
	sscanf_s(value.c_str(), "mat4x4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))",
		&mat4x4Array[0], &mat4x4Array[1], &mat4x4Array[2], &mat4x4Array[3],
		&mat4x4Array[4], &mat4x4Array[5], &mat4x4Array[6], &mat4x4Array[7],
		&mat4x4Array[8], &mat4x4Array[9], &mat4x4Array[10], &mat4x4Array[11],
		&mat4x4Array[12], &mat4x4Array[13], &mat4x4Array[14], &mat4x4Array[15]);
	mat4x4 readInMat = mat4x4(mat4x4Array[0], mat4x4Array[1], mat4x4Array[2], mat4x4Array[3],
		mat4x4Array[4], mat4x4Array[5], mat4x4Array[6], mat4x4Array[7],
		mat4x4Array[8], mat4x4Array[9], mat4x4Array[10], mat4x4Array[11],
		mat4x4Array[12], mat4x4Array[13], mat4x4Array[14], mat4x4Array[15]);
	Set(readInMat, index);
}

template<>
void Datum::SetFromStringTemplated<string>(string const & value, size_t const & index)
{
	Set(value, index);
}

template<>
void Datum::SetFromStringTemplated<RTTI*>(string const & value, size_t const & index)
{
	throw exception(unsupportedDataTypeExceptionText.c_str());
	value;
	index;
}
#pragma endregion

#pragma region ToStringTemplated
template<typename T>
string Datum::ToStringTemplated(T * const & templatedPtr, size_t const & index) const
{
	throw exception(unsupportedDataTypeExceptionText.c_str());
}

template<>
string Datum::ToStringTemplated(int * const & templatedPtr, size_t const & index) const
{
	return std::to_string(templatedPtr[index]);
}

template<>
string Datum::ToStringTemplated(float * const & templatedPtr, size_t const & index) const
{
	return std::to_string(templatedPtr[index]);
}

template<>
string Datum::ToStringTemplated(vec4 * const & templatedPtr, size_t const & index) const
{
	return glm::to_string(templatedPtr[index]);
}

template<>
string Datum::ToStringTemplated(mat4x4 * const & templatedPtr, size_t const & index) const
{
	return glm::to_string(templatedPtr[index]);
}

template<>
string Datum::ToStringTemplated(string * const & templatedPtr, size_t const & index) const
{
	return templatedPtr[index];
}

template<>
string Datum::ToStringTemplated(RTTI ** const & templatedPtr, size_t const & index) const
{
	return (templatedPtr[index] != nullptr ? templatedPtr[index]->ToString() : "nullptr");
}
#pragma endregion

#pragma region PushBackTemplated
template<typename T>
inline void Datum::PushBackTemplated(T * & templatedPtr, T const & value)
{
	if (mIsInternal)
	{
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				mCapacity = 1;
			}
			Reserve(mCapacity * 2);
		}

		new (templatedPtr + (mSize++)) T(value);
	}
	else
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
}
#pragma endregion

#pragma region PopBack
template<typename T>
inline void Datum::PopBackTemplated(T * & templatedPtr)
{
	if (mIsInternal)
	{
		if (mSize != 0)
		{
			templatedPtr[--mSize].~T();
		}
	}
	else
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
}
#pragma endregion

#pragma region RemoveTemplated
template<typename T>
void Datum::RemoveTemplated(T *& templatedPtr, T const & value)
{
	if (mType != DatumType::Unknown)
	{
		if (mIsInternal)
		{
			for (size_t i = 0; i < mSize; i++)
			{
				if (templatedPtr[i] == value)
				{
					templatedPtr[i].~T();
					memmove(&(templatedPtr[i]), &(templatedPtr[i + 1]), (mSize - 1 - i) * sizeof(T));
					mSize--;
					break;
				}
			}
		}
		else
		{
			throw exception(cannotMutateExternalStorageExceptionText.c_str());
		}
	}
	else
	{
		throw exception(datumTypeNotInitializedExceptionText.c_str());
	}
}
#pragma endregion

#pragma region RemoveAtTemplated
template<typename T>
void Datum::RemoveAtTemplated(T *& templatedPtr, size_t const & index)
{
	if (mIsInternal)
	{
		if (index < mSize)
		{
			templatedPtr[index].~T();
			memmove(&(templatedPtr[index]), &(templatedPtr[index + 1]), (mSize - 1 - index) * sizeof(T));
			mSize--;
		}
		else
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
	}
	else
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
}
#pragma endregion

#pragma region RemoveRangeTemplated
template<typename T>
void Datum::RemoveRangeTemplated(T *& templatedPtr, size_t const & start, size_t const & finish)
{
	if (mIsInternal)
	{
		if (start < mSize && finish <= mSize)
		{
			if (mSize > 0 && start < finish)
			{

				for (size_t i = start; i < finish; i++)
				{
					templatedPtr[i].~T();
				}
				memmove(&(templatedPtr[start]), &(templatedPtr[finish]), (mSize - finish) * sizeof(T));
				mSize -= (finish - start);

			}
		}
		else
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
	}
	else
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
}
#pragma endregion