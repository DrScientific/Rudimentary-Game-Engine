#include "pch.h"
#include "Event.h"
#include "EventQueue.h"
#include "AsyncEventQueueTestSubscriber.h"
#include "CppUnitTest.h"
#include "assert.h"

using namespace FIEAGameEngine;

namespace UnitTests
{
	AsyncEventQueueTestSubscriber::AsyncEventQueueTestSubscriber()
	{
		Event<EventQueue*>::Subscribe(*this);
	}


	AsyncEventQueueTestSubscriber::~AsyncEventQueueTestSubscriber()
	{
		Event<EventQueue*>::Unsubscribe(*this);
	}

	void AsyncEventQueueTestSubscriber::Notify(FIEAGameEngine::EventPublisher const & publisher)
	{
		assert(publisher.Is(Event<EventQueue*>::TypeIdClass()));
		
		EventQueue * queue = static_cast<Event<EventQueue*> const &>(publisher).GetMessage();
		std::shared_ptr<Event<EventQueue*>> newEvent = std::make_shared<Event<EventQueue*>>(queue);
		queue->Enqueue(newEvent, GameTime());
		Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(to_string(queue->Size()).c_str());
	}
}