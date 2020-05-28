#pragma once
#include "IEventSubscriber.h"

namespace UnitTests
{
	class AsyncEventQueueTestSubscriber :
		public FIEAGameEngine::IEventSubscriber
	{
	public:
		AsyncEventQueueTestSubscriber();
		~AsyncEventQueueTestSubscriber();
		virtual void Notify(class FIEAGameEngine::EventPublisher const& publisher);
	};
}