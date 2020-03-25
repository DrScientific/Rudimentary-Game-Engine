#include "pch.h"
#include "EventQueue.h"
#include "EventPublisher.h"
#include <algorithm>
#include "WorldState.h"

using namespace std;

namespace FIEAGameEngine
{

	void EventQueue::Enqueue(std::shared_ptr<EventPublisher> eventToQueue, GameTime & currentTime, std::chrono::milliseconds delay)
	{
		eventToQueue->SetTime(currentTime.CurrentTime(), delay);
		mEvents.PushBack(move(eventToQueue));
	}

	void EventQueue::Send(std::shared_ptr<EventPublisher> eventToSend)
	{
		Vector<std::shared_ptr<EventPublisher>>::Iterator iteratorInEventQueue = find(mEvents.begin(), mEvents.end(), eventToSend);
		if (iteratorInEventQueue != mEvents.end())
		{
			eventToSend->Deliver();
			mEvents.Remove(iteratorInEventQueue);
		}
	}

	void EventQueue::Update(WorldState & worldState)
	{
		GameTime * gameTime = worldState.mGameTime;

		//TODO: Pass game time to IsExpired

		Vector<std::shared_ptr<EventPublisher>>::Iterator expiredBoundary = partition(mEvents.begin(), mEvents.end(), [&gameTime](shared_ptr<EventPublisher> & i) {return !i->IsExpired(gameTime->CurrentTime()); });

		for (auto i = expiredBoundary; i != mEvents.end(); i++ )
		{
			(*i)->Deliver();
		}

		mEvents.Remove(expiredBoundary, mEvents.end());
		

		//TODO: Replace this with above

		/*for (size_t i = 0; i < mEvents.Size();)
		{
			if ((mEvents[i])->IsExpired(gameTime->CurrentTime()))
			{
				mEvents[i]->Deliver();
				mEvents.RemoveAt(i);
			}
			else
			{
				i++;
			}
		}*/
	}
	void EventQueue::Clear()
	{
		mEvents.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		return mEvents.IsEmpty();
	}

	size_t EventQueue::Size() const
	{
		return mEvents.Size();
	}
}