#include "pch.h"
#include "Event.h"
#include "Foo.h"
#include "AsyncSubscriberListTestSubscriber.h"
#include <random>

using namespace FIEAGameEngine;

namespace UnitTests
{

	AsyncSubscriberListTestSubscriber::AsyncSubscriberListTestSubscriber()
	{
		Event<Foo>::Subscribe(*this);
	}


	AsyncSubscriberListTestSubscriber::~AsyncSubscriberListTestSubscriber()
	{
		Event<Foo>::Unsubscribe(*this);
	}

	void AsyncSubscriberListTestSubscriber::Notify(FIEAGameEngine::EventPublisher const &)
	{
		if (rand() % 10 == 0)
		{
			Event<Foo>::Unsubscribe(*this);
		}
		else
		{
			Event<Foo>::Unsubscribe(*this);
			Event<Foo>::Subscribe(*this);
		}
	}
}