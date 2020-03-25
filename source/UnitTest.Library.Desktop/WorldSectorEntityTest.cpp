#include "pch.h"

#include "CppUnitTest.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "Factory.h"
#include "ScopeJsonParseHelper.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(WorldSectorEntityTest)
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

		TEST_METHOD(WorldConstructorTest)
		{
			GameTime time;
			World world(time);
		}

		TEST_METHOD(SectorConstructorTest)
		{
			Sector sector;
		}

		TEST_METHOD(EntityConstructorTest)
		{
			Entity entity;
		}

		TEST_METHOD(RTTITests)
		{
			GameTime time;
			World world(time);
			Sector sector;
			Entity entity;

			Assert::IsTrue(world.Is("Scope"));
			Assert::IsTrue(world.ToString() == "World");
			Assert::IsTrue(sector.Is("Scope"));
			Assert::IsTrue(sector.ToString() == "Sector");
			Assert::IsTrue(entity.Is("Scope"));
			Assert::IsTrue(entity.ToString() == "Entity");
		}

		TEST_METHOD(WorldNameAndAwakeTest)
		{
			GameTime time;
			World world(time);

			Assert::IsTrue(world.Name() == "");
			world.SetName("world");
			Assert::IsTrue(world.Name() == "world");
		}

		TEST_METHOD(SectorNameAndAwakeTest)
		{
			Sector sector;

			Assert::IsTrue(sector.Name() == "");
			sector.SetName("sector");
			Assert::IsTrue(sector.Name() == "sector");

			Assert::IsFalse(sector.IsAwake());
			sector.Wake();
			Assert::IsTrue(sector.IsAwake());
			sector.Sleep();
			Assert::IsFalse(sector.IsAwake());
			sector.SetIsAwake(true);
			Assert::IsTrue(sector.IsAwake());
			sector.SetIsAwake(false);
			Assert::IsFalse(sector.IsAwake());
		}

		TEST_METHOD(EntityNameAndAwakeTest)
		{
			Entity entity;

			Assert::IsTrue(entity.Name() == "");
			entity.SetName("entity");
			Assert::IsTrue(entity.Name() == "entity");

			Assert::IsFalse(entity.IsAwake());
			entity.Wake();
			Assert::IsTrue(entity.IsAwake());
			entity.Sleep();
			Assert::IsFalse(entity.IsAwake());
			entity.SetIsAwake(true);
			Assert::IsTrue(entity.IsAwake());
			entity.SetIsAwake(false);
			Assert::IsFalse(entity.IsAwake());
		}

		TEST_METHOD(WorldCreateSectorsTest)
		{
			SectorFactory sectorFactory;

			GameTime time;
			World world(time);

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			Sector & sectorB = world.CreateSector("Sector B");
			Sector & sectorC = world.CreateSector("Sector C");
			Sector & sectorD = world.CreateSector("Sector D");

			Assert::IsTrue(world.Sectors()[0] == sectorA);
			Assert::IsTrue(world.Sectors()[1] == sectorB);
			Assert::IsTrue(world.Sectors()[2] == sectorC);
			Assert::IsTrue(world.Sectors()[3] == sectorD);
		}

		TEST_METHOD(SectorCreateEntitiesTest)
		{
			EntityFactory entityFactory;

			Sector sector;

			Entity & entityA = sector.CreateEntity("Entity A", "Entity");
			Entity & entityB = sector.CreateEntity("Entity B", "Entity");
			Entity & entityC = sector.CreateEntity("Entity C", "Entity");
			Entity & entityD = sector.CreateEntity("Entity D", "Entity");

			Assert::IsTrue(sector.Entities()[0] == entityA);
			Assert::IsTrue(sector.Entities()[1] == entityB);
			Assert::IsTrue(sector.Entities()[2] == entityC);
			Assert::IsTrue(sector.Entities()[3] == entityD);
		}

		TEST_METHOD(NestedCreateTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;

			GameTime time;
			World world(time);

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			Sector & sectorB = world.CreateSector("Sector B");
			Sector & sectorC = world.CreateSector("Sector C");
			Sector & sectorD = world.CreateSector("Sector D");

			Entity & entityA1 = sectorA.CreateEntity("Entity A1", "Entity");
			Entity & entityA2 = sectorA.CreateEntity("Entity A2", "Entity");
			Entity & entityA3 = sectorA.CreateEntity("Entity A3", "Entity");
			Entity & entityA4 = sectorA.CreateEntity("Entity A4", "Entity");

			Entity & entityB1 = sectorB.CreateEntity("Entity B1", "Entity");
			Entity & entityB2 = sectorB.CreateEntity("Entity B2", "Entity");
			Entity & entityB3 = sectorB.CreateEntity("Entity B3", "Entity");
			Entity & entityB4 = sectorB.CreateEntity("Entity B4", "Entity");

			Entity & entityC1 = sectorC.CreateEntity("Entity C1", "Entity");
			Entity & entityC2 = sectorC.CreateEntity("Entity C2", "Entity");
			Entity & entityC3 = sectorC.CreateEntity("Entity C3", "Entity");
			Entity & entityC4 = sectorC.CreateEntity("Entity C4", "Entity");

			Entity & entityD1 = sectorD.CreateEntity("Entity D1", "Entity");
			Entity & entityD2 = sectorD.CreateEntity("Entity D2", "Entity");
			Entity & entityD3 = sectorD.CreateEntity("Entity D3", "Entity");
			Entity & entityD4 = sectorD.CreateEntity("Entity D4", "Entity");

			Assert::IsTrue(world.Sectors()[0] == sectorA);
			Assert::IsTrue(sectorA.Entities()[0] == entityA1);
			Assert::IsTrue(sectorA.Entities()[1] == entityA2);
			Assert::IsTrue(sectorA.Entities()[2] == entityA3);
			Assert::IsTrue(sectorA.Entities()[3] == entityA4);

			Assert::IsTrue(world.Sectors()[1] == sectorB);
			Assert::IsTrue(sectorB.Entities()[0] == entityB1);
			Assert::IsTrue(sectorB.Entities()[1] == entityB2);
			Assert::IsTrue(sectorB.Entities()[2] == entityB3);
			Assert::IsTrue(sectorB.Entities()[3] == entityB4);

			Assert::IsTrue(world.Sectors()[2] == sectorC);
			Assert::IsTrue(sectorC.Entities()[0] == entityC1);
			Assert::IsTrue(sectorC.Entities()[1] == entityC2);
			Assert::IsTrue(sectorC.Entities()[2] == entityC3);
			Assert::IsTrue(sectorC.Entities()[3] == entityC4);

			Assert::IsTrue(world.Sectors()[3] == sectorD);
			Assert::IsTrue(sectorD.Entities()[0] == entityD1);
			Assert::IsTrue(sectorD.Entities()[1] == entityD2);
			Assert::IsTrue(sectorD.Entities()[2] == entityD3);
			Assert::IsTrue(sectorD.Entities()[3] == entityD4);
		}

		TEST_METHOD(GetAndSetParentTest)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;

			GameTime time1;
			World world1(time1);

			world1.SetName("world1");

			Sector & sector1A = world1.CreateSector("Sector 1A");
			Sector & sector1B = world1.CreateSector("Sector 1B");
			Sector & sector1C = world1.CreateSector("Sector 1C");
			Sector & sector1D = world1.CreateSector("Sector 1D");

			Entity & entity1A1 = sector1A.CreateEntity("Entity 1A1", "Entity");
			Entity & entity1A2 = sector1A.CreateEntity("Entity 1A2", "Entity");
			Entity & entity1A3 = sector1A.CreateEntity("Entity 1A3", "Entity");
			Entity & entity1A4 = sector1A.CreateEntity("Entity 1A4", "Entity");

			Entity & entity1B1 = sector1B.CreateEntity("Entity 1B1", "Entity");
			Entity & entity1B2 = sector1B.CreateEntity("Entity 1B2", "Entity");
			Entity & entity1B3 = sector1B.CreateEntity("Entity 1B3", "Entity");
			Entity & entity1B4 = sector1B.CreateEntity("Entity 1B4", "Entity");

			Entity & entity1C1 = sector1C.CreateEntity("Entity 1C1", "Entity");
			Entity & entity1C2 = sector1C.CreateEntity("Entity 1C2", "Entity");
			Entity & entity1C3 = sector1C.CreateEntity("Entity 1C3", "Entity");
			Entity & entity1C4 = sector1C.CreateEntity("Entity 1C4", "Entity");

			Entity & entity1D1 = sector1D.CreateEntity("Entity 1D1", "Entity");
			Entity & entity1D2 = sector1D.CreateEntity("Entity 1D2", "Entity");
			Entity & entity1D3 = sector1D.CreateEntity("Entity 1D3", "Entity");
			Entity & entity1D4 = sector1D.CreateEntity("Entity 1D4", "Entity");

			Assert::IsTrue(world1.Sectors()[0] == sector1A);
			Assert::IsTrue(sector1A.Entities()[0] == entity1A1);
			Assert::IsTrue(sector1A.Entities()[1] == entity1A2);
			Assert::IsTrue(sector1A.Entities()[2] == entity1A3);
			Assert::IsTrue(sector1A.Entities()[3] == entity1A4);

			Assert::IsTrue(world1.Sectors()[1] == sector1B);
			Assert::IsTrue(sector1B.Entities()[0] == entity1B1);
			Assert::IsTrue(sector1B.Entities()[1] == entity1B2);
			Assert::IsTrue(sector1B.Entities()[2] == entity1B3);
			Assert::IsTrue(sector1B.Entities()[3] == entity1B4);

			Assert::IsTrue(world1.Sectors()[2] == sector1C);
			Assert::IsTrue(sector1C.Entities()[0] == entity1C1);
			Assert::IsTrue(sector1C.Entities()[1] == entity1C2);
			Assert::IsTrue(sector1C.Entities()[2] == entity1C3);
			Assert::IsTrue(sector1C.Entities()[3] == entity1C4);

			Assert::IsTrue(world1.Sectors()[3] == sector1D);
			Assert::IsTrue(sector1D.Entities()[0] == entity1D1);
			Assert::IsTrue(sector1D.Entities()[1] == entity1D2);
			Assert::IsTrue(sector1D.Entities()[2] == entity1D3);
			Assert::IsTrue(sector1D.Entities()[3] == entity1D4);

			GameTime time2;
			World world2(time2);

			world2.SetName("world2");

			Sector & sector2A = world2.CreateSector("Sector 2A");
			Sector & sector2B = world2.CreateSector("Sector 2B");
			Sector & sector2C = world2.CreateSector("Sector 2C");
			Sector & sector2D = world2.CreateSector("Sector 2D");

			Entity & entity2A1 = sector2A.CreateEntity("Entity 2A1", "Entity");
			Entity & entity2A2 = sector2A.CreateEntity("Entity 2A2", "Entity");
			Entity & entity2A3 = sector2A.CreateEntity("Entity 2A3", "Entity");
			Entity & entity2A4 = sector2A.CreateEntity("Entity 2A4", "Entity");

			Entity & entity2B1 = sector2B.CreateEntity("Entity 2B1", "Entity");
			Entity & entity2B2 = sector2B.CreateEntity("Entity 2B2", "Entity");
			Entity & entity2B3 = sector2B.CreateEntity("Entity 2B3", "Entity");
			Entity & entity2B4 = sector2B.CreateEntity("Entity 2B4", "Entity");

			Entity & entity2C1 = sector2C.CreateEntity("Entity 2C1", "Entity");
			Entity & entity2C2 = sector2C.CreateEntity("Entity 2C2", "Entity");
			Entity & entity2C3 = sector2C.CreateEntity("Entity 2C3", "Entity");
			Entity & entity2C4 = sector2C.CreateEntity("Entity 2C4", "Entity");

			Entity & entity2D1 = sector2D.CreateEntity("Entity 2D1", "Entity");
			Entity & entity2D2 = sector2D.CreateEntity("Entity 2D2", "Entity");
			Entity & entity2D3 = sector2D.CreateEntity("Entity 2D3", "Entity");
			Entity & entity2D4 = sector2D.CreateEntity("Entity 2D4", "Entity");

			Assert::IsTrue(world2.Sectors()[0] == sector2A);
			Assert::IsTrue(sector2A.Entities()[0] == entity2A1);
			Assert::IsTrue(sector2A.Entities()[1] == entity2A2);
			Assert::IsTrue(sector2A.Entities()[2] == entity2A3);
			Assert::IsTrue(sector2A.Entities()[3] == entity2A4);

			Assert::IsTrue(world2.Sectors()[1] == sector2B);
			Assert::IsTrue(sector2B.Entities()[0] == entity2B1);
			Assert::IsTrue(sector2B.Entities()[1] == entity2B2);
			Assert::IsTrue(sector2B.Entities()[2] == entity2B3);
			Assert::IsTrue(sector2B.Entities()[3] == entity2B4);

			Assert::IsTrue(world2.Sectors()[2] == sector2C);
			Assert::IsTrue(sector2C.Entities()[0] == entity2C1);
			Assert::IsTrue(sector2C.Entities()[1] == entity2C2);
			Assert::IsTrue(sector2C.Entities()[2] == entity2C3);
			Assert::IsTrue(sector2C.Entities()[3] == entity2C4);

			Assert::IsTrue(world2.Sectors()[3] == sector2D);
			Assert::IsTrue(sector2D.Entities()[0] == entity2D1);
			Assert::IsTrue(sector2D.Entities()[1] == entity2D2);
			Assert::IsTrue(sector2D.Entities()[2] == entity2D3);
			Assert::IsTrue(sector2D.Entities()[3] == entity2D4);

			Assert::IsTrue(entity2D4.GetSector() == &sector2D);

			entity2D4.SetSector(&sector2A);

			Assert::IsTrue(entity2D4.GetSector() == &sector2A);
			
			Assert::IsTrue(sector2D.Entities().Size() == 3);
			Assert::IsTrue(sector2A.Entities().Size() == 5);
			Assert::IsTrue(sector2A.Entities()[4] == entity2D4);

			Assert::IsTrue(entity1D4.GetSector() == &sector1D);

			entity1D4.SetSector(&sector2A);

			Assert::IsTrue(sector1D.Entities().Size() == 3);
			Assert::IsTrue(sector2A.Entities().Size() == 6);
			Assert::IsTrue(sector2A.Entities()[5] == entity1D4);


			Assert::IsTrue(sector2A.GetWorld() == &world2);

			sector2A.SetWorld(&world1);

			Assert::IsTrue(sector2A.GetWorld() == &world1);
			
			Assert::IsTrue(world2.Sectors().Size() == 3);
			Assert::IsTrue(world1.Sectors().Size() == 5);
			Assert::IsTrue(world1.Sectors()[4] == sector2A);

			Assert::IsTrue(sector2A.GetWorld() == &world1);
		}

		TEST_METHOD(TestUpdate)
		{
			SectorFactory sectorFactory;
			EntityFactory entityFactory;

			GameTime time;
			World world(time);

			world.SetName("world");

			Sector & sectorA = world.CreateSector("Sector A");
			sectorA.Wake();
			Sector & sectorB = world.CreateSector("Sector B");
			sectorB.Wake();
			Sector & sectorC = world.CreateSector("Sector C");
			sectorC.Wake();
			Sector & sectorD = world.CreateSector("Sector D");
			sectorD.Wake();

			sectorA.CreateEntity("Entity A1", "Entity").Wake();
			sectorA.CreateEntity("Entity A2", "Entity").Wake();
			sectorA.CreateEntity("Entity A3", "Entity").Wake();
			sectorA.CreateEntity("Entity A4", "Entity").Wake();
			
			sectorB.CreateEntity("Entity B1", "Entity").Wake();
			sectorB.CreateEntity("Entity B2", "Entity").Wake();
			sectorB.CreateEntity("Entity B3", "Entity").Wake();
			sectorB.CreateEntity("Entity B4", "Entity").Wake();
			
			sectorC.CreateEntity("Entity C1", "Entity").Wake();
			sectorC.CreateEntity("Entity C2", "Entity").Wake();
			sectorC.CreateEntity("Entity C3", "Entity").Wake();
			sectorC.CreateEntity("Entity C4", "Entity").Wake();
			
			sectorD.CreateEntity("Entity D1", "Entity").Wake();
			sectorD.CreateEntity("Entity D2", "Entity").Wake();
			sectorD.CreateEntity("Entity D3", "Entity").Wake();
			sectorD.CreateEntity("Entity D4", "Entity").Wake();

			world.Update();
		}

		TEST_METHOD(WorldParseTest)
		{
			/*
			While the data is being parsed and accessible it is being stored in the wrong location.
			*/
			GameTime time;

			shared_ptr<Scope> sharedScope = make_shared<World>(time);
			ScopeJsonParseHelper::ScopeSharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			SectorFactory sectorFactory;
			EntityFactory entityFactory;

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/World.json"));

			World & ourWorld = static_cast<World&>(sharedData.GetScope());

			Sector & sectorA = static_cast<Sector&>(ourWorld.Sectors()[0]);			
			Entity & entityA1 = static_cast<Entity&>(sectorA.Entities()[0]);
			Entity & entityA2 = static_cast<Entity&>(sectorA.Entities()[1]);
			Entity & entityA3 = static_cast<Entity&>(sectorA.Entities()[2]);
			Entity & entityA4 = static_cast<Entity&>(sectorA.Entities()[3]);

			Sector & sectorB = static_cast<Sector&>(ourWorld.Sectors()[1]);
			Assert::IsTrue(&ourWorld.Sectors()[1] == &sectorB);
			Entity & entityB1 = static_cast<Entity&>(sectorB.Entities()[0]);
			Entity & entityB2 = static_cast<Entity&>(sectorB.Entities()[1]);
			Entity & entityB3 = static_cast<Entity&>(sectorB.Entities()[2]);
			Entity & entityB4 = static_cast<Entity&>(sectorB.Entities()[3]);

			Sector & sectorC = static_cast<Sector&>(ourWorld.Sectors()[2]);
			Assert::IsTrue(&ourWorld.Sectors()[2] == &sectorC);
			Entity & entityC1 = static_cast<Entity&>(sectorC.Entities()[0]);
			Entity & entityC2 = static_cast<Entity&>(sectorC.Entities()[1]);
			Entity & entityC3 = static_cast<Entity&>(sectorC.Entities()[2]);
			Entity & entityC4 = static_cast<Entity&>(sectorC.Entities()[3]);

			Sector & sectorD = static_cast<Sector&>(ourWorld.Sectors()[3]);
			Assert::IsTrue(&ourWorld.Sectors()[3] == &sectorD);
			Entity & entityD1 = static_cast<Entity&>(sectorD.Entities()[0]);
			Entity & entityD2 = static_cast<Entity&>(sectorD.Entities()[1]);
			Entity & entityD3 = static_cast<Entity&>(sectorD.Entities()[2]);
			Entity & entityD4 = static_cast<Entity&>(sectorD.Entities()[3]);

			Assert::IsTrue(ourWorld.Is(World::TypeIdClass()));
			Assert::IsTrue(sectorA.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityA1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityA2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityA3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityA4.Is(Entity::TypeIdClass()));

			Assert::IsTrue(sectorB.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityB1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityB2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityB3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityB4.Is(Entity::TypeIdClass()));

			Assert::IsTrue(sectorC.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityC1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityC2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityC3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityC4.Is(Entity::TypeIdClass()));

			Assert::IsTrue(sectorD.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityD1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityD2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityD3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityD4.Is(Entity::TypeIdClass()));


			Assert::IsTrue(ourWorld.Name() == "Test World");


			Assert::IsTrue(sectorA.Name() == "Sector A");
			Assert::IsTrue(sectorA.IsAwake());

			Assert::IsTrue(entityA1.Name() == "Entity A1");
			Assert::IsTrue(entityA1.IsAwake());

			Assert::IsTrue(entityA2.Name() == "Entity A2");
			Assert::IsTrue(!entityA2.IsAwake());

			Assert::IsTrue(entityA3.Name() == "Entity A3");
			Assert::IsTrue(entityA3.IsAwake());

			Assert::IsTrue(entityA4.Name() == "Entity A4");
			Assert::IsTrue(!entityA4.IsAwake());



			Assert::IsTrue(sectorB.Name() == "Sector B");
			Assert::IsTrue(sectorB.IsAwake());

			Assert::IsTrue(entityB1.Name() == "Entity B1");
			Assert::IsTrue(!entityB1.IsAwake());

			Assert::IsTrue(entityB2.Name() == "Entity B2");
			Assert::IsTrue(!entityB2.IsAwake());

			Assert::IsTrue(entityB3.Name() == "Entity B3");
			Assert::IsTrue(!entityB3.IsAwake());

			Assert::IsTrue(entityB4.Name() == "Entity B4");
			Assert::IsTrue(!entityB4.IsAwake());



			Assert::IsTrue(sectorC.Name() == "Sector C");
			Assert::IsTrue(!sectorC.IsAwake());

			Assert::IsTrue(entityC1.Name() == "Entity C1");
			Assert::IsTrue(entityC1.IsAwake());

			Assert::IsTrue(entityC2.Name() == "Entity C2");
			Assert::IsTrue(entityC2.IsAwake());

			Assert::IsTrue(entityC3.Name() == "Entity C3");
			Assert::IsTrue(entityC3.IsAwake());

			Assert::IsTrue(entityC4.Name() == "Entity C4");
			Assert::IsTrue(entityC4.IsAwake());


			Assert::IsTrue(sectorD.Name() == "Sector D");
			Assert::IsTrue(!sectorD.IsAwake());

			Assert::IsTrue(entityD1.Name() == "Entity D1");
			Assert::IsTrue(entityD1.IsAwake());

			Assert::IsTrue(entityD2.Name() == "Entity D2");
			Assert::IsTrue(!entityD2.IsAwake());

			Assert::IsTrue(entityD3.Name() == "Entity D3");
			Assert::IsTrue(entityD3.IsAwake());

			Assert::IsTrue(entityD4.Name() == "Entity D4");
			Assert::IsTrue(!entityD4.IsAwake());
		}

		TEST_METHOD(WorldCloneTest)
		{
			GameTime time;

			shared_ptr<Scope> sharedScope = make_shared<World>(time);
			ScopeJsonParseHelper::ScopeSharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			SectorFactory sectorFactory;
			EntityFactory entityFactory;

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/World.json"));

			JsonParseMaster* clonedMaster = master.Clone();

			clonedMaster->Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/World.json"));

			ScopeJsonParseHelper::ScopeSharedData & clonedSharedData = *clonedMaster->GetSharedData()->As< ScopeJsonParseHelper::ScopeSharedData>();

			World & cloneOurWorld = static_cast<World&>(clonedSharedData.GetScope());

			Sector & sectorA = static_cast<Sector&>(cloneOurWorld.Sectors()[0]);
			Entity & entityA1 = static_cast<Entity&>(sectorA.Entities()[0]);

			Assert::IsTrue(sectorA.Name() == "Sector A");
			Assert::IsTrue(sectorA.IsAwake());

			Assert::IsTrue(entityA1.Name() == "Entity A1");
			Assert::IsTrue(entityA1.IsAwake());

			Entity & entityA2 = static_cast<Entity&>(sectorA.Entities()[1]);
			Entity & entityA3 = static_cast<Entity&>(sectorA.Entities()[2]);
			Entity & entityA4 = static_cast<Entity&>(sectorA.Entities()[3]);

			Sector & sectorB = static_cast<Sector&>(cloneOurWorld.Sectors()[1]);
			Entity & entityB1 = static_cast<Entity&>(sectorB.Entities()[0]);
			Entity & entityB2 = static_cast<Entity&>(sectorB.Entities()[1]);
			Entity & entityB3 = static_cast<Entity&>(sectorB.Entities()[2]);
			Entity & entityB4 = static_cast<Entity&>(sectorB.Entities()[3]);

			Sector & sectorC = static_cast<Sector&>(cloneOurWorld.Sectors()[2]);
			Entity & entityC1 = static_cast<Entity&>(sectorC.Entities()[0]);
			Entity & entityC2 = static_cast<Entity&>(sectorC.Entities()[1]);
			Entity & entityC3 = static_cast<Entity&>(sectorC.Entities()[2]);
			Entity & entityC4 = static_cast<Entity&>(sectorC.Entities()[3]);

			Sector & sectorD = static_cast<Sector&>(cloneOurWorld.Sectors()[3]);
			Entity & entityD1 = static_cast<Entity&>(sectorD.Entities()[0]);
			Entity & entityD2 = static_cast<Entity&>(sectorD.Entities()[1]);
			Entity & entityD3 = static_cast<Entity&>(sectorD.Entities()[2]);
			Entity & entityD4 = static_cast<Entity&>(sectorD.Entities()[3]);

			Assert::IsTrue(cloneOurWorld.Is(World::TypeIdClass()));
			Assert::IsTrue(sectorA.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityA1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityA2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityA3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityA4.Is(Entity::TypeIdClass()));

			Assert::IsTrue(sectorB.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityB1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityB2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityB3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityB4.Is(Entity::TypeIdClass()));

			Assert::IsTrue(sectorC.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityC1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityC2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityC3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityC4.Is(Entity::TypeIdClass()));

			Assert::IsTrue(sectorD.Is(Sector::TypeIdClass()));
			Assert::IsTrue(entityD1.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityD2.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityD3.Is(Entity::TypeIdClass()));
			Assert::IsTrue(entityD4.Is(Entity::TypeIdClass()));


			Assert::IsTrue(cloneOurWorld.Name() == "Test World");


			Assert::IsTrue(sectorA.Name() == "Sector A");
			Assert::IsTrue(sectorA.IsAwake());

			Assert::IsTrue(entityA1.Name() == "Entity A1");
			Assert::IsTrue(entityA1.IsAwake());

			Assert::IsTrue(entityA2.Name() == "Entity A2");
			Assert::IsTrue(!entityA2.IsAwake());

			Assert::IsTrue(entityA3.Name() == "Entity A3");
			Assert::IsTrue(entityA3.IsAwake());

			Assert::IsTrue(entityA4.Name() == "Entity A4");
			Assert::IsTrue(!entityA4.IsAwake());



			Assert::IsTrue(sectorB.Name() == "Sector B");
			Assert::IsTrue(sectorB.IsAwake());

			Assert::IsTrue(entityB1.Name() == "Entity B1");
			Assert::IsTrue(!entityB1.IsAwake());

			Assert::IsTrue(entityB2.Name() == "Entity B2");
			Assert::IsTrue(!entityB2.IsAwake());

			Assert::IsTrue(entityB3.Name() == "Entity B3");
			Assert::IsTrue(!entityB3.IsAwake());

			Assert::IsTrue(entityB4.Name() == "Entity B4");
			Assert::IsTrue(!entityB4.IsAwake());



			Assert::IsTrue(sectorC.Name() == "Sector C");
			Assert::IsTrue(!sectorC.IsAwake());

			Assert::IsTrue(entityC1.Name() == "Entity C1");
			Assert::IsTrue(entityC1.IsAwake());

			Assert::IsTrue(entityC2.Name() == "Entity C2");
			Assert::IsTrue(entityC2.IsAwake());

			Assert::IsTrue(entityC3.Name() == "Entity C3");
			Assert::IsTrue(entityC3.IsAwake());

			Assert::IsTrue(entityC4.Name() == "Entity C4");
			Assert::IsTrue(entityC4.IsAwake());


			Assert::IsTrue(sectorD.Name() == "Sector D");
			Assert::IsTrue(!sectorD.IsAwake());

			Assert::IsTrue(entityD1.Name() == "Entity D1");
			Assert::IsTrue(entityD1.IsAwake());

			Assert::IsTrue(entityD2.Name() == "Entity D2");
			Assert::IsTrue(!entityD2.IsAwake());

			Assert::IsTrue(entityD3.Name() == "Entity D3");
			Assert::IsTrue(entityD3.IsAwake());

			Assert::IsTrue(entityD4.Name() == "Entity D4");
			Assert::IsTrue(!entityD4.IsAwake());

			delete clonedMaster;
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState WorldSectorEntityTest::sStartMemState;
}