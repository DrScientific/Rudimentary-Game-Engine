#pragma once
#include "pch.h"
#include "IDepthTestParseHelper.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(IDepthTestParseHelper);
	RTTI_DEFINITIONS(IDepthTestParseHelper::SharedData);

	gsl::owner<JsonParseMaster::SharedData*> IDepthTestParseHelper::SharedData::Create() const
	{
		return new SharedData();
	}

	void IDepthTestParseHelper::SharedData::Initialize()
	{
		JsonParseMaster::SharedData::Initialize();
		mMaxDepth = 0;
	}
	
	gsl::owner<IJsonParseHelper*> IDepthTestParseHelper::Create() const
	{
		return new IDepthTestParseHelper();
	}
	void IDepthTestParseHelper::Initialize()
	{
		IJsonParseHelper::Initialize();
		mStartHandlerCount = 0;
		mEndHandlerCount = 0;
	}
	bool IDepthTestParseHelper::StartHandler(JsonParseMaster::SharedData const * const sharedData, std::string const & key, Json::Value jsonValue, bool isArray)
	{
		isArray;
		key;
		IDepthTestParseHelper::SharedData* depthSharedData = sharedData->As<IDepthTestParseHelper::SharedData>();
		if (depthSharedData == nullptr)
		{
			return false;
		}

		++mStartHandlerCount;

		return true;
	}
	bool IDepthTestParseHelper::EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key)
	{
		key;

		IDepthTestParseHelper::SharedData* depthSharedData = sharedData->As<IDepthTestParseHelper::SharedData>();

		++mEndHandlerCount;

		if (depthSharedData->Depth() > depthSharedData->mMaxDepth)
		{
			depthSharedData->mMaxDepth = depthSharedData->Depth();
		}

		return true;
	}
}