#include "pch.h"
#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
#include "EventPublisher.h"
#include "Event.h"
#include "World.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed)


	ReactionAttributed::ReactionAttributed(std::string name, std::string subtype) : Reaction(ReactionAttributed::TypeIdClass(), name), mSubtype(subtype)
	{
		Event<EventMessageAttributed>::Subscribe(this);
	}


	ReactionAttributed::~ReactionAttributed()
	{
		Event<EventMessageAttributed>::Unsubscribe(this);
	}

	gsl::owner<Scope*> ReactionAttributed::Clone() const
	{
		return new ReactionAttributed(*this);
	}

	void ReactionAttributed::Notify(FIEAGameEngine::EventPublisher const & publisher)
	{
		assert(publisher.Is(Event<EventMessageAttributed>::TypeIdClass()));
		Event<EventMessageAttributed> const * attributedEvent = static_cast<Event<EventMessageAttributed> const *>(&publisher);

		EventMessageAttributed const & message = attributedEvent->GetMessage();

		if (message.Subtype() == mSubtype)
		{
			mWorld = message.mWorld;
			Vector<pair<string const, Datum>*> parameters = message.AuxiliaryAttributes();
			Datum & actions = operator[](mActionsIndex);
			for (size_t i = 0; i < actions.Size(); i++)
			{
				for (size_t j = 0; j < parameters.Size(); j++)
				{
					Action & action = *static_cast<Action*>(&actions[i]);
					Datum * actionAttribute = action.Find(parameters[j]->first);
					if (actionAttribute != nullptr)
					{
						actionAttribute->StoragePreservedAssignment(parameters[j]->second);
					}
				}
				
			}
			ActionList::Update(mWorld->mState);
		}
	}

	const Vector<Attributed::Signature> ReactionAttributed::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{mNameKey, Datum::DatumType::String, 1, offsetof(ReactionAttributed, mName) },
			{ mActionsKey, Datum::DatumType::Scope, 0, 0 },
			{ mSubtypeKey, Datum::DatumType::String, 1,  offsetof(ReactionAttributed, mSubtype) }
		};
	}
}