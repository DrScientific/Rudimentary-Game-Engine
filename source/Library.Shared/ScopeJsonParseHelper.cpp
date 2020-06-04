#include "pch.h"
#include "ScopeJsonParseHelper.h"
#include "Scope.h"
#include "Factory.h"
#include "json/json.h"

using namespace std;
using namespace glm;


namespace FIEAGameEngine
{

	RTTI_DEFINITIONS(ScopeJsonParseHelper);
	RTTI_DEFINITIONS(ScopeJsonParseHelper::ScopeSharedData);

	UnorderedMap<string const, Datum::DatumType> const ScopeJsonParseHelper::stringToTypeMap = {
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

	ScopeJsonParseHelper::StackFrame::StackFrame(std::string const key, Datum::DatumType type, std::string scopeClass, Scope * contextFrame) :
		Key(key), Type(type), Class(scopeClass), ContextFrame(contextFrame)
	{
	}

	ScopeJsonParseHelper::ScopeSharedData::ScopeSharedData(shared_ptr<Scope> & scope)
		:rootScope(scope)
	{
	}

	ScopeJsonParseHelper::ScopeSharedData::ScopeSharedData(shared_ptr<Scope> && scope)
		: rootScope(std::move(scope))
	{
	}

	gsl::owner<JsonParseMaster::SharedData*> ScopeJsonParseHelper::ScopeSharedData::Create() const
	{
		return new ScopeJsonParseHelper::ScopeSharedData(shared_ptr<Scope>(GetScope().Clone()));
	}

	Scope & ScopeJsonParseHelper::ScopeSharedData::GetScope()
	{
		return *(rootScope.get());
	}

	Scope const& ScopeJsonParseHelper::ScopeSharedData::GetScope() const
	{
		return *(rootScope.get());
	}

	bool ScopeJsonParseHelper::StartHandler(JsonParseMaster::SharedData  * const sharedData, string const& key, Json::Value const& jsonValue, bool const& isArrayElement, size_t const& index)
	{
		ScopeJsonParseHelper::ScopeSharedData * scopeSharedData = sharedData->As< ScopeJsonParseHelper::ScopeSharedData>();

		bool result = true;

		if (scopeSharedData == nullptr || key.empty())
		{
			result = false;
		}
		else if (key == "class")
		{
			StackFrame & top = stack.Top();
			top.Class = jsonValue.asString();
			result = true;
		}
		else if (key == "type")
		{
			StackFrame & top = stack.Top();
			Datum::DatumType datumType = stringToTypeMap.At(jsonValue.asString());
			top.Type = top.ContextFrame->Append(top.Key).SetType(datumType);
			result = true;
		}
		else if (key == "value")
		{
			StackFrame & top = stack.Top();
			if ((*(top.ContextFrame))[top.Key].IsInternal())
			{
				if (jsonValue.isObject())
				{
					Scope * newScope = nullptr;
					if (!top.Class.empty() && top.Type != Datum::DatumType::Scope)
					{
						throw exception(classMustBeTypeScopeText.c_str());
					}
					else if (!top.Class.empty())
					{
						newScope = Factory<Scope>::Create(top.Class);
					}
					else
					{
						newScope = new Scope();
					}

					top.ContextFrame->Adopt(*newScope, top.Key);

					if (isArrayElement)
					{
						//stack.Push(StackFrame(key, Datum::DatumType::Scope, &top.ContextFrame->AppendScope(top.Key)));
						stack.Push(StackFrame(key, Datum::DatumType::Scope, top.Class, newScope));
					}
					else
					{
						//top.ContextFrame = &top.ContextFrame->AppendScope(top.Key);
						top.ContextFrame = newScope;
					}
					result = true;
				}
				else
				{
					Datum & newDatum = *top.ContextFrame->Find(top.Key);
					if (jsonValue.isInt())
					{
						newDatum.PushBack(jsonValue.asInt());
						result = true;
					}
					else if (jsonValue.isDouble())
					{
						newDatum.PushBack(jsonValue.asFloat());
						result = true;
					}
					else if (jsonValue.isString())
					{
						newDatum.PushBackFromString(jsonValue.asString());
						result = true;
					}
					else
					{
						result = false;
					}
				}
				
			}
			else
			{
				Datum & newDatum = *top.ContextFrame->Find(top.Key);
				if (jsonValue.isInt())
				{
					index;
					newDatum.Set(jsonValue.asInt(), index);
					result = true;
				}
				else if (jsonValue.isDouble())
				{
					newDatum.Set(jsonValue.asFloat(), index);
					result = true;
				}
				else if (jsonValue.isString())
				{
					newDatum.Set(jsonValue.asString(), index);
					result = true;
				}
				else
				{
					result = false;
				}
			}
		}
		else
		{
			Scope * contextFrame = stack.IsEmpty() ? &scopeSharedData->GetScope() : stack.Top().ContextFrame;
			stack.Push(StackFrame(key, Datum::DatumType::Unknown, contextFrame));
		}

		return result;
	}

	bool ScopeJsonParseHelper::EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const& key)
	{
		if (sharedData->As< ScopeJsonParseHelper::ScopeSharedData>() == nullptr)
		{
			return false;
		}

		StackFrame top = stack.Top();

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