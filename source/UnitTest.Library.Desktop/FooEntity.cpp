#include "pch.h"
#include "FooEntity.h"
#include "Event.h"
#include "Foo.h"

using namespace FIEAGameEngine;

namespace UnitTests
{
	FooEntity::FooEntity()
	{
		Event<Foo>::Subscribe(*this);
	}

	FooEntity::~FooEntity()
	{
		Event<Foo>::Unsubscribe(*this);
	}

	void FooEntity::Notify(FIEAGameEngine::EventPublisher const& publisher)
	{
		assert(publisher.Is(Event<Foo>::TypeIdClass()));
		Event<Foo> const* fooEvent = static_cast<Event<Foo> const*>(&publisher);
		mData = fooEvent->GetMessage().Data();
	}
}