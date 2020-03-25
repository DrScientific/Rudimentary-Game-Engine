#include "pch.h"
#include "JsonParseMaster.h"
#include "IJsonParseHelper.h"
#include <vector>
#include <sstream>
#include <fstream>
#include "IIntegerJsonParseHelper.h"
#include "IDepthTestParseHelper.h"

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

	size_t const JsonParseMaster::SharedData::IncrementDepth()
	{
		return mDepth++;
	}

	size_t const JsonParseMaster::SharedData::DecrementDepth()
	{
		return mDepth--;
	}

	size_t const JsonParseMaster::SharedData::Depth()
	{
		return mDepth;
	}

	void JsonParseMaster::SharedData::SetJsonParseMaster(JsonParseMaster * master)
	{
		mMaster = master;
	}

	JsonParseMaster::JsonParseMaster(SharedData * sharedData):
		mSharedData(sharedData)
	{
		if (sharedData != nullptr)
		{
			mSharedData->SetJsonParseMaster(this);
		}
	}

	JsonParseMaster::JsonParseMaster(JsonParseMaster && other) :
		mParseHandlers(std::move(other.mParseHandlers)),	mCurrentFileBeingParsed(std::move(other.mCurrentFileBeingParsed)), mSharedData(other.mSharedData)
	{
		if (mSharedData != nullptr)
		{
			mSharedData->SetJsonParseMaster(this);
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
		mParseHandlers = std::move(other.mParseHandlers);
		mCurrentFileBeingParsed = std::move(other.mCurrentFileBeingParsed);
		mSharedData = std::move(other.mSharedData);

		return *this;
	}

	void JsonParseMaster::Initialize()
	{
		for (auto & i: mParseHandlers)
		{
			i.second->Initialize();
		}
	}

	owner<JsonParseMaster*> JsonParseMaster::Clone()
	{
		SharedData * clonedData = nullptr;
		if (mSharedData != nullptr)
		{
			clonedData = mSharedData->Create();
		}
		JsonParseMaster * clone = new JsonParseMaster(clonedData);

		clone->doesOwnSharedData = true;

		for (auto & i : mParseHandlers)
		{
			clone->mParseHandlers.PushBack(pair<bool, IJsonParseHelper*>(true, i.second->Create()));
		}

		return clone;
	}

	

	void JsonParseMaster::AddHelper(IJsonParseHelper & helper)
	{
		mParseHandlers.PushBack(pair<bool, IJsonParseHelper*>(false, &helper));
	}


	void JsonParseMaster::RemoveHelper(IJsonParseHelper & helper)
	{
		for (size_t i = 0; i < mParseHandlers.Size(); i++)
		{
			if (mParseHandlers[i].second == &helper)
			{
				if (mParseHandlers[i].first)
				{
					delete mParseHandlers[i].second;
				}
				mParseHandlers.RemoveAt(i);
				break;
			}
		}
	}

	bool JsonParseMaster::Parse(std::string jsonString)
	{
		if (mSharedData == nullptr)
		{
			throw exception(sharedDataUninitializedExceptionText.c_str());
		}
		Json::Value jsonValue;
		stringstream intermediateStream;
		intermediateStream << jsonString;
		intermediateStream >> jsonValue;
		return ParseMembers(jsonValue);
	}

	bool JsonParseMaster::ParseFromFile(std::string jsonFile)
	{
		if (mSharedData == nullptr)
		{
			throw exception(sharedDataUninitializedExceptionText.c_str());
		}
		Json::Value jsonValue;
		fstream intermediateStream;
		intermediateStream.open(jsonFile);
		mCurrentFileBeingParsed = jsonFile;
		intermediateStream >> jsonValue;
		intermediateStream.close();
		return ParseMembers(jsonValue);
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

	std::string JsonParseMaster::GetFileName()
	{
		return mCurrentFileBeingParsed;
	}

	JsonParseMaster::SharedData * JsonParseMaster::GetSharedData()
	{
		return mSharedData;
	}

	void JsonParseMaster::SetSharedData(SharedData * sharedData)
	{
		mSharedData = sharedData;
	}

	bool JsonParseMaster::ParseMembers(Json::Value jsonValue)
	{
		bool succeeded = true;
		std::vector<string> memberNames = jsonValue.getMemberNames();
		
		for (auto & i : memberNames)
		{
			succeeded = Parse(i, jsonValue[i], jsonValue[i].isArray());
			mSharedData->DecrementDepth();
			if (!succeeded)
			{
				break;
			}
		}
		return succeeded;
	}

	bool JsonParseMaster::Parse(std::string key, Json::Value value, bool isInArray)
	{
		mSharedData->IncrementDepth();
		for (size_t i = 0; i < mParseHandlers.Size(); i++)
		{
			if (mParseHandlers[i].second->StartHandler(mSharedData, key, value, isInArray))
			{
				if (value.type() == Json::ValueType::objectValue)
				{
					ParseMembers(value);
				}
				if (mParseHandlers[i].second->EndHandler(mSharedData, key))
				{
					return true;
				}
			}
		}
		return false;
	}

	
}