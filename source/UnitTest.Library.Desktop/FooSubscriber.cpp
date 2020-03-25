#include "pch.h"
#include "FooSubscriber.h"
#include "Event.h"
#include "Foo.h"

using namespace FIEAGameEngine;

namespace UnitTests
{

	FooSubscriber::FooSubscriber(int data) : mData(data)
	{
		Event<Foo>::Subscribe(this);
	}

	FooSubscriber::~FooSubscriber()
	{
		Event<Foo>::Unsubscribe(this);
	}

	void FooSubscriber::Notify(EventPublisher const & publisher)
	{
		assert(publisher.Is(Event<Foo>::TypeIdClass()));
		Event<Foo> const * fooEvent = static_cast<Event<Foo> const *>(&publisher);
		mData = fooEvent->GetMessage().Data();
	}

	
}

