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


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
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
		
		TEST_METHOD(RTTITest)
		{
			Event<Foo> fooEvent;

			Assert::IsTrue(fooEvent.Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(fooEvent.Is(EventPublisher::TypeIdClass()));
			Assert::IsTrue(fooEvent.ToString() == "Event");
		}
		
		TEST_METHOD(EventTimeEnqueuedAndDelayTest)
		{
			Event<Foo> fooEvent(10);

			Assert::IsTrue(fooEvent.TimeEnqueued() == std::chrono::high_resolution_clock::time_point());

			Assert::IsTrue(fooEvent.Delay() == std::chrono::milliseconds());

			GameTime time;

			std::chrono::milliseconds testDelay(1000);

			std::chrono::high_resolution_clock::time_point testTime(testDelay);

			time.SetCurrentTime(testTime);

			fooEvent.SetTime(time.CurrentTime(), testDelay);

			Assert::IsTrue(fooEvent.TimeEnqueued() == testTime);

			Assert::IsTrue(fooEvent.Delay() == testDelay);
		}

		TEST_METHOD(EventDeliverTest)
		{
			Event<Foo> fooEvent(10);

			FooSubscriber subscriber1(1,1);

			FooSubscriber subscriber2(2, 2);
			
			FooSubscriber subscriber3(3, 3);

			Assert::IsTrue(subscriber1.mData == 1);

			Assert::IsTrue(subscriber2.mData == 2);

			Assert::IsTrue(subscriber3.mData == 3);

			fooEvent.Deliver();

			Assert::IsTrue(subscriber1.mData == 10);

			Assert::IsTrue(subscriber2.mData == 10);

			Assert::IsTrue(subscriber3.mData == 10);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(EventSendTest)
		{
			GameClock clock;

			SectorFactory sectorFactory;
			FooEntityFactory fooEntityFactory;

			GameTime time;
			EventQueue eventQueue;
			World world(&time, &eventQueue);

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();

			FooEntity & fooEntityA1 = static_cast<FooEntity &>(sectorA.CreateEntity("FooEntity A1", "FooEntity"));

			Assert::IsTrue(fooEntityA1.mData == 0);

			shared_ptr<Event<Foo>> fooPtr = make_shared<Event<Foo>>(10);

			world.mEventQueue->Enqueue(fooPtr, *world.mState.mGameTime, std::chrono::milliseconds(1000));

			world.mEventQueue->Send(fooPtr);

			Assert::IsTrue(fooEntityA1.mData == 10);
		}

		TEST_METHOD(EventQueueUpdateTest)
		{
			GameClock clock;

			SectorFactory sectorFactory;
			FooEntityFactory fooEntityFactory;

			GameTime time;
			EventQueue eventQueue;
			World world(&time, &eventQueue);

			clock.UpdateGameTime(*world.mState.mGameTime);

			world.mEventQueue->Enqueue(make_shared<Event<Foo>>(10), *world.mState.mGameTime, std::chrono::milliseconds(1000));

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();
			

			FooEntity & fooEntityA1 = static_cast<FooEntity &>(sectorA.CreateEntity("FooEntity A1", "FooEntity"));

			clock.UpdateGameTime(*world.mState.mGameTime);

			while (fooEntityA1.mData != 10)
			{
				clock.UpdateGameTime(*world.mState.mGameTime);
				world.Update();
			}

			Assert::IsTrue(fooEntityA1.mData == 10);
		}

		TEST_METHOD(EventQueueSizeTest)
		{
			GameClock clock;

			SectorFactory sectorFactory;
			FooEntityFactory fooEntityFactory;

			GameTime time;
			EventQueue eventQueue;
			World world(&time, &eventQueue);

			clock.UpdateGameTime(*world.mState.mGameTime);
			
			Assert::IsTrue(world.mEventQueue->IsEmpty());

			world.mEventQueue->Enqueue(make_shared<Event<Foo>>(10), *world.mState.mGameTime, std::chrono::milliseconds(1000));

			Assert::IsTrue(world.mEventQueue->Size() == 1);

			world.mEventQueue->Clear();

			Assert::IsTrue(world.mEventQueue->IsEmpty());

			world.mEventQueue->Enqueue(make_shared<Event<Foo>>(10), *world.mState.mGameTime, std::chrono::milliseconds(1000));

			Assert::IsTrue(world.mEventQueue->Size() == 1);

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();


			FooEntity & fooEntityA1 = static_cast<FooEntity &>(sectorA.CreateEntity("FooEntity A1", "FooEntity"));


			clock.UpdateGameTime(*world.mState.mGameTime);

			while (fooEntityA1.mData != 10)
			{
				Assert::IsTrue(world.mEventQueue->Size() == 1);
				clock.UpdateGameTime(*world.mState.mGameTime);
				world.Update();
			}

			Assert::IsTrue(world.mEventQueue->IsEmpty());

			Assert::IsTrue(fooEntityA1.mData == 10);
		}
		

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
}