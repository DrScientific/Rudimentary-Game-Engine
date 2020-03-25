#include "pch.h"

#include "CppUnitTest.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Action.h"
#include "ActionList.h"
#include "CreateAction.h"
#include "DestroyAction.h"
#include "ActionListWhile.h"
#include "ActionIncrement.h"
#include "Factory.h"
#include "ScopeJsonParseHelper.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ActionTest)
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

		TEST_METHOD(ActionListConstructorTest)
		{
			ActionList actionList;
		}

		TEST_METHOD(ActionListWhileConstructorTest)
		{
			ActionListWhile actionListWhile;
		}

		TEST_METHOD(ActionIncrementConstructorTest)
		{
			ActionIncrement actionIncrement;
		}

		TEST_METHOD(CreateActionConstructorTest)
		{
			CreateAction createAction;
		}

		TEST_METHOD(DestroyActionConstructorTest)
		{
			DestroyAction destroyAction;
		}

		TEST_METHOD(RTTITests)
		{
			CreateAction createAction;
			DestroyAction destroyAction;
			ActionList actionList;
			ActionListWhile actionListWhile;
			ActionIncrement actionIncrement;

			Assert::IsTrue(createAction.Is("Scope"));
			Assert::IsTrue(createAction.ToString() == "CreateAction");
			Assert::IsTrue(destroyAction.Is("Scope"));
			Assert::IsTrue(destroyAction.ToString() == "DestroyAction");
			Assert::IsTrue(actionList.Is("Scope"));
			Assert::IsTrue(actionList.ToString() == "ActionList");
			Assert::IsTrue(actionListWhile.Is("Scope"));
			Assert::IsTrue(actionListWhile.ToString() == "ActionListWhile");
			Assert::IsTrue(actionIncrement.Is("Scope"));
			Assert::IsTrue(actionIncrement.ToString() == "ActionIncrement");
		}

		TEST_METHOD(ActionNameTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListFactory actionListFactory;
			ActionIncrementFactory actionIncrementFactory;

			GameTime time;
			World world(time);

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();

			Entity & entityA = sectorA.CreateEntity("Entity A", "Entity");
			entityA.Wake();
			entityA.Append("Health").PushBack(10);

			Assert::IsTrue(entityA.Actions().Size() == 0);

			ActionList & actionListA1 = static_cast<ActionList &>(entityA.CreateAction("ActionList A1", "ActionList"));

			Assert::IsTrue(actionListA1.Name() == "ActionList A1");

			actionListA1.CreateAction("ActionIncrement A1", "ActionIncrement");

			ActionIncrement & actionIncrementA1 = static_cast<ActionIncrement &>(actionListA1.Actions()[0]);

			Assert::IsTrue(actionIncrementA1.Name() == "ActionIncrement A1");
		}

		TEST_METHOD(ActionIncrementTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListFactory actionListFactory;
			ActionIncrementFactory actionIncrementFactory;
			
			GameTime time;
			World world(time);

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();

			Entity & entityA = sectorA.CreateEntity("Entity A", "Entity");
			entityA.Wake();
			entityA.Append("Health").PushBack(10);

			Assert::IsTrue(entityA.Actions().Size() == 0);

			ActionList & actionListA1 = static_cast<ActionList &>(entityA.CreateAction("ActionList A1", "ActionList"));

			actionListA1.CreateAction("ActionIncrement A1", "ActionIncrement");

			ActionIncrement & actionIncrementA1 = static_cast<ActionIncrement &>(actionListA1.Actions()[0]);

			Assert::IsNotNull(actionIncrementA1.Find("this"));
			Assert::IsNotNull(actionIncrementA1.Find("Name"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetGameContainer"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetName"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetAttribute"));
			Assert::IsNotNull(actionIncrementA1.Find("Step"));
			
			*actionIncrementA1.Find("TargetGameContainer") = "Entities";
			*actionIncrementA1.Find("TargetName") = "Entity A";
			*actionIncrementA1.Find("TargetAttribute") = "Health";
			*actionIncrementA1.Find("Step") = 2;

			world.Update();

			Assert::IsTrue(entityA["Health"] == 12);
		}

		TEST_METHOD(CreateActionTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListFactory actionListFactory;
			CreateActionFactory createActionFactory;
			ActionIncrementFactory actionIncrementFactory;

			GameTime time;
			World world(time);

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();

			Entity & entityA = sectorA.CreateEntity("Entity A", "Entity");
			entityA.Wake();
			entityA.Append("Health").PushBack(10);

			Assert::IsTrue(entityA.Actions().Size() == 0);

			ActionList & actionListA1 = static_cast<ActionList &>(entityA.CreateAction("ActionList A1", "ActionList"));

			CreateAction & createActionA1 = static_cast<CreateAction &>(actionListA1.CreateAction("CreateAction A1", "CreateAction"));

			Assert::IsNotNull(createActionA1.Find("this"));
			Assert::IsNotNull(createActionA1.Find("Name"));
			Assert::IsNotNull(createActionA1.Find("ClassName"));
			Assert::IsNotNull(createActionA1.Find("InstanceName"));
			

			*createActionA1.Find("ClassName") = "ActionIncrement";
			*createActionA1.Find("InstanceName") = "ActionIncrement A1";

			world.Update();

			ActionIncrement & actionIncrementA1 = *static_cast<ActionIncrement*>(actionListA1["Actions"].Back<Scope*>());

			Assert::IsNotNull(actionIncrementA1.Find("this"));
			Assert::IsNotNull(actionIncrementA1.Find("Name"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetGameContainer"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetName"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetAttribute"));
			Assert::IsNotNull(actionIncrementA1.Find("Step"));

			*actionIncrementA1.Find("TargetGameContainer") = "Entities";
			*actionIncrementA1.Find("TargetName") = "Entity A";
			*actionIncrementA1.Find("TargetAttribute") = "Health";
			*actionIncrementA1.Find("Step") = 2;

			world.Update();

			Assert::IsTrue(entityA["Health"] == 12);
		}

		TEST_METHOD(DestroyActionTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListFactory actionListFactory;
			DestroyActionFactory destroyActionFactory;
			ActionIncrementFactory actionIncrementFactory;

			GameTime time;
			World world(time);

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();

			Entity & entityA = sectorA.CreateEntity("Entity A", "Entity");
			entityA.Wake();
			entityA.Append("Health").PushBack(10);

			Assert::IsTrue(entityA.Actions().Size() == 0);

			entityA.CreateAction("ActionList A1", "ActionList");

			ActionList & actionListA1 = static_cast<ActionList &>(entityA.Actions()[0]);

			actionListA1.CreateAction("ActionIncrement A1", "ActionIncrement");

			ActionIncrement & actionIncrementA1 = static_cast<ActionIncrement &>(actionListA1.Actions()[0]);

			Assert::IsNotNull(actionIncrementA1.Find("this"));
			Assert::IsNotNull(actionIncrementA1.Find("Name"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetGameContainer"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetName"));
			Assert::IsNotNull(actionIncrementA1.Find("TargetAttribute"));
			Assert::IsNotNull(actionIncrementA1.Find("Step"));

			*actionIncrementA1.Find("TargetGameContainer") = "Entities";
			*actionIncrementA1.Find("TargetName") = "Entity A";
			*actionIncrementA1.Find("TargetAttribute") = "Health";
			*actionIncrementA1.Find("Step") = 2;

			DestroyAction & destroyActionA1 = static_cast<DestroyAction &>(actionListA1.CreateAction("DestroyAction A1", "DestroyAction"));

			Assert::IsNotNull(destroyActionA1.Find("this"));
			Assert::IsNotNull(destroyActionA1.Find("Name"));
			Assert::IsNotNull(destroyActionA1.Find("Target"));

			*destroyActionA1.Find("Target") = "ActionIncrement A1";

			world.Update();

			Assert::IsTrue(entityA["Health"] == 12);
			
			world.Update();

			Assert::IsTrue(entityA["Health"] == 12);
		}

		TEST_METHOD(ActionListWhileTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListWhileFactory actionListWhileFactory;
			ActionIncrementFactory actionIncrementFactory;

			GameTime time;
			World world(time);

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();

			Entity & entityA = sectorA.CreateEntity("Entity A", "Entity");
			entityA.Wake();
			entityA.Append("Health").PushBack(10);

			Assert::IsTrue(entityA.Actions().Size() == 0);

			ActionListWhile & actionListWhileA1 = static_cast<ActionListWhile &>(entityA.CreateAction("ActionListWhile A1", "ActionListWhile"));

			Assert::IsNotNull(actionListWhileA1.Find("this"));
			Assert::IsNotNull(actionListWhileA1.Find("Name"));
			Assert::IsNotNull(actionListWhileA1.Find("Actions"));
			Assert::IsNotNull(actionListWhileA1.Find("Condition"));
			Assert::IsNotNull(actionListWhileA1.Find("Preamble"));
			Assert::IsNotNull(actionListWhileA1.Find("Increment"));

			ActionIncrement actionListWhileA1PreambleAction;

			actionListWhileA1.Adopt(actionListWhileA1PreambleAction, "Preamble");

			Assert::IsNotNull(actionListWhileA1PreambleAction.Find("this"));
			Assert::IsNotNull(actionListWhileA1PreambleAction.Find("Name"));
			Assert::IsNotNull(actionListWhileA1PreambleAction.Find("TargetGameContainer"));
			Assert::IsNotNull(actionListWhileA1PreambleAction.Find("TargetName"));
			Assert::IsNotNull(actionListWhileA1PreambleAction.Find("TargetAttribute"));
			Assert::IsNotNull(actionListWhileA1PreambleAction.Find("Step"));

			*actionListWhileA1PreambleAction.Find("TargetGameContainer") = "Actions";
			*actionListWhileA1PreambleAction.Find("TargetName") = "ActionListWhile A1";
			*actionListWhileA1PreambleAction.Find("TargetAttribute") = "Condition";
			*actionListWhileA1PreambleAction.Find("Step") = -10;

			actionListWhileA1.CreateAction("IncrementHealth", "ActionIncrement");

			ActionIncrement & actionListWhileA1LoopAction = static_cast<ActionIncrement &>(actionListWhileA1.Actions()[0]);

			Assert::IsNotNull(actionListWhileA1LoopAction.Find("this"));
			Assert::IsNotNull(actionListWhileA1LoopAction.Find("Name"));
			Assert::IsNotNull(actionListWhileA1LoopAction.Find("TargetGameContainer"));
			Assert::IsNotNull(actionListWhileA1LoopAction.Find("TargetName"));
			Assert::IsNotNull(actionListWhileA1LoopAction.Find("TargetAttribute"));
			Assert::IsNotNull(actionListWhileA1LoopAction.Find("Step"));

			*actionListWhileA1LoopAction.Find("TargetGameContainer") = "Entities";
			*actionListWhileA1LoopAction.Find("TargetName") = "Entity A";
			*actionListWhileA1LoopAction.Find("TargetAttribute") = "Health";
			*actionListWhileA1LoopAction.Find("Step") = 2;

			ActionIncrement actionListWhileA1IncrementAction;

			actionListWhileA1.Adopt(actionListWhileA1IncrementAction, "Increment");

			Assert::IsNotNull(actionListWhileA1IncrementAction.Find("this"));
			Assert::IsNotNull(actionListWhileA1IncrementAction.Find("Name"));
			Assert::IsNotNull(actionListWhileA1IncrementAction.Find("TargetGameContainer"));
			Assert::IsNotNull(actionListWhileA1IncrementAction.Find("TargetName"));
			Assert::IsNotNull(actionListWhileA1IncrementAction.Find("TargetAttribute"));
			Assert::IsNotNull(actionListWhileA1IncrementAction.Find("Step"));

			*actionListWhileA1IncrementAction.Find("TargetGameContainer") = "Actions";
			*actionListWhileA1IncrementAction.Find("TargetName") = "ActionListWhile A1";
			*actionListWhileA1IncrementAction.Find("TargetAttribute") = "Condition";
			*actionListWhileA1IncrementAction.Find("Step") = 1;

			Assert::IsTrue(entityA["Health"] == 10);

			world.Update();

			Assert::IsTrue(entityA["Health"] == 30);
		}

		TEST_METHOD(ActionParseTest)
		{
			//Action while is not running proper number of times, only running once

			GameTime time;

			shared_ptr<Scope> sharedScope = make_shared<World>(time);
			ScopeJsonParseHelper::ScopeSharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListFactory actionListFactory;
			ActionListWhileFactory actionListWhileFactory;
			CreateActionFactory createActionFactory;
			DestroyActionFactory destroyActionFactory;
			ActionIncrementFactory actionIncrementFactory;

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/WorldAction.json"));

			World & ourWorld = static_cast<World&>(sharedData.GetScope());

			Sector & sectorA = static_cast<Sector&>(ourWorld.Sectors()[0]);

			Entity & entityA1 = static_cast<Entity&>(sectorA.Entities()[0]);

			entityA1;

			ourWorld.Update();

			int health = entityA1["Health"].Front<int>();
			health;

			Assert::IsTrue(entityA1["Health"] == 30);
		}

		TEST_METHOD(ActionCloneTest)
		{
			GameTime time;

			shared_ptr<Scope> sharedScope = make_shared<World>(time);
			ScopeJsonParseHelper::ScopeSharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			SectorFactory sectorFactory;
			EntityFactory entityFactory;
			ActionListFactory actionListFactory;
			ActionListWhileFactory actionListWhileFactory;
			CreateActionFactory createActionFactory;
			DestroyActionFactory destroyActionFactory;
			ActionIncrementFactory actionIncrementFactory;

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/WorldAction.json"));

			World & ourWorld = static_cast<World&>(sharedData.GetScope());

			Sector & sectorA = static_cast<Sector&>(ourWorld.Sectors()[0]);

			Entity & entityA1 = static_cast<Entity&>(sectorA.Entities()[0]);

			ourWorld.Update();

			Assert::IsTrue(entityA1["Health"] == 30);

			JsonParseMaster& clonedMaster = *master.Clone();

			clonedMaster.Initialize();			

			Assert::IsTrue(clonedMaster.ParseFromFile("Content/WorldAction.json"));

			ScopeJsonParseHelper::ScopeSharedData & clonedSharedData = *clonedMaster.GetSharedData()->As< ScopeJsonParseHelper::ScopeSharedData>();

			World & clonedOurWorld = static_cast<World&>(clonedSharedData.GetScope());

			Sector & clonedSectorA = static_cast<Sector&>(clonedOurWorld.Sectors()[0]);

			Entity & clonedEntityA1 = static_cast<Entity&>(clonedSectorA.Entities()[0]);

			clonedOurWorld.Update();

			int health = clonedEntityA1["Health"].Front<int>();
			health;

			Assert::IsTrue(clonedEntityA1["Health"] == 50);

			Assert::IsTrue(entityA1["Health"] == 30);


			delete &clonedMaster;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionTest::sStartMemState;
}