#include "pch.h"

#include "CppUnitTest.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"
#include "Factory.h"
#include "ScopeJsonParseHelper.h"
#include "IEventSubscriber.h"
#include "EventQueue.h"
#include "Event.h"
#include "ActionEvent.h"
#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
#include "ActionIncrement.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ReactionTest)
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
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(EventMessageAttributedCtorTest)
		{
			EventMessageAttributed attributedMessage("testSubtype", nullptr);
		}

		TEST_METHOD(ActionEventCtorTest)
		{
			ActionEvent actionEvent;
		}

		TEST_METHOD(ReactionAttributedCtorTest)
		{
			ReactionAttributed attributedReaction;
		}

		TEST_METHOD(RTTITest)
		{
			EventMessageAttributed attributedMessage("testSubtype", nullptr);

			Assert::IsTrue(attributedMessage.Is(Attributed::TypeIdClass()));

			ActionEvent actionEvent;

			Assert::IsTrue(actionEvent.Is(Action::TypeIdClass()));

			ReactionAttributed attributedReaction;

			Assert::IsTrue(attributedReaction.Is(ActionList::TypeIdClass()));
			Assert::IsTrue(attributedReaction.Is(Attributed::TypeIdClass()));
		}

		TEST_METHOD(ReactionAttributedTest)
		{

			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionEventFactory actionEventFactory;
			ActionIncrementFactory actionIncrementFactory;

			GameTime time;
			EventQueue eventQueue;
			World world(&time, &eventQueue);

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();


			Entity & entityA1 = static_cast<Entity &>(sectorA.CreateEntity("Entity A1", "Entity"));
			entityA1.Wake();
			entityA1.Append("Health") = 10;

			Action & actionEventA1 = static_cast<Action &>(entityA1.CreateAction("ActionEvent A1", "ActionEvent"));

			*actionEventA1.Find("Subtype") = "Test";
			*actionEventA1.Find("Delay") = 2000;


			actionEventA1.AppendAuxiliaryAttribute("TargetGameContainer") = "Entities";
			actionEventA1.AppendAuxiliaryAttribute("TargetName") = "Entity A1";
			actionEventA1.AppendAuxiliaryAttribute("TargetAttribute") = "Health";
			actionEventA1.AppendAuxiliaryAttribute("Step") = 2;

			ReactionAttributed * testReaction = new ReactionAttributed("TestReaction", "Test");

			testReaction->CreateAction("ReactionIncrement", "ActionIncrement");

			entityA1.Adopt(*testReaction, "Reactions");

			world.Update();

			Assert::IsTrue(entityA1["Health"] == 10);

			time.SetCurrentTime(chrono::high_resolution_clock::time_point(chrono::seconds(1)));

			world.Update();

			Assert::IsTrue(entityA1["Health"] == 10);

			time.SetCurrentTime(chrono::high_resolution_clock::time_point(chrono::seconds(3)));

			world.Update();

			Assert::IsTrue(entityA1["Health"] == 12); 

			delete testReaction;
		}

		TEST_METHOD(ReactionAttributedParseTest)
		{
			GameTime time;
			EventQueue eventQueue;

			shared_ptr<Scope> sharedScope = make_shared<World>(&time, &eventQueue);
			ScopeJsonParseHelper::ScopeSharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionEventFactory actionEventFactory;
			ReactionAttributedFactory reactionAttributedFactory;
			ActionIncrementFactory actionIncrementFactory;

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/WorldReaction.json"));

			World & ourWorld = static_cast<World&>(sharedData.GetScope());

			Sector & sectorA = static_cast<Sector&>(ourWorld.Sectors()[0]);
			Entity & entityA1 = static_cast<Entity&>(sectorA.Entities()[0]);

			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 10);

			time.SetCurrentTime(chrono::high_resolution_clock::time_point(chrono::seconds(1)));

			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 10);

			time.SetCurrentTime(chrono::high_resolution_clock::time_point(chrono::seconds(3)));

			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 12);
		}

		/*TEST_METHOD(ReactionAttributedCloneTest)
		{
			GameTime time;
			EventQueue eventQueue;

			shared_ptr<Scope> sharedScope = make_shared<World>(&time, &eventQueue);
			ScopeJsonParseHelper::ScopeSharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionEventFactory actionEventFactory;
			ReactionAttributedFactory reactionAttributedFactory;
			ActionIncrementFactory actionIncrementFactory;

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/WorldReaction.json"));

			JsonParseMaster* clonedMaster = master.Clone();

			clonedMaster->Initialize();

			//Assert::IsTrue(clonedMaster->ParseFromFile("Content/WorldReaction.json"));

			World & ourWorld = static_cast<World&>(clonedMaster->GetSharedData()->As< ScopeJsonParseHelper::ScopeSharedData>()->GetScope());

			ourWorld.SetName("Cloned World");

			Sector & sectorA = static_cast<Sector&>(ourWorld.Sectors()[0]);
			Entity & entityA1 = static_cast<Entity&>(sectorA.Entities()[0]);


			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 10);

			
			ourWorld.mState.mGameTime->SetCurrentTime(chrono::high_resolution_clock::time_point(chrono::seconds(1)));

			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 10);

			ourWorld.mState.mGameTime->SetCurrentTime(chrono::high_resolution_clock::time_point(chrono::seconds(3)));

			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 12);

			delete clonedMaster;
		}*/

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionTest::sStartMemState;
}