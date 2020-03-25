#include "pch.h"
#include "FooSubscriber.h"
#include "Event.h"
#include "Foo.h"

using namespace FIEAGameEngine;
using namespace std;

namespace UnitTests
{

	FooSubscriber::FooSubscriber(int id, int data) : mID(id), mData(data)
	{
		Event<Foo>::Subscribe(*this);
	}

	FooSubscriber::~FooSubscriber()
	{
		Event<Foo>::Unsubscribe(*this);
	}

	void FooSubscriber::Notify(EventPublisher const & publisher)
	{
		lock_guard<mutex> lock(mMutex);
		assert(publisher.Is(Event<Foo>::TypeIdClass()));
		Event<Foo> const * fooEvent = static_cast<Event<Foo> const *>(&publisher);
		mData = fooEvent->GetMessage().Data();
	}

	
}

