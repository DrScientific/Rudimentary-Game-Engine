#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "EventPublisher.h"
#include "IEventSubscriber.h"
#include "EventQueue.h"
#include "Event.h"
#include "Foo.h"
#include "FooSubscriber.h"
#include "World.h"
#include "Sector.h"
#include "FooEntity.h"
#include "FooEntity.h"
#include "GameClock.h"
#include "AsyncSubscriberListTestSubscriber.h"
#include "AsyncEventQueueTestSubscriber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AsyncEventTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				_CrtDumpMemoryLeaks();
				Assert::Fail(L"Memory leak detected!\nIf a static object is dynamically allocating memory this may be a false positive.");
			}
#endif
		}

		TEST_METHOD(AsyncSubscribeUnsubscribeTest)
		{
			GameClock clock;
			GameTime time;
			EventQueue eventQueue;
			World world(&time, &eventQueue);

			clock.UpdateGameTime(*world.mState.mGameTime);

			AsyncSubscriberListTestSubscriber subscribers[10000];
			
			clock.UpdateGameTime(*world.mState.mGameTime);

			while (Event<Foo>::HasSubscribers())
			{
				if (world.mEventQueue->IsEmpty())
				{
					world.mEventQueue->Enqueue(make_shared<Event<Foo>>(), *world.mState.mGameTime);
				}
				clock.UpdateGameTime(*world.mState.mGameTime);
				world.Update();
			}
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AsyncEventTest::sStartMemState;
}