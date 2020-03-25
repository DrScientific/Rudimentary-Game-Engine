#include "pch.h"
#include "ScopeJsonParseHelper.h"
#include "Scope.h"
#include "json/json.h"

using namespace std;
using namespace glm;


namespace FIEAGameEngine
{

	RTTI_DEFINITIONS(ScopeJsonParseHelper);
	RTTI_DEFINITIONS(ScopeJsonParseHelper::SharedData);

	HashMap<string const, Datum::DatumType> const ScopeJsonParseHelper::stringToTypeMap = {
		{"integer", Datum::DatumType::Integer}, {"Integer", Datum::DatumType::Integer},
		{"float", Datum::DatumType::Float}, {"Float", Datum::DatumType::Float},
		{"vector", Datum::DatumType::Vector4}, {"Vector", Datum::DatumType::Vector4}, {"vec4", Datum::DatumType::Vector4}, {"Vec4", Datum::DatumType::Vector4},
		{"matrix", Datum::DatumType::Matrix4x4}, {"Matrix", Datum::DatumType::Matrix4x4}, {"mat4x4", Datum::DatumType::Matrix4x4}, {"Mat4x4", Datum::DatumType::Matrix4x4}, {"mat4", Datum::DatumType::Matrix4x4}, {"Mat4", Datum::DatumType::Matrix4x4},
		{"scope", Datum::DatumType::Scope}, {"Scope", Datum::DatumType::Scope}, {"table", Datum::DatumType::Scope}, {"Table", Datum::DatumType::Scope},
		{"string", Datum::DatumType::String}, {"String", Datum::DatumType::String},
		{"rtti", Datum::DatumType::RTTIPtr}, {"Rtti", Datum::DatumType::RTTIPtr}, {"RTTI", Datum::DatumType::RTTIPtr},
	};

	ScopeJsonParseHelper::StackFrame::StackFrame(string const key, Datum::DatumType type, Scope * contextFrame) :
		Key(key), Type(type), ContextFrame(contextFrame)
	{
	}

	ScopeJsonParseHelper::SharedData::SharedData(shared_ptr<Scope> scope)
		:rootScope(scope)
	{
	}

	gsl::owner<JsonParseMaster::SharedData*> ScopeJsonParseHelper::SharedData::Create() const
	{
		return new ScopeJsonParseHelper::SharedData(make_shared<Scope>(GetScope().Clone()));
	}

	Scope & ScopeJsonParseHelper::SharedData::GetScope()
	{
		return *rootScope;
	}

	Scope const & ScopeJsonParseHelper::SharedData::GetScope() const
	{
		return *rootScope;
	}

	bool ScopeJsonParseHelper::StartHandler(JsonParseMaster::SharedData  * const sharedData, string const & key, Json::Value const & jsonValue, bool const & isArrayElement, size_t const & index)
	{
		isArrayElement;
		ScopeJsonParseHelper::SharedData * scopeSharedData = sharedData->As< ScopeJsonParseHelper::SharedData>();

		if (scopeSharedData == nullptr || key.empty())
		{
			return false;
		}

		if (scopeSharedData->Depth() % 2 == 1)
		{
			if (jsonValue.isObject())
			{
				if (stack.IsEmpty())
				{
					StackFrame baseFrame("", Datum::DatumType::Scope, &scopeSharedData->GetScope());
					stack.Push(baseFrame);
				}
				StackFrame currentFrame(key, Datum::DatumType::Unknown, stack.Top().ContextFrame);
				stack.Push(currentFrame);
				stack.Top().ContextFrame->Append(stack.Top().Key);
				return true;
			}
		}
		else
		{
			if (key == "type")
			{
				Datum::DatumType datumType = stringToTypeMap.At(jsonValue.asString());
				stack.Top().ContextFrame->Find(stack.Top().Key)->SetType(datumType);
				stack.Top().Type = datumType;
				return true;
			}
			else if (key == "value")
			{
				StackFrame test = stack.Top();
				test;
				if ((*(stack.Top().ContextFrame))[stack.Top().Key].IsInternal())
				{
					if (jsonValue.isObject())
					{
						if (isArrayElement)
						{
							stack.Push(StackFrame(key, Datum::DatumType::Scope, &stack.Top().ContextFrame->AppendScope(stack.Top().Key)));
						}
						else
						{
							stack.Top().ContextFrame = &stack.Top().ContextFrame->AppendScope(stack.Top().Key);
						}
						return true;
					}
					if (jsonValue.isInt())
					{
						stack.Top().ContextFrame->Append(stack.Top().Key).PushBack(jsonValue.asInt());
						return true;
					}
					else if (jsonValue.isDouble())
					{
						stack.Top().ContextFrame->Append(stack.Top().Key).PushBack(jsonValue.asFloat());
						return true;
					}
					else if (jsonValue.isString())
					{
						stack.Top().ContextFrame->Append(stack.Top().Key).PushBackFromString(jsonValue.asString());
						return true;
					}
				}
				else
				{
					if (jsonValue.isInt())
					{
						stack.Top().ContextFrame->Append(stack.Top().Key).Set(jsonValue.asInt(), index);
						return true;
					}
					else if (jsonValue.isDouble())
					{
						stack.Top().ContextFrame->Append(stack.Top().Key).Set(jsonValue.asFloat(), index);
						return true;
					}
					else if (jsonValue.isString())
					{
						stack.Top().ContextFrame->Append(stack.Top().Key).SetFromString(jsonValue.asString(), index);
						return true;
					}
				}
			}
		}

		return false;
	}

	bool ScopeJsonParseHelper::EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key)
	{
		if (sharedData->As< ScopeJsonParseHelper::SharedData>() == nullptr)
		{
			return false;
		}

		if (stack.Top().Key == key)
		{
			stack.Pop();
		}

		return true;
	}

	gsl::owner<IJsonParseHelper*> ScopeJsonParseHelper::Create() const
	{
		return new ScopeJsonParseHelper();
	}
}