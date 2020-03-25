#include "pch.h"
#include "IIntegerJsonParseHelper.h"



namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(IIntegerJsonParseHelper);
	RTTI_DEFINITIONS(IIntegerJsonParseHelper::SharedData);

	gsl::owner<JsonParseMaster::SharedData*> IIntegerJsonParseHelper::SharedData::Create() const
	{
		return new SharedData();
	}

	void IIntegerJsonParseHelper::SharedData::Initialize()
	{
		JsonParseMaster::SharedData::Initialize();
	}

	gsl::owner<IJsonParseHelper*> IIntegerJsonParseHelper::Create() const
	{
		return new IIntegerJsonParseHelper();
	}

	void IIntegerJsonParseHelper::Initialize()
	{
		IJsonParseHelper::Initialize();
	}
	
	bool IIntegerJsonParseHelper::StartHandler(JsonParseMaster::SharedData const * const sharedData, std::string const & key, Json::Value jsonValue, bool isArray)
	{
		isArray;
		if ((key != "integer" && key != "Integer") || !jsonValue.isInt() || sharedData->As< IIntegerJsonParseHelper::SharedData>() == nullptr)
		{
			return false;
		}

		tempInt = jsonValue.asInt();

		return true;
	}
	bool IIntegerJsonParseHelper::EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key)
	{
		key;
		sharedData->As< IIntegerJsonParseHelper::SharedData>()->parsedInt = tempInt;
		return true;
	}
	

}