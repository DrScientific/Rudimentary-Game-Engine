#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "Datum.h"
#include "Vector.h"
#include "Scope.h"
#include <random>
#include <time.h>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace std;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeTest)
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
				_CrtMemDumpStatistics(&diffMemState); _CrtDumpMemoryLeaks();
				Assert::Fail(L"Memory leak detected!\nIf a static object is dynamically allocating memory this may be a false positive.");
			}
#endif
		}

		float randFloat()
		{
			numeric_limits<float> floatLimits;
			return floatLimits.min() + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (floatLimits.max() - floatLimits.min())));
		}

		std::string random_string(size_t length)
		{
			auto randchar = []() -> char
			{
				const char charset[] =
					"0123456789"
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz";
				const size_t max_index = (sizeof(charset) - 1);
				return charset[rand() % max_index];
			};
			std::string str(length, 0);
			std::generate_n(str.begin(), length, randchar);
			return str;
		}

		TEST_METHOD(TestConstructorsAndDestructor)
		{
			Scope b;
		}

		TEST_METHOD(TestAppend)
		{
			Scope rathalos;

			Assert::IsTrue(rathalos.Size() == 0);
			rathalos.Append("Name");
			Assert::IsTrue(rathalos.Size() == 1);
			rathalos.Append("Model");
			Assert::IsTrue(rathalos.Size() == 2);
			rathalos.Append("Health");
			Assert::IsTrue(rathalos.Size() == 3);
			rathalos.Append("Size");
			Assert::IsTrue(rathalos.Size() == 4);
			rathalos.Append("Move Set");
			Assert::IsTrue(rathalos.Size() == 5);
			rathalos.Append("Drops");
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos.Append("Name");
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos.Append("Model");
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos.Append("Health");
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos.Append("Size");
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos.Append("Move Set");
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos.Append("Drops");
			Assert::IsTrue(rathalos.Size() == 6);

			auto emptyKeyException = [&rathalos] {rathalos.Append(""); };
			Assert::ExpectException<exception>(emptyKeyException);
		}

		TEST_METHOD(TestStringOperatorBracket)
		{
			Scope rathalos;

			Assert::IsTrue(rathalos.Size() == 0);
			rathalos["Name"];
			Assert::IsTrue(rathalos.Size() == 1);
			rathalos["Model"];
			Assert::IsTrue(rathalos.Size() == 2);
			rathalos["Health"];
			Assert::IsTrue(rathalos.Size() == 3);
			rathalos["Size"];
			Assert::IsTrue(rathalos.Size() == 4);
			rathalos["Move Set"];
			Assert::IsTrue(rathalos.Size() == 5);
			rathalos["Drops"];
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos["Name"];
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos["Model"];
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos["Health"];
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos["Size"];
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos["Move Set"];
			Assert::IsTrue(rathalos.Size() == 6);
			rathalos["Drops"];
			Assert::IsTrue(rathalos.Size() == 6);

			auto outOfBoundsException = [&rathalos] {rathalos[7]; };
			Assert::ExpectException<exception>(outOfBoundsException);
		}

		TEST_METHOD(TestIndexOperatorBracket)
		{
			Scope rathalos;

			rathalos["Name"];
			rathalos[0];
			Assert::IsTrue(rathalos[0] == rathalos["Name"]);
			rathalos["Model"];
			rathalos[1];
			Assert::IsTrue(rathalos[1] == rathalos["Model"]);
			rathalos["Health"];
			rathalos[2];
			Assert::IsTrue(rathalos[2] == rathalos["Health"]);
			rathalos["Size"];
			rathalos[3];
			Assert::IsTrue(rathalos[3] == rathalos["Size"]);
			rathalos["Move Set"];
			rathalos[4];
			Assert::IsTrue(rathalos[4] == rathalos["Move Set"]);
			rathalos["Drops"];
			rathalos[5];
			Assert::IsTrue(rathalos[5] == rathalos["Drops"]);

			auto emptyKeyException = [&rathalos] {rathalos.AppendScope(""); };
			Assert::ExpectException<exception>(emptyKeyException);
		}

		TEST_METHOD(TestAppendScope)
		{
			srand(static_cast<unsigned int>(time(NULL)));

			Scope rathalos;


			rathalos.Append("Name");
			rathalos.Append("Model");
			rathalos.Append("Health");
			rathalos.Append("Size");
			Scope & moveSet = (rathalos.AppendScope("Move Set"));
			Scope & drops = rathalos.AppendScope("Drops");
			
			Scope & fireball = (moveSet.AppendScope("Fireball"));
			Scope & talonAttack = (moveSet.AppendScope("Talon Attack"));
			Scope & tailSpin = (moveSet.AppendScope("Tail Spin"));
			
			fireball.Append("Damage").PushBack(rand());
			fireball.Append("Knockback").PushBack(rand());
			fireball.Append("StausEffect").PushBack(rand());
			
			talonAttack.Append("Damage").PushBack(rand());
			talonAttack.Append("Knockback").PushBack(rand());
			talonAttack.Append("StausEffect").PushBack(rand());

			tailSpin.Append("Damage").PushBack(rand());
			tailSpin.Append("Knockback").PushBack(rand());
			tailSpin.Append("StausEffect").PushBack(rand());
			
			drops.Append("Rathalos Scale");
			drops.Append("Rathalos Webbing");
			drops.Append("Rathalos Plate");
			drops.Append("Rathalos Gem");
			drops.Append("Rathalos Family Photo");
			
			auto emptyKeyException = [&rathalos] {rathalos.AppendScope(""); };
			Assert::ExpectException<exception>(emptyKeyException);
		}



		TEST_METHOD(PaulAppendScope)
		{
			Scope scope;
			string a = "A";
			string b = "B";
			string c = "C";

			size_t index = 0;

			Scope& aScope = scope.AppendScope(a);
			Assert::IsTrue((size_t)1 == scope.Size());
			Assert::IsTrue(&scope == aScope.GetParent());

			Datum* aScopeDatum = scope.Find(a);
			Assert::IsNotNull(aScopeDatum);
			Assert::IsTrue(Datum::DatumType::Scope == aScopeDatum->Type());
			Assert::IsTrue(&aScope == aScopeDatum->Get<Scope*>());
			Assert::IsTrue(aScopeDatum == &(scope[index]));

			Scope& bScope = scope.AppendScope(b);
			Assert::IsTrue((size_t)2 == scope.Size());
			Assert::IsTrue(&scope == bScope.GetParent());

			Datum* bScopeDatum = scope.Find(b);
			Assert::IsTrue(bScopeDatum != nullptr);
			Assert::IsTrue(Datum::DatumType::Scope == bScopeDatum->Type());
			Assert::IsTrue(&bScope == bScopeDatum->Get<Scope*>());
			Assert::IsTrue(bScopeDatum == &(scope[++index]));

			Scope& cScope = scope.AppendScope(c);
			Assert::IsTrue((size_t)3 == scope.Size());
			Assert::IsTrue(&scope == cScope.GetParent());

			Datum* cScopeDatum = scope.Find(c);
			Assert::IsTrue(cScopeDatum != nullptr);
			Assert::IsTrue(Datum::DatumType::Scope == cScopeDatum->Type());
			Assert::IsTrue(&cScope == cScopeDatum->Get<Scope*>());
			Assert::IsTrue(cScopeDatum == &(scope[2]));


			Scope& anotherCScope = scope.AppendScope(c);
			Assert::IsTrue((size_t)3 == scope.Size());
			Assert::IsTrue(&scope == anotherCScope.GetParent());
			cScopeDatum = scope.Find(c);
			Assert::IsTrue(cScopeDatum != nullptr);
			Assert::IsTrue(Datum::DatumType::Scope == cScopeDatum->Type());
			Assert::IsTrue(&anotherCScope == cScopeDatum->Get<Scope*>(1));

			delete &aScope;
			delete &bScope;

		}

		TEST_METHOD(TestFind)
		{
			Scope rathalos;

			Assert::IsTrue(nullptr == rathalos.Find("Name"));
			Assert::IsTrue(nullptr == rathalos.Find("Model"));
			Assert::IsTrue(nullptr == rathalos.Find("Health"));
			Assert::IsTrue(nullptr == rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr == rathalos.Find("Drops"));
			rathalos.Append("Name");
			rathalos.Append("Name");
			Assert::IsTrue(nullptr != rathalos.Find("Name"));
			Assert::IsTrue(nullptr == rathalos.Find("Model"));
			Assert::IsTrue(nullptr == rathalos.Find("Health"));
			Assert::IsTrue(nullptr == rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr == rathalos.Find("Drops"));
			rathalos.Append("Model");
			Assert::IsTrue(nullptr != rathalos.Find("Name"));
			Assert::IsTrue(nullptr != rathalos.Find("Model"));
			Assert::IsTrue(nullptr == rathalos.Find("Health"));
			Assert::IsTrue(nullptr == rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr == rathalos.Find("Drops"));
			rathalos.Append("Health");
			Assert::IsTrue(nullptr != rathalos.Find("Name"));
			Assert::IsTrue(nullptr != rathalos.Find("Model"));
			Assert::IsTrue(nullptr != rathalos.Find("Health"));
			Assert::IsTrue(nullptr == rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr == rathalos.Find("Drops"));
			rathalos.Append("Move Set");
			Assert::IsTrue(nullptr != rathalos.Find("Name"));
			Assert::IsTrue(nullptr != rathalos.Find("Model"));
			Assert::IsTrue(nullptr != rathalos.Find("Health"));
			Assert::IsTrue(nullptr != rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr == rathalos.Find("Drops"));
			rathalos.Append("Drops");
			Assert::IsTrue(nullptr != rathalos.Find("Name"));
			Assert::IsTrue(nullptr != rathalos.Find("Model"));
			Assert::IsTrue(nullptr != rathalos.Find("Health"));
			Assert::IsTrue(nullptr != rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr != rathalos.Find("Drops"));
			rathalos.Append("Drops");
			Assert::IsTrue(nullptr != rathalos.Find("Name"));
			Assert::IsTrue(nullptr != rathalos.Find("Model"));
			Assert::IsTrue(nullptr != rathalos.Find("Health"));
			Assert::IsTrue(nullptr != rathalos.Find("Move Set"));
			Assert::IsTrue(nullptr != rathalos.Find("Drops"));

			auto emptyKeyException = [&rathalos] {rathalos.Find(""); };
			Assert::ExpectException<exception>(emptyKeyException);
		}

		TEST_METHOD(TestFindName)
		{
			Scope rathalos;

			Scope & moveSet = (rathalos.AppendScope("Move Set"));
			Scope & drops = (rathalos.AppendScope("Drops"));

			Scope & fireball = (moveSet.AppendScope("Fireball"));
			Scope & talonAttack = (moveSet.AppendScope("Talon Attack"));
			Scope & tailSpin = (moveSet.AppendScope("Tail Spin"));

			Assert::IsTrue(rathalos.FindName(&moveSet) == "Move Set");
			Assert::IsTrue(moveSet.FindName(&fireball) == "Fireball");
			Assert::IsTrue(moveSet.FindName(&talonAttack) == "Talon Attack");
			Assert::IsTrue(moveSet.FindName(&tailSpin) == "Tail Spin");
			Assert::IsTrue(rathalos.FindName(&drops) == "Drops");

		}

		TEST_METHOD(TestSearch)
		{
			Scope rathalos;
			Scope dummy;
			Scope* foundScope = &dummy;

			Scope & moveSet = (rathalos.AppendScope("Move Set"));
			Scope & drops = (rathalos.AppendScope("Drops"));

			Scope & fireball = (moveSet.AppendScope("Fireball"));
			Scope & talonAttack = (moveSet.AppendScope("Talon Attack"));
			Scope & tailSpin = (moveSet.AppendScope("Tail Spin"));


			Assert::IsTrue(fireball.Search("Move Set") == rathalos.Find("Move Set"));
			fireball.Search("Move Set", &foundScope);
			Assert::IsTrue(foundScope == &rathalos);
			Assert::IsTrue(moveSet.FindName(&talonAttack) == "Talon Attack");
			Assert::IsTrue(moveSet.FindName(&tailSpin) == "Tail Spin");
			Assert::IsTrue(rathalos.FindName(&drops) == "Drops");

			auto emptyKeyException = [&rathalos] {rathalos.Search(""); };
			Assert::ExpectException<exception>(emptyKeyException);
		}

		TEST_METHOD(TestAdopt)
		{
			Scope rathalos;

			Scope & moveSet = (rathalos.AppendScope("Move Set"));
			Scope & drops = (rathalos.AppendScope("Drops"));

			Scope & fireball = (moveSet.AppendScope("Fireball"));
			Scope & talonAttack = (moveSet.AppendScope("Talon Attack"));
			Scope & tailSpin = (moveSet.AppendScope("Tail Spin"));

			Assert::IsTrue(rathalos.FindName(&moveSet) == "Move Set");
			Assert::IsTrue(moveSet.FindName(&fireball) == "Fireball");
			Assert::IsTrue(moveSet.FindName(&talonAttack) == "Talon Attack");
			Assert::IsTrue(moveSet.FindName(&tailSpin) == "Tail Spin");
			Assert::IsTrue(rathalos.FindName(&drops) == "Drops");

			Scope azureRathalos;

			Assert::IsTrue(azureRathalos.Size() == 0);
			Assert::IsTrue(rathalos[1].Size() == 1);
			azureRathalos.Adopt(drops, "Drops");
			Assert::IsTrue(rathalos[1].Size() == 0);
			Assert::IsTrue(azureRathalos.Size() == 1);
			Assert::IsTrue(azureRathalos[0].Size() == 1);
			Assert::IsTrue(azureRathalos.FindName(&drops) == "Drops");

			auto hasAncestorException = [&rathalos, &fireball] {fireball.Adopt(rathalos, "Rathalos"); };
			Assert::ExpectException<exception>(hasAncestorException);
		}
		
		TEST_METHOD(PaulAdoptTest)
		{
			Scope scope;
			Scope scopeChild;
			Assert::IsTrue(scopeChild.GetParent() == nullptr);

			scope.Adopt(scopeChild, "Adopt");
			Assert::IsTrue(&scope == scopeChild.GetParent());
		}
		

		TEST_METHOD(PaulOrphanTest)
		{
			Scope scope;
			Scope& scopeReference = scope.AppendScope("TEST");
			Assert::IsTrue(&scope == scopeReference.GetParent());

			scopeReference.Orphan();
			Assert::IsTrue(scopeReference.GetParent() == nullptr);

			delete &scopeReference;
		}

		TEST_METHOD(TestEquivalenceOperator)
		{
			Scope rathalos;

			Scope & moveSet = (rathalos.AppendScope("Move Set"));
			Scope & drops = (rathalos.AppendScope("Drops"));

			Scope & fireball = (moveSet.AppendScope("Fireball"));
			Scope & talonAttack = (moveSet.AppendScope("Talon Attack"));
			Scope & tailSpin = (moveSet.AppendScope("Tail Spin"));

			fireball.Append("Damage").PushBack(50);
			fireball.Append("Knockback").PushBack(50);
			fireball.Append("StausEffect").PushBack(50);

			talonAttack.Append("Damage").PushBack(50);
			talonAttack.Append("Knockback").PushBack(50);
			talonAttack.Append("StausEffect").PushBack(50);

			tailSpin.Append("Damage").PushBack(50);
			tailSpin.Append("Knockback").PushBack(50);
			tailSpin.Append("StausEffect").PushBack(50);

			drops.Append("Rathalos Scale");
			drops.Append("Rathalos Webbing");
			drops.Append("Rathalos Plate");
			drops.Append("Rathalos Gem");
			drops.Append("Rathalos Family Photo");

			Scope azureRathalos;
			
			Scope & azureMoveSet = (azureRathalos.AppendScope("Move Set"));
			Scope & azureDrops = (azureRathalos.AppendScope("Drops"));

			Scope & azureFireball = (azureMoveSet.AppendScope("Fireball"));
			Scope & azureTalonAttack= (azureMoveSet.AppendScope("Talon Attack"));
			Scope & azureTailSpin = (azureMoveSet.AppendScope("Tail Spin"));
			
			azureFireball.Append("Damage").PushBack(50);
			azureFireball.Append("Knockback").PushBack(50);
			azureFireball.Append("StausEffect").PushBack(50);

			azureTalonAttack.Append("Damage").PushBack(50);
			azureTalonAttack.Append("Knockback").PushBack(50);
			azureTalonAttack.Append("StausEffect").PushBack(50);

			azureTailSpin.Append("Damage").PushBack(50);
			azureTailSpin.Append("Knockback").PushBack(50);
			azureTailSpin.Append("StausEffect").PushBack(50);

			azureDrops.Append("Rathalos Scale");
			azureDrops.Append("Rathalos Webbing");
			azureDrops.Append("Rathalos Plate");
			azureDrops.Append("Rathalos Gem");
			azureDrops.Append("Rathalos Family Photo");

			Scope silverRathalos;

			Scope & silverMoveSet = (silverRathalos.AppendScope("Move Set"));
			Scope & silverDrops = (silverRathalos.AppendScope("Drops"));

			Scope & silverFireball = (silverMoveSet.AppendScope("Fireball"));
			Scope & silverTalonAttack = (silverMoveSet.AppendScope("Talon Attack"));
			Scope & silverTailSpin = (silverMoveSet.AppendScope("Tail Spin"));

			silverFireball.Append("Damage").PushBack(500);
			silverFireball.Append("Knockback").PushBack(500);
			silverFireball.Append("StausEffect").PushBack(500);

			silverTalonAttack.Append("Damage").PushBack(500);
			silverTalonAttack.Append("Knockback").PushBack(500);
			silverTalonAttack.Append("StausEffect").PushBack(500);

			silverTailSpin.Append("Damage").PushBack(500);
			silverTailSpin.Append("Knockback").PushBack(500);
			silverTailSpin.Append("StausEffect").PushBack(500);

			silverDrops.Append("Rathalos Scale");
			silverDrops.Append("Rathalos Webbing");
			silverDrops.Append("Rathalos Plate");
			silverDrops.Append("Rathalos Gem");
			silverDrops.Append("Rathalos Family Photo");

			Scope mysteryMachine;

			Scope& carParts = mysteryMachine.AppendScope("Car Parts");
			Scope & chasis = carParts.AppendScope("Chasis");
			Scope & engine = carParts.AppendScope("Engine");
			Scope & steeringWheel = carParts.AppendScope("Steering Wheel");

			chasis.Append("Wheels").PushBack(50);
			chasis.Append("Axels").PushBack(50);
			chasis.Append("Weight").PushBack(50);

			engine.Append("Cylinders").PushBack(50);
			engine.Append("Horsepower").PushBack(50);
			engine.Append("Weight").PushBack(50);

			steeringWheel.Append("Circumference").PushBack(50);
			steeringWheel.Append("Resistance").PushBack(50);
			steeringWheel.Append("Weight").PushBack(50);

			Scope& gang = mysteryMachine.AppendScope("Gang");

			gang.AppendScope("Shaggy");
			gang.AppendScope("Scooby");
			gang.AppendScope("Velma");
			gang.AppendScope("Daphne");
			gang.AppendScope("Shaggy");
			gang.AppendScope("Scooby");
			gang.AppendScope("Fred");

			Assert::IsTrue(rathalos == azureRathalos);
			Assert::IsTrue(rathalos != silverRathalos);
			Assert::IsTrue(azureRathalos != silverRathalos);
			Assert::IsTrue(azureRathalos != mysteryMachine);
			Assert::IsTrue(rathalos != mysteryMachine);
			Assert::IsTrue(silverRathalos != mysteryMachine);
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			Scope rathalos;

			Scope & moveSet = (rathalos.AppendScope("Move Set"));
			Scope & drops = (rathalos.AppendScope("Drops"));

			Scope & fireball = (moveSet.AppendScope("Fireball"));
			Scope & talonAttack = (moveSet.AppendScope("Talon Attack"));
			Scope & tailSpin = (moveSet.AppendScope("Tail Spin"));

			fireball.Append("Damage").PushBack(rand());
			fireball.Append("Knockback").PushBack(rand());
			fireball.Append("StausEffect").PushBack(rand());

			talonAttack.Append("Damage").PushBack(rand());
			talonAttack.Append("Knockback").PushBack(rand());
			talonAttack.Append("StausEffect").PushBack(rand());

			tailSpin.Append("Damage").PushBack(rand());
			tailSpin.Append("Knockback").PushBack(rand());
			tailSpin.Append("StausEffect").PushBack(rand());

			drops.Append("Rathalos Scale");
			drops.Append("Rathalos Webbing");
			drops.Append("Rathalos Plate");
			drops.Append("Rathalos Gem");
			drops.Append("Rathalos Family Photo");

			Scope azureRathalos = rathalos;

			
			Assert::IsTrue(azureRathalos == rathalos);
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ScopeTest::sStartMemState;
}