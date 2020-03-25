#include "pch.h"
#include "ActionEvent.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "WorldState.h"
#include "World.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionEvent)


	ActionEvent::ActionEvent(std::string const & name, int const & delay) : Action(ActionEvent::TypeIdClass(), name), mDelay(delay)
	{
	}

	gsl::owner<Scope*> ActionEvent::Clone() const
	{
		return new ActionEvent(*this);
	}

	void ActionEvent::Update(WorldState & worldState)
	{
		shared_ptr<Event<EventMessageAttributed>> attributedEvent = make_shared<Event<EventMessageAttributed>>(EventMessageAttributed(mSubtype, worldState.mWorld, AuxiliaryAttributes()));
		worldState.mWorld->mEventQueue.Enqueue(attributedEvent, *worldState.mGameTime, std::chrono::milliseconds(mDelay));
		//TODO: Add functionality for actions to delete themselves and determine how to deal with memory ownership issue. Maybe clear should be called here.
		//Clear();
	}

	const FIEAGameEngine::Vector<Attributed::Signature> ActionEvent::Signatures()
	{
		return Action::Signatures() + Vector<Attributed::Signature>
		{
			{ mSubtypeKey, Datum::DatumType::String, 1, offsetof(ActionEvent, mSubtype) },
			{ mDelayKey, Datum::DatumType::Integer, 1,  offsetof(ActionEvent, mDelay) }
		};
	}
}