#include "pch.h"
#include "EventMessageAttributed.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(EventMessageAttributed)


	EventMessageAttributed::EventMessageAttributed(std::string subtype, World * world) : mSubtype(subtype), mWorld(world),Attributed(EventMessageAttributed::TypeIdClass())
	{
	}

	EventMessageAttributed::EventMessageAttributed(std::string subtype, World * world, Vector<pair<string const, Datum>*> auxilliaryAttributes) : mSubtype(subtype), mWorld(world), Attributed(EventMessageAttributed::TypeIdClass())
	{
		for (auto & element : auxilliaryAttributes)
		{
			Append(element->first) = element->second;
		}
	}

	EventMessageAttributed::~EventMessageAttributed()
	{
	}

	gsl::owner<Scope*> EventMessageAttributed::Clone() const
	{
		return new EventMessageAttributed(*this);
	}
	
	std::string const & EventMessageAttributed::Subtype() const
	{
		return mSubtype;
	}

	const FIEAGameEngine::Vector<Attributed::Signature> EventMessageAttributed::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{ mSubtypeKey, Datum::DatumType::String, 1,  offsetof(EventMessageAttributed, mSubtype) }
		};
	}
}