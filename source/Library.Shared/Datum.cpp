/// <summary>
/// The cpp file containing the definition of nontemplated Datum functions declared in Datum.h.
/// </summary>

#include "pch.h"
#include "Datum.h"
#include "Scope.h"

using namespace glm;
using namespace std;
using namespace FIEAGameEngine;

#pragma region TypeSizesTable
const size_t Datum::mTypeSizes[] =
{
	0, // Unknown
	sizeof(int),
	sizeof(float),
	sizeof(vec4),
	sizeof(mat4),
	sizeof(Scope*),
	sizeof(string),
	sizeof(RTTI*)
};
#pragma endregion

#pragma region Constructor
Datum::Datum(Datum const & other)
{
	*this = other;
}

Datum::Datum(int const & other)
{
	PushBack(other);
}

Datum::Datum(float const & other)
{
	PushBack(other);
}

Datum::Datum(vec4 const & other)
{
	PushBack(other);
}

Datum::Datum(mat4x4 const & other)
{
	PushBack(other);
}

FIEAGameEngine::Datum::Datum(Scope * const & other)
{
	PushBack(other);
}

Datum::Datum(string const & other)
{
	PushBack(other);
}

Datum::Datum(RTTI * const & other)
{
	PushBack(other);
}
#pragma endregion

#pragma region operator=
Datum & Datum::operator=(Datum const & rhs)
{
	if (*this != rhs)
	{
		if (mIsInternal)
		{
			Clear();
			ShrinkToFit();
		}

		mType = rhs.mType;

		if (rhs.mIsInternal)
		{
			mIsInternal = true;
			if (mType != DatumType::Unknown && mType != DatumType::String)
			{
				Reserve(rhs.mSize);
				memcpy(mArray.tVoid, rhs.mArray.tVoid, rhs.mSize * mTypeSizes[static_cast<size_t>(mType)]);
				mSize = rhs.mSize;
			}
			else if (mType == DatumType::String)
			{
				for (size_t i = 0; i < rhs.mSize; i++)
				{
					PushBack(rhs.mArray.tString[i]);
				}
			}
		}
		else if (!rhs.mIsInternal)
		{
			mIsInternal = false;
			mCapacity = rhs.mCapacity;
			mSize = rhs.mSize;
			mArray = rhs.mArray;
		}
	}
	return *this;
}

Datum & Datum::operator=(int const & rhs)
{

	if (mType == DatumType::Unknown || mType == DatumType::Integer)
	{
		mType = DatumType::Integer;
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Resize(1);
		ShrinkToFit();
		Set(rhs);
	}
	else
	{
		mSize = 1;
		mCapacity = 1;
		mArray.tInt = &(const_cast<int&>(rhs));
	}

	return *this;
}

Datum & Datum::operator=(float const & rhs)
{
	if (mType == DatumType::Unknown || mType == DatumType::Float)
	{
		mType = DatumType::Float;
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Resize(1);
		ShrinkToFit();
		Set(rhs);
	}
	else
	{
		mSize = 1;
		mCapacity = 1;
		mArray.tFloat = &(const_cast<float&>(rhs));
	}
	return *this;
}

Datum & Datum::operator=(vec4 const & rhs)
{
	if (mType == DatumType::Unknown || mType == DatumType::Vector4)
	{
		mType = DatumType::Vector4;
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Resize(1);
		ShrinkToFit();
		Set(rhs);
	}
	else
	{
		mSize = 1;
		mCapacity = 1;
		mArray.tVec4 = &(const_cast<vec4&>(rhs));
	}
	return *this;
}

Datum & Datum::operator=(mat4x4 const & rhs)
{
	if (mType == DatumType::Unknown || mType == DatumType::Matrix4x4)
	{
		mType = DatumType::Matrix4x4;
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Resize(1);
		ShrinkToFit();
		Set(rhs);
	}
	else
	{
		mSize = 1;
		mCapacity = 1;
		mArray.tMat4x4 = &(const_cast<mat4x4&>(rhs));
	}
	return *this;
}

//Datum & FIEAGameEngine::Datum::operator=(Scope * const & rhs)
//{
//	if (mType == DatumType::Unknown || mType == DatumType::Table)
//	{
//		mType = DatumType::Table;
//	}
//	else
//	{
//		throw exception(operationTypeMismatchExceptionText.c_str());
//	}
//	if (mIsInternal)
//	{
//		Resize(1);
//		ShrinkToFit();
//		Set(rhs);
//	}
//	else
//	{
//		mSize = 1;
//		mCapacity = 1;
//		mArray.tScope = &(const_cast<Scope*&>(rhs));
//	}
//	return *this;
//}

Datum & Datum::operator=(string const & rhs)
{
	if (mType == DatumType::Unknown || mType == DatumType::String)
	{
		mType = DatumType::String;
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Resize(1);
		ShrinkToFit();
		Set(rhs);
	}
	else
	{
		mSize = 1;
		mCapacity = 1;
		mArray.tString = &(const_cast<string&>(rhs));
	}
	return *this;
}

Datum & Datum::operator=(RTTI * const & rhs)
{
	if (mType == DatumType::Unknown || mType == DatumType::RTTIPtr)
	{
		mType = DatumType::RTTIPtr;
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Resize(1);
		ShrinkToFit();
		Set(rhs);
	}
	else
	{
		mSize = 1;
		mCapacity = 1;
		mArray.tRTTIPtr = &(const_cast<RTTI*&>(rhs));
	}
	return *this;
}
#pragma endregion

#pragma region InitializerList
Datum::Datum(initializer_list<int> const & iList)
{
	SetType(DatumType::Integer);
	for (auto i : iList)
	{
		PushBack(i);
	}
}

Datum::Datum(initializer_list<float> const & iList)
{
	SetType(DatumType::Float);
	for (auto i : iList)
	{
		PushBack(i);
	}
}

Datum::Datum(initializer_list<vec4> const & iList)
{
	SetType(DatumType::Vector4);
	for (auto i : iList)
	{
		PushBack(i);
	}
}

Datum::Datum(initializer_list<mat4x4> const & iList)
{
	SetType(DatumType::Matrix4x4);
	for (auto i : iList)
	{
		PushBack(i);
	}
}

Datum::Datum(initializer_list<Scope*> const & iList)
{
	SetType(DatumType::Table);
	for (auto i : iList)
	{
		PushBack(i);
	}
}

Datum::Datum(initializer_list<string> const & iList)
{
	SetType(DatumType::String);
	for (auto i : iList)
	{
		PushBack(i);
	}
}

Datum::Datum(initializer_list<RTTI*> const & iList)
{
	SetType(DatumType::RTTIPtr);
	for (auto i : iList)
	{
		PushBack(i);
	}
}
#pragma endregion

#pragma region Destructor
Datum::~Datum()
{
	if (mIsInternal)
	{
		if (mType != DatumType::Unknown)
		{
			Clear();
			ShrinkToFit();
		}
	}
}
#pragma endregion

#pragma region Reserve
void Datum::Reserve(size_t newCapacity)
{
	if (!mIsInternal)
	{
		throw exception(cannotMutateExternalStorageExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		throw exception(datumTypeNotInitializedExceptionText.c_str());
	}
	if (newCapacity > mCapacity)
	{
		mCapacity = newCapacity;
		mArray.tVoid = realloc(mArray.tVoid, mCapacity * mTypeSizes[static_cast<size_t>(mType)]);
	}
}
#pragma endregion

#pragma region operator==
bool Datum::operator==(Datum const & rhs) const
{
	bool result = false;
	if (mSize == rhs.mSize && mIsInternal == rhs.mIsInternal && mType == rhs.mType)
	{
		if (mType != DatumType::String)
		{
			result = memcmp(mArray.tVoid, rhs.mArray.tVoid, mSize * mTypeSizes[static_cast<size_t>(mType)]) == 0;
		}
		else
		{
			result = true;
			for (size_t i = 0; i < mSize; i++)
			{
				if (mArray.tString[i] != rhs.mArray.tString[i])
				{
					result = false;
					break;
				}
			}
		}
	}
	return result;
}

bool Datum::operator==(int const & rhs) const
{
	if (DatumType::Integer != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	return mSize == 1 && mArray.tInt[0] == rhs;
}

bool Datum::operator==(float const & rhs) const
{
	if (DatumType::Float != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	return mSize == 1 && mArray.tFloat[0] == rhs;
}

bool Datum::operator==(vec4 const & rhs) const
{
	if (DatumType::Vector4 != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	return mSize == 1 && mArray.tVec4[0] == rhs;
}

bool Datum::operator==(mat4x4 const & rhs) const
{
	if (DatumType::Matrix4x4 != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	return mSize == 1 && mArray.tMat4x4[0] == rhs;
}

bool Datum::operator==(string const & rhs) const
{
	if (DatumType::String != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	return mSize == 1 && mArray.tString[0] == rhs;
}

bool Datum::operator==(RTTI * const & rhs) const
{
	bool result = false;
	if (DatumType::RTTIPtr != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mArray.tRTTIPtr[0] != nullptr)
	{
		result = mSize == 1 && mArray.tRTTIPtr[0]->Equals(const_cast<RTTI*>(rhs));
	}
	else if (rhs == nullptr)
	{
		result = true;
	}
	return result;
}
#pragma endregion

#pragma region operator!=
bool Datum::operator!=(Datum const & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(int const & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(float const & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(vec4 const & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(mat4x4 const & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(string const & rhs) const
{
	return !(operator==(rhs));
}

bool Datum::operator!=(RTTI * const & rhs) const
{
	return !(operator==(rhs));
}
#pragma endregion

#pragma region operator[]
Scope & FIEAGameEngine::Datum::operator[](size_t index)
{
	if (mType != DatumType::Table)
	{
		throw exception(bracketOperatorOnlyValidForScopesExceptionText.c_str());
	}
	return *Get<Scope*>(index);
}
#pragma endregion

#pragma region Type
Datum::DatumType Datum::Type() const
{
	return mType;
}
#pragma endregion

#pragma region SetType
void Datum::SetType(DatumType type)
{
	if (mType == DatumType::Unknown)
	{
		mType = type;
	}
	else
	{
		throw exception(datumTypeAlreadyInitializedExceptionText.c_str());
	}
}
#pragma endregion

#pragma region Size
size_t Datum::Size() const
{
	return mSize;
}
#pragma endregion

#pragma region Capacity
size_t FIEAGameEngine::Datum::Capacity() const
{
	return mCapacity;
}
#pragma endregion

#pragma region Resize
void Datum::Resize(size_t newSize)
{
	//External memory check done in templated function.
	switch (mType)
	{
	case DatumType::Integer:
		ResizeTemplated<int>(mArray.tInt, newSize);
		break;
	case DatumType::Float:
		ResizeTemplated<float>(mArray.tFloat, newSize);
		break;
	case DatumType::Vector4:
		ResizeTemplated<vec4>(mArray.tVec4, newSize);
		break;
	case DatumType::Matrix4x4:
		ResizeTemplated<mat4x4>(mArray.tMat4x4, newSize);
		break;
	case DatumType::Table:
		ResizeTemplated<Scope*>(mArray.tScope, newSize);
		break;
	case DatumType::String:
		ResizeTemplated<string>(mArray.tString, newSize);
		break;
	case DatumType::RTTIPtr:
		ResizeTemplated<RTTI*>(mArray.tRTTIPtr, newSize);
		break;
	default:
		throw exception(datumTypeNotInitializedExceptionText.c_str());
		break;
	}
}
#pragma endregion

#pragma region ShrinkToFit
void FIEAGameEngine::Datum::ShrinkToFit()
{
	if (mIsInternal)
	{
		if (mSize != mCapacity)
		{
			if (mSize == 0)
			{
				free(mArray.tVoid);
				mArray.tVoid = nullptr;
				mCapacity = 0;
			}
			else
			{
				mCapacity = mSize;
				mArray.tVoid = realloc(mArray.tVoid, mCapacity * mTypeSizes[static_cast<size_t>(mType)]);
			}
		}
	}
}
#pragma endregion

#pragma region Clear
void Datum::Clear()
{
	//External memory check done in templated function.
	switch (mType)
	{
	case DatumType::Integer:
		ClearTemplated<int>(mArray.tInt);
		break;
	case DatumType::Float:
		ClearTemplated<float>(mArray.tFloat);
		break;
	case DatumType::Vector4:
		ClearTemplated<vec4>(mArray.tVec4);
		break;
	case DatumType::Matrix4x4:
		ClearTemplated<mat4x4>(mArray.tMat4x4);
		break;
	case DatumType::Table:
		ClearTemplated<Scope*>(mArray.tScope);
		break;
	case DatumType::String:
		ClearTemplated<string>(mArray.tString);
		break;
	case DatumType::RTTIPtr:
		ClearTemplated<RTTI*>(mArray.tRTTIPtr);
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region SetStorage
void Datum::SetStorage(int * const & data, size_t const & size)
{
	if (data == nullptr || size <= 0)
	{
		throw exception(cannotSetStorageInvalidParamExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Integer;
	}
	if (mType != DatumType::Integer)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Clear();
		ShrinkToFit();
	}
	mIsInternal = false;
	mArray.tInt = data;
	mSize = mCapacity = size;
}

void Datum::SetStorage(float * const & data, size_t const & size)
{
	if (data == nullptr || size <= 0)
	{
		throw exception(cannotSetStorageInvalidParamExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Float;
	}
	if (mType != DatumType::Float)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Clear();
		free(mArray.tVoid);
	}
	mIsInternal = false;
	mArray.tFloat = data;
	mSize = mCapacity = size;
}

void Datum::SetStorage(vec4 * const & data, size_t const & size)
{
	if (data == nullptr || size <= 0)
	{
		throw exception(cannotSetStorageInvalidParamExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Vector4;
	}
	if (mType != DatumType::Vector4)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Clear();
		free(mArray.tVoid);
	}
	mIsInternal = false;
	mArray.tVec4 = data;
	mSize = mCapacity = size;
}

void Datum::SetStorage(mat4x4 * const & data, size_t const & size)
{
	if (data == nullptr || size <= 0)
	{
		throw exception(cannotSetStorageInvalidParamExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::Matrix4x4;
	}
	if (mType != DatumType::Matrix4x4)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Clear();
		free(mArray.tVoid);
	}
	mIsInternal = false;
	mArray.tMat4x4 = data;
	mSize = mCapacity = size;
}

void Datum::SetStorage(string * const & data, size_t const & size)
{
	if (data == nullptr || size <= 0)
	{
		throw exception(cannotSetStorageInvalidParamExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::String;
	}
	if (mType != DatumType::String)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Clear();
		free(mArray.tVoid);
	}
	mIsInternal = false;
	mArray.tString = data;
	mSize = mCapacity = size;
}

void Datum::SetStorage(RTTI ** const & data, size_t const & size)
{
	if (data == nullptr || size <= 0)
	{
		throw exception(cannotSetStorageInvalidParamExceptionText.c_str());
	}
	if (mType == DatumType::Unknown)
	{
		mType = DatumType::RTTIPtr;
	}
	if (mType != DatumType::RTTIPtr)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	if (mIsInternal)
	{
		Clear();
		free(mArray.tVoid);
	}
	mIsInternal = false;
	mArray.tRTTIPtr = data;
	mSize = mCapacity = size;
}
#pragma endregion

#pragma region IsInternal
bool FIEAGameEngine::Datum::IsInternal() const
{
	return mIsInternal;
}
#pragma endregion

#pragma region Set
void Datum::Set(int const & value, size_t const & index)
{
	if (DatumType::Integer != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tInt[index] = value;
}

void Datum::Set(float const & value, size_t const & index)
{
	if (DatumType::Float != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tFloat[index] = value;
}

void Datum::Set(vec4 const & value, size_t const & index)
{
	if (DatumType::Vector4 != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tVec4[index] = value;
}

void Datum::Set(mat4x4 const & value, size_t const & index)
{
	if (DatumType::Matrix4x4 != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tMat4x4[index] = value;
}

void FIEAGameEngine::Datum::Set(Scope * const & value, size_t const & index)
{
	if (DatumType::Table != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tScope[index] = value;
}

void Datum::Set(string const & value, size_t const & index)
{
	if (DatumType::String != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tString[index].~basic_string();
	mArray.tString[index] = value;
}

void Datum::Set(RTTI * const & value, size_t const & index)
{
	if (DatumType::RTTIPtr != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	mArray.tRTTIPtr[index] = value;
}
#pragma endregion

#pragma region SetFromString
void Datum::SetFromString(string const & value, size_t const & index)
{
	switch (mType)
	{
	case DatumType::Integer:
		SetFromStringTemplated<int>(value, index);
		break;
	case DatumType::Float:
		SetFromStringTemplated<float>(value, index);
		break;
	case DatumType::Vector4:
		SetFromStringTemplated<vec4>(value, index);
		break;
	case DatumType::Matrix4x4:
		SetFromStringTemplated<mat4x4>(value, index);
		break;
	case DatumType::Table:
		//TODO: Future implementation
		break;
	case DatumType::String:
		SetFromStringTemplated<string>(value, index);
		break;
	case DatumType::RTTIPtr:
		SetFromStringTemplated<RTTI*>(value, index);
		break;
	default:
		throw exception(datumTypeNotInitializedExceptionText.c_str());
		break;
	}
}
#pragma endregion

#pragma region ToString
string Datum::ToString(size_t const & index) const
{
	string result = "";
	switch (mType)
	{
	case DatumType::Integer:
		result = ToStringTemplated<int>(mArray.tInt, index);
		break;
	case DatumType::Float:
		result = ToStringTemplated<float>(mArray.tFloat, index);
		break;
	case DatumType::Vector4:
		result = ToStringTemplated<vec4>(mArray.tVec4, index);
		break;
	case DatumType::Matrix4x4:
		result = ToStringTemplated<mat4x4>(mArray.tMat4x4, index);
		break;
	case DatumType::Table:
		result = ToStringTemplated<RTTI*>(mArray.tRTTIPtr, index);
		break;
	case DatumType::String:
		result = ToStringTemplated<string>(mArray.tString, index);
		break;
	case DatumType::RTTIPtr:
		result = ToStringTemplated<RTTI*>(mArray.tRTTIPtr, index);
		break;
	default:
		throw exception(datumTypeNotInitializedExceptionText.c_str());
		break;
	}
	return result;
}
#pragma endregion

#pragma region PushBack
void Datum::PushBack(int const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::Integer);
	}
	if (mType == DatumType::Integer)
	{
		PushBackTemplated<int>(mArray.tInt, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}

void Datum::PushBack(float const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::Float);
	}
	if (mType == DatumType::Float)
	{
		PushBackTemplated<float>(mArray.tFloat, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}

void Datum::PushBack(vec4 const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::Vector4);
	}
	if (mType == DatumType::Vector4)
	{
		PushBackTemplated<vec4>(mArray.tVec4, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}

void Datum::PushBack(mat4x4 const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::Matrix4x4);
	}
	if (mType == DatumType::Matrix4x4)
	{
		PushBackTemplated<mat4x4>(mArray.tMat4x4, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}

void FIEAGameEngine::Datum::PushBack(Scope * const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::Table);
	}
	if (mType == DatumType::Table)
	{
		PushBackTemplated<Scope*>(mArray.tScope, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}

void Datum::PushBack(string const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::String);
	}
	if (mType == DatumType::String)
	{
		PushBackTemplated<string>(mArray.tString, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}


void Datum::PushBack(RTTI * const & value)
{
	//External memory check done in templated function.
	if (mType == DatumType::Unknown)
	{
		SetType(DatumType::RTTIPtr);
	}
	if (mType == DatumType::RTTIPtr)
	{
		PushBackTemplated<RTTI*>(mArray.tRTTIPtr, value);
	}
	else
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
}
#pragma endregion

#pragma region PopBack
void Datum::PopBack()
{
	//External memory check done in templated function.
	switch (mType)
	{
	case DatumType::Integer:
		PopBackTemplated<int>(mArray.tInt);
		break;
	case DatumType::Float:
		PopBackTemplated<float>(mArray.tFloat);
		break;
	case DatumType::Vector4:
		PopBackTemplated<vec4>(mArray.tVec4);
		break;
	case DatumType::Matrix4x4:
		PopBackTemplated<mat4x4>(mArray.tMat4x4);
		break;
	case DatumType::Table:
		//TODO: Future implementation
		break;
	case DatumType::String:
		PopBackTemplated<string>(mArray.tString);
		break;
	case DatumType::RTTIPtr:
		PopBackTemplated<RTTI*>(mArray.tRTTIPtr);
		break;
	default:
		throw exception(datumTypeNotInitializedExceptionText.c_str());
		break;
	}
}
#pragma endregion

#pragma region Remove
void Datum::Remove(int const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tInt, value);
}


void Datum::Remove(float const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tFloat, value);
}

void Datum::Remove(vec4 const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tVec4, value);
}

void Datum::Remove(mat4x4 const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tMat4x4, value);
}

void FIEAGameEngine::Datum::Remove(Scope* const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tScope, value);
}

void Datum::Remove(string const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tString, value);
}

void Datum::Remove(RTTI* const & value)
{
	//External memory check done in templated function.
	RemoveTemplated(mArray.tRTTIPtr, value);
}
#pragma endregion

#pragma region RemoveAt
void Datum::RemoveAt(size_t const & index)
{
	//External memory check done in templated function.
	switch (mType)
	{
	case DatumType::Integer:
		RemoveAtTemplated<int>(mArray.tInt, index);
		break;
	case DatumType::Float:
		RemoveAtTemplated<float>(mArray.tFloat, index);
		break;
	case DatumType::Vector4:
		RemoveAtTemplated<vec4>(mArray.tVec4, index);
		break;
	case DatumType::Matrix4x4:
		RemoveAtTemplated<mat4x4>(mArray.tMat4x4, index);
		break;
	case DatumType::Table:
		//TODO: Future implementation
		break;
	case DatumType::String:
		RemoveAtTemplated<string>(mArray.tString, index);
		break;
	case DatumType::RTTIPtr:
		RemoveAtTemplated<RTTI*>(mArray.tRTTIPtr, index);
		break;
	default:
		throw exception(datumTypeNotInitializedExceptionText.c_str());
		break;
	}
}
#pragma endregion

#pragma region RemoveRange
void Datum::RemoveRange(size_t const & start, size_t const & finish)
{
	//External memory check done in templated function.
	switch (mType)
	{
	case DatumType::Integer:
		RemoveRangeTemplated<int>(mArray.tInt, start, finish);
		break;
	case DatumType::Float:
		RemoveRangeTemplated<float>(mArray.tFloat, start, finish);
		break;
	case DatumType::Vector4:
		RemoveRangeTemplated<vec4>(mArray.tVec4, start, finish);
		break;
	case DatumType::Matrix4x4:
		RemoveRangeTemplated<mat4x4>(mArray.tMat4x4, start, finish);
		break;
	case DatumType::Table:
		//TODO: Future implementation
		break;
	case DatumType::String:
		RemoveRangeTemplated<string>(mArray.tString, start, finish);
		break;
	case DatumType::RTTIPtr:
		RemoveRangeTemplated<RTTI*>(mArray.tRTTIPtr, start, finish);
		break;
	default:
		throw exception(datumTypeNotInitializedExceptionText.c_str());
		break;
	}
}
#pragma endregion

#pragma region Find
pair<bool, int*>  Datum::Find(int const & searchedValue) const
{
	if (DatumType::Integer != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tInt[i] == searchedValue)
		{
			return pair<bool, int*>(true, &(mArray.tInt[i]));
		}
	}
	return pair<bool, int*>(false, nullptr);
}

pair<bool, float*> Datum::Find(float const & searchedValue) const
{
	if (DatumType::Float != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tFloat[i] == searchedValue)
		{
			return pair<bool, float*>(true, &(mArray.tFloat[i]));
		}
	}
	return pair<bool, float*>(false, nullptr);
}

pair<bool, vec4*> Datum::Find(vec4 const & searchedValue) const
{
	if (DatumType::Vector4 != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tVec4[i] == searchedValue)
		{
			return pair<bool, vec4*>(true, &(mArray.tVec4[i]));
		}
	}
	return pair<bool, vec4*>(false, nullptr);
}

pair<bool, mat4x4*> Datum::Find(mat4x4 const & searchedValue) const
{
	if (DatumType::Matrix4x4 != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tMat4x4[i] == searchedValue)
		{
			return pair<bool, mat4x4*>(true, &(mArray.tMat4x4[i]));
		}
	}
	return pair<bool, mat4x4*>(false, nullptr);
}

pair<bool, Scope**> FIEAGameEngine::Datum::Find(Scope * const & searchedValue) const
{
	if (DatumType::Table != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tScope[i] == searchedValue)
		{
			return pair<bool, Scope**>(true, &(mArray.tScope[i]));
		}
	}
	return pair<bool, Scope**>(false, nullptr);
}

pair<bool, string*> Datum::Find(string const & searchedValue) const
{
	if (DatumType::String != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tString[i] == searchedValue)
		{
			return pair<bool, string*>(true, &(mArray.tString[i]));
		}
	}
	return pair<bool, string*>(false, nullptr);
}

pair<bool, RTTI**> Datum::Find(RTTI * const & searchedValue) const
{
	if (DatumType::RTTIPtr != mType)
	{
		throw exception(operationTypeMismatchExceptionText.c_str());
	}
	for (size_t i = 0; i < mSize; i++)
	{
		if (mArray.tRTTIPtr[i] == searchedValue)
		{
			return pair<bool, RTTI**>(true, &(mArray.tRTTIPtr[i]));
		}
	}
	return pair<bool, RTTI**>(false, nullptr);
}
#pragma endregion