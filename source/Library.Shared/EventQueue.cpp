#include "pch.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include <algorithm>
#include "WorldState.h"
#include "assert.h"

using namespace std;

namespace FIEAGameEngine
{

	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> eventToQueue, GameTime const& currentTime, std::chrono::milliseconds delay)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		eventToQueue->SetTime(currentTime.CurrentTime(), delay);
		mPendingEvents.PushBack(move(eventToQueue));
	}

	void EventQueue::Send(std::shared_ptr<EventPublisher> eventToSend)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		Vector<std::shared_ptr<EventPublisher>>::Iterator iteratorInEventQueue = find(mEvents.begin(), mEvents.end(), eventToSend);
		if (iteratorInEventQueue != mEvents.end())
		{
			eventToSend->Deliver();
			mEvents.Remove(iteratorInEventQueue);
		}
		else
		{
			Vector<std::shared_ptr<EventPublisher>>::Iterator iteratorInPendingEventQueue = find(mPendingEvents.begin(), mPendingEvents.end(), eventToSend);
			if (iteratorInPendingEventQueue != mPendingEvents.end())
			{
				eventToSend->Deliver();
				mPendingEvents.Remove(iteratorInPendingEventQueue);
			}
		}
	}

	void EventQueue::Update(WorldState & worldState)
	{
		GameTime * gameTime = worldState.mGameTime;

		std::move(mPendingEvents.begin(), mPendingEvents.end(), std::back_inserter(mEvents));

		mPendingEvents.Clear();

		Vector<std::shared_ptr<EventPublisher>>::Iterator expiredBoundary = partition(mEvents.begin(), mEvents.end(), [&gameTime](shared_ptr<EventPublisher> & i) {return !i->IsExpired(gameTime->CurrentTime()); });
		
		//note this is an std::vector
		vector<future<void>> futures;
		{
			lock_guard<recursive_mutex> lock(mMutex);

			for (auto i = expiredBoundary; i != mEvents.end(); i++)
			{
				auto& expiredEvent = *i;
				futures.emplace_back(std::async(launch::async, [&expiredEvent]
					{
						expiredEvent->Deliver();
					}));
			}
		}
		for (auto& i : futures)
		{
			i.get();
		}

		mEvents.Remove(expiredBoundary, mEvents.end());
	}
	void EventQueue::Clear()
	{
		lock_guard<recursive_mutex> lock(mMutex);
		mEvents.Clear();
		mPendingEvents.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		lock_guard<recursive_mutex> lock(mMutex);
		return mEvents.IsEmpty() && mPendingEvents.IsEmpty();
	}

	size_t EventQueue::Size() const
	{
		lock_guard<recursive_mutex> lock(mMutex);
		return mEvents.Size() + mPendingEvents.Size();
	}
}