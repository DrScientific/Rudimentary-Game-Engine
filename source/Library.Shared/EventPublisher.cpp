#include "pch.h"
#include "EventPublisher.h"
#include "IEventSubscriber.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);



	EventPublisher::EventPublisher(std::set<IEventSubscriber*>* const subscribers) : mSubscribersPtr(subscribers)
	{
	}

	EventPublisher::~EventPublisher()
	{
	}

	void EventPublisher::SetTime(std::chrono::high_resolution_clock::time_point timeEnqueued, std::chrono::milliseconds delay)
	{
		mTimeEnqueued = timeEnqueued;
		mDelay = delay;
	}

	std::chrono::high_resolution_clock::time_point EventPublisher::TimeEnqueued() const
	{
		return mTimeEnqueued;
	}

	std::chrono::milliseconds EventPublisher::Delay() const
	{
		return mDelay;
	}

	bool EventPublisher::IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const
	{
		return currentTime >= mTimeEnqueued + mDelay;
	}

	void EventPublisher::Deliver()
	{
		for (auto subscriber : *mSubscribersPtr)
		{
			subscriber->Notify(*this);
		}
	}
}