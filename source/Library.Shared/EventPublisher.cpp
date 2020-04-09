#include "pch.h"
#include "EventPublisher.h"
#include "IEventSubscriber.h"
#include <thread>
#include <future>
#include "Assert.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(EventPublisher);



	EventPublisher::EventPublisher(std::set<IEventSubscriber*>* const subscribers, std::recursive_mutex * const lock) : mSubscribersPtr(subscribers), mMutexPtr(lock), mDelay(0)
	{
	}

	void EventPublisher::SetTime(std::chrono::high_resolution_clock::time_point timeEnqueued, std::chrono::milliseconds delay)
	{
		lock_guard<recursive_mutex> lock(*mMutexPtr);
		mTimeEnqueued = timeEnqueued;
		mDelay = delay;
	}

	std::chrono::high_resolution_clock::time_point EventPublisher::TimeEnqueued() const
	{
		lock_guard<recursive_mutex> lock(*mMutexPtr);
		return mTimeEnqueued;
	}

	std::chrono::milliseconds EventPublisher::Delay() const
	{
		return mDelay;
	}

	bool EventPublisher::IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const
	{
		lock_guard<recursive_mutex> lock(*mMutexPtr);
		return currentTime >= mTimeEnqueued + mDelay;
	}

	void EventPublisher::Deliver()
	{
		vector<future<void>> futures;
		{
			lock_guard<recursive_mutex> lock(*mMutexPtr);

			for (auto & subscriber : *mSubscribersPtr)
			{
				futures.emplace_back(std::async(launch::async, [&subscriber, this]
				{
					subscriber->Notify(*this);
				}));
			}
		}
		for (auto & i : futures)
		{
			i.get();
		}
	}
}
