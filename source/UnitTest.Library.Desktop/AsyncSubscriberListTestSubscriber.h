#pragma once
#include "IEventSubscriber.h"

namespace UnitTests
{

	class AsyncSubscriberListTestSubscriber :
		public FIEAGameEngine::IEventSubscriber
	{
	public:
		AsyncSubscriberListTestSubscriber();
		~AsyncSubscriberListTestSubscriber();
		virtual void Notify(class FIEAGameEngine::EventPublisher const& publisher);
	};
}