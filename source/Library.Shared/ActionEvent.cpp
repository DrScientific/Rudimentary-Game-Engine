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


	ActionEvent::~ActionEvent()
	{
	}

	gsl::owner<ActionEvent*> ActionEvent::Clone() const
	{
		return new ActionEvent(*this);
	}

	void ActionEvent::Update(WorldState & worldState)
	{
		shared_ptr<Event<EventMessageAttributed>> attributedEvent = make_shared<Event<EventMessageAttributed>>(EventMessageAttributed(mSubtype, worldState.mWorld, AuxiliaryAttributes()));
		worldState.mWorld->mEventQueue->Enqueue(attributedEvent, *worldState.mGameTime, std::chrono::milliseconds(mDelay));
	}

	const FIEAGameEngine::Vector<Attributed::Signature> ActionEvent::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{mNameKey, Datum::DatumType::String, 1, offsetof(ActionEvent, mName) },
			{ mSubtypeKey, Datum::DatumType::String, 1, offsetof(ActionEvent, mSubtype) },
			{ mDelayKey, Datum::DatumType::Integer, 1,  offsetof(ActionEvent, mDelay) }
		};
	}
}