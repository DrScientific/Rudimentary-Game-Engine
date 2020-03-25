#include "pch.h"
#include "JsonParseMaster.h"
#include "IJsonParseHelper.h"
#include <vector>
#include <sstream>
#include <fstream>
#include "json/json.h"

using namespace std;
using namespace gsl;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(JsonParseMaster);
	RTTI_DEFINITIONS(JsonParseMaster::SharedData);

	JsonParseMaster::SharedData::~SharedData()
	{

	}

	JsonParseMaster * JsonParseMaster::SharedData::GetJsonParseMaster()
	{
		return mMaster;
	}

	size_t JsonParseMaster::SharedData::IncrementDepth()
	{
		return ++mDepth;
	}

	size_t JsonParseMaster::SharedData::DecrementDepth()
	{
		if (mDepth > 0)
		{
			return --mDepth;
		}
		return mDepth;
	}

	size_t JsonParseMaster::SharedData::Depth() const
	{
		return mDepth;
	}

	void JsonParseMaster::SharedData::SetJsonParseMaster(JsonParseMaster & master)
	{
		mMaster = &master;
	}

	JsonParseMaster::JsonParseMaster(SharedData & sharedData):
		mSharedData(&sharedData)
	{
		mSharedData->SetJsonParseMaster(*this);
	}

	JsonParseMaster::JsonParseMaster(JsonParseMaster && other) :
		mParseHandlers(std::move(other.mParseHandlers)),	mCurrentFileBeingParsed(std::move(other.mCurrentFileBeingParsed)), mSharedData(other.mSharedData), doesOwnSharedData(other.doesOwnSharedData)
	{
		other.mSharedData = nullptr;
		other.doesOwnSharedData = false;
		if (mSharedData != nullptr)
		{
			mSharedData->SetJsonParseMaster(*this);
		}
	}

	JsonParseMaster::~JsonParseMaster()
	{
		for (auto & i : mParseHandlers)
		{
			if (i.first)
			{
				delete i.second;
			}
		}

		if (doesOwnSharedData)
		{
			delete mSharedData;
		}
	}

	JsonParseMaster & JsonParseMaster::operator=(JsonParseMaster && other)
	{
		
		if (this != &other)
		{
			//Should be made into clear functions
			for (auto & i : mParseHandlers)
			{
				if (i.first)
				{
					delete i.second;
				}
			}

			if (doesOwnSharedData)
			{
				delete mSharedData;
			}
			//^
			mParseHandlers = std::move(other.mParseHandlers);
			mCurrentFileBeingParsed = std::move(other.mCurrentFileBeingParsed);
			mSharedData = std::move(other.mSharedData);
			other.mSharedData = nullptr;
			other.doesOwnSharedData = false;
		}
		return *this;
	}

	void JsonParseMaster::Initialize()
	{
		mSharedData->Initialize();
		
		for (auto & i: mParseHandlers)
		{
			i.second->Initialize();
		}

		mCurrentFileBeingParsed.clear();
	}

	owner<JsonParseMaster*> JsonParseMaster::Clone()
	{
		SharedData * clonedData = nullptr;
		if (mSharedData != nullptr)
		{
			clonedData = mSharedData->Create();
		}
		JsonParseMaster * clone = new JsonParseMaster(*clonedData);

		clone->doesOwnSharedData = true;

		for (auto & i : mParseHandlers)
		{
			clone->mParseHandlers.PushBack(pair<bool, IJsonParseHelper*>(true, i.second->Create()));
		}

		return clone;
	}

	

	void JsonParseMaster::AddHelper(IJsonParseHelper & helper)
	{
		bool alreadyExists = false;
		alreadyExists |= mParseHandlers.Find(pair<bool, IJsonParseHelper*>(true, &helper)) != mParseHandlers.end() || mParseHandlers.Find(pair<bool, IJsonParseHelper*>(false, &helper)) != mParseHandlers.end();
		if (!alreadyExists)
		{
			mParseHandlers.PushBack(pair<bool, IJsonParseHelper*>(false, &helper));
		}
	}


	void JsonParseMaster::RemoveHelper(IJsonParseHelper & helper)
	{
		for (size_t i = 0; i < mParseHandlers.Size(); i++)
		{
			pair<bool , IJsonParseHelper*> currentHelper = mParseHandlers[i];
			if (currentHelper.second == &helper)
			{
				if (currentHelper.first)
				{
					delete currentHelper.second;
				}
				mParseHandlers.RemoveAt(i);
				break;
			}
		}
	}

	bool JsonParseMaster::Parse(std::string const & jsonString)
	{
		istringstream intermediateStream(jsonString);
		return Parse(intermediateStream);
	}

	bool JsonParseMaster::ParseFromFile(std::string const & jsonFile)
	{
		mCurrentFileBeingParsed = jsonFile;
		fstream intermediateStream(jsonFile);
		return Parse(intermediateStream);
	}

	bool JsonParseMaster::Parse(std::istream & jsonIStream)
	{
		if (mSharedData == nullptr)
		{
			throw exception(sharedDataUninitializedExceptionText.c_str());
		}
		Json::Value jsonValue;
		jsonIStream >> jsonValue;
		return ParseMembers(jsonValue);
	}

	std::string const & JsonParseMaster::GetFileName() const
	{
		return mCurrentFileBeingParsed;
	}

	JsonParseMaster::SharedData * JsonParseMaster::GetSharedData()
	{
		return mSharedData;
	}

	void JsonParseMaster::SetSharedData(SharedData & sharedData)
	{
		mSharedData = &sharedData;
	}

	bool JsonParseMaster::ParseMembers(Json::Value const & jsonValue)
	{
		std::vector<string> memberNames = jsonValue.getMemberNames();

		for (auto & i : memberNames)
		{
			if (!Parse(i, jsonValue[i], jsonValue[i].isArray(), 0))
			{
				return false;
			}
		}
		return true;
	}

	bool JsonParseMaster::Parse(std::string const & key, Json::Value const & value, bool const & isArrayElement, size_t const & index)
	{
		bool result = false;
		if (value.isObject())
		{
			mSharedData->IncrementDepth();
			for (auto const & pair : mParseHandlers)
			{
				IJsonParseHelper* handler = pair.second;
				if (handler->StartHandler(mSharedData, key, value, isArrayElement, index))
				{
					result = ParseMembers(value);
					if (!handler->EndHandler(mSharedData, key))
					{
						throw exception(startHandlerFailedToEndException.c_str());
					}
					break;
				}
			}
			mSharedData->DecrementDepth();
		}
		else if (value.isArray())
		{
			result = true;
			size_t i = 0;
			for (auto const & element : value)
			{
				result |= Parse(key, element, true, i);
				++i;
			}
		}
		else
		{
			mSharedData->IncrementDepth();
			for (auto const & pair : mParseHandlers)
			{
				IJsonParseHelper* handler = pair.second;
				if (handler->StartHandler(mSharedData, key, value, isArrayElement, index))
				{
					if (!handler->EndHandler(mSharedData, key))
					{
						throw exception(startHandlerFailedToEndException.c_str());
					}
					result = true;
					break;
				}
			}
			mSharedData->DecrementDepth();
		}
		return result;
	}

	
}