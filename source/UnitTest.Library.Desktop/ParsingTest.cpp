#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "json/json.h"
#include <string>
#include <sstream>
#include "JsonParseMaster.h"
#include "IIntegerJsonParseHelper.h"
#include "IDepthTestParseHelper.h"
#include "ScopeJsonParseHelper.h"
#include "Scope.h"
#include "AttributedFoo.h"
#include "TypeManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ParsingTest)
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

		TEST_METHOD(TestSimpleDeserialization)
		{
			stringstream inputStream;
			inputStream << R"({ "Health": { "type": "integer", "value" : 100 }})"s;

			Json::Value root;
			inputStream >> root;


			Logger::WriteMessage(root["Health"]["value"].toStyledString().c_str());
		}

		TEST_METHOD(TestIntegerJsonParser)
		{
			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			master.SetSharedData(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(R"({ "integer" : 100 })"s));

			master.AddHelper(intHandler);

			Assert::IsTrue(master.Parse(R"({ "integer" : 100 })"s));


			Assert::IsTrue(master.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}

		TEST_METHOD(TestClone)
		{
			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(R"({ "integer" : 100 })"s));

			master.AddHelper(intHandler);

			Assert::IsTrue(master.Parse(R"({ "integer" : 100 })"s));

			JsonParseMaster* clonedMaster = master.Clone();

			Assert::IsTrue(clonedMaster->GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 0);
			Assert::IsTrue(clonedMaster->GetSharedData()->GetJsonParseMaster() == clonedMaster);
			Assert::IsTrue(clonedMaster->GetFileName() == "");

			clonedMaster->Initialize();
			Assert::IsTrue(clonedMaster->Parse(R"({ "integer" : 100 })"s));
			Assert::IsTrue(clonedMaster->GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);

			delete clonedMaster;
		}

		TEST_METHOD(TestMoveAssignment)
		{
			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(R"({ "integer" : 100 })"s));

			master.AddHelper(intHandler);

			Assert::IsTrue(master.Parse(R"({ "integer" : 100 })"s));

			IIntegerJsonParseHelper::SharedData tempInt;
			tempInt.Initialize();
			JsonParseMaster movedMaster(tempInt);
			movedMaster = std::move(master);

			Assert::IsTrue(movedMaster.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.AddHelper(intHandler);

			master.Initialize();
			master.Parse(R"({ "integer" : 100 })"s);

			JsonParseMaster movedMaster(std::move(master));

			Assert::IsTrue(movedMaster.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}


		TEST_METHOD(TestFileParsing)
		{
			string const fileName = "Content/TestFile.json";
			string const inputString = R"({ "integer" : 100 })"s;

			ofstream outputFile(fileName);
			Assert::IsFalse(outputFile.bad());

			outputFile << inputString;
			outputFile.close();


			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.ParseFromFile("Content/TestFile.json"));

			master.AddHelper(intHandler);
			
			Assert::IsTrue(master.ParseFromFile("Content/TestFile.json"));

			Assert::IsTrue(master.GetFileName() == "Content/TestFile.json");

			Assert::IsTrue(master.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}

		TEST_METHOD(TestParseIfStream)
		{
			string const fileName = "Content/TestFile.json";
			string const inputString = R"({ "integer" : 100 })"s;

			ofstream outputFile(fileName);
			Assert::IsFalse(outputFile.bad());

			outputFile << inputString;
			outputFile.close();

			std::ifstream fileStream;
			fileStream.open(fileName);
			Assert::IsFalse(fileStream.bad());

			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(fileStream));
			
			fileStream.close();

			master.AddHelper(intHandler);
			
			fileStream.open(fileName);
			Assert::IsFalse(fileStream.bad());

			Assert::IsTrue(master.Parse(fileStream));

			Assert::IsTrue(master.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);

			fileStream.close();
		}

		TEST_METHOD(TestRemoveHelper)
		{
			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(R"({ "integer" : 100 })"s));

			master.AddHelper(intHandler);

			Assert::IsTrue(master.Parse(R"({ "integer" : 100 })"s));

			master.RemoveHelper(intHandler);

			Assert::IsFalse(master.Parse(R"({ "integer" : 100 })"s));
		}

		TEST_METHOD(TestDepthParser)
		{
			IDepthTestParseHelper::SharedData sharedDepth;
			sharedDepth.Initialize();
			JsonParseMaster master(sharedDepth);
			master.SetSharedData(sharedDepth);
			IDepthTestParseHelper depthHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse( R"({ "Health": { "type": "integer", "value" : 100 }})"s));

			master.AddHelper(depthHandler);

			master.Initialize();

			Assert::IsTrue(master.Parse(R"({ "One": { "Two": { "Three": { "Four" : 0 } } } })"s));

			size_t maxDepth = master.GetSharedData()->As<IDepthTestParseHelper::SharedData>()->mMaxDepth;
			Assert::IsTrue( maxDepth == 4);
		}

		TEST_METHOD(TestDepthParserClone)
		{
			IDepthTestParseHelper::SharedData sharedDepth;
			sharedDepth.Initialize();
			JsonParseMaster master(sharedDepth);
			master.SetSharedData(sharedDepth);
			IDepthTestParseHelper depthHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(R"({ "Health": { "type": "integer", "value" : 100 }})"s));

			master.AddHelper(depthHandler);

			master.Initialize();

			Assert::IsTrue(master.Parse(R"({ "One": { "Two": { "Three": { "Four" : 0 } } } })"s));

			size_t maxDepth = master.GetSharedData()->As<IDepthTestParseHelper::SharedData>()->mMaxDepth;
			Assert::IsTrue(maxDepth == 4);

			JsonParseMaster* clonedMaster = master.Clone();

			Assert::IsTrue(clonedMaster->GetSharedData()->As<IDepthTestParseHelper::SharedData>()->mMaxDepth == 0);
			Assert::IsTrue(clonedMaster->GetSharedData()->GetJsonParseMaster() == clonedMaster);
			Assert::IsTrue(clonedMaster->GetFileName() == "");

			clonedMaster->Initialize();
			Assert::IsTrue(clonedMaster->Parse((R"({ "One": { "Two": { "Three": { "Four" : 0 } } } })"s)));
			Assert::IsTrue(clonedMaster->GetSharedData()->As<IDepthTestParseHelper::SharedData>()->mMaxDepth == 4);

			delete clonedMaster;
		}


		TEST_METHOD(TestScopeParser)
		{
			shared_ptr sharedScope = make_shared<Scope>();
			ScopeJsonParseHelper::SharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			master.Initialize();

			Assert::IsFalse(master.ParseFromFile("Content/scopeTest.json"));

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/scopeTest.json"));

			Scope & ourScope = sharedData.GetScope();

			Assert::IsTrue(ourScope.Size() == 8);

			Assert::IsTrue(ourScope["A"].Front<string>() == "A");
			Assert::IsTrue(ourScope["B"].Front<float>() == 66.1f);
			Assert::IsTrue(ourScope["C"].Front<int>() == 67);
			Assert::IsTrue(ourScope["D"].Front<float>() == 68.f);
			Assert::IsTrue(ourScope["E"].Front<int>() == 69);
			Assert::IsTrue(ourScope["F"].Front<string>() == "F");
			Assert::IsTrue(ourScope["G"].Front<vec4>() == vec4(1.0f,2.0f,3.0f,4.0f));
			Assert::IsTrue(ourScope["H"].Front<mat4x4>() == mat4x4(1, 1, 1, 1 , 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4));
		}

		TEST_METHOD(TestNestedScopeParser)
		{
			shared_ptr sharedScope = make_shared<Scope>();
			ScopeJsonParseHelper::SharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			master.Initialize();

			Assert::IsFalse(master.ParseFromFile("Content/monsters.json"));

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/monsters.json"));

			Scope & ourScope = sharedData.GetScope();

			Scope & rathalosScope = ourScope["Rathalos"][0];

			Scope & rathalosAttacksScope = rathalosScope["Attacks"][0];

			Scope & rathalosFireballScope = rathalosAttacksScope["Fireball"][0];

			Scope & rathalosTailSpinScope = rathalosAttacksScope["TailSpin"][0];

			Scope & rathalosClawAttackScope = rathalosAttacksScope["ClawAttack"][0];

			Scope & rathianScope = ourScope["Rathian"][0];

			Scope & rathianAttacksScope = rathianScope["Attacks"][0];

			Scope & rathianFireballScope = rathianAttacksScope["Fireball"][0];

			Scope & rathianTailSpinScope = rathianAttacksScope["TailSpin"][0];

			Scope & rathianClawAttackScope = rathianAttacksScope["ClawAttack"][0];

			string rathalosDrops[4] = { "Rathalos Plate", "Rathalos Webbing", "Wing Talon", "Rathalos Tail"};

			string rathianDrops[4] = { "Rathian Plate", "Rathian Webbing", "Wing Talon", "Rathian Tail" };


			Assert::IsTrue(rathalosFireballScope["Damage"].Get<int>(0) == 111);
			Assert::IsTrue(rathalosFireballScope["KnockBack"].Get<float>(0) == 111.f);
			Assert::IsTrue(rathalosFireballScope["StatusEffect"].Get<string>(0) == "burning");
			Assert::IsTrue(rathalosTailSpinScope["Damage"].Get<int>(0) == 222);
			Assert::IsTrue(rathalosTailSpinScope["KnockBack"].Get<float>(0) == 222.f);
			Assert::IsTrue(rathalosTailSpinScope["StatusEffect"].Get<string>(0) == "none");
			Assert::IsTrue(rathalosClawAttackScope["Damage"].Get<int>(0) == 333);
			Assert::IsTrue(rathalosClawAttackScope["KnockBack"].Get<float>(0) == 333.f);
			Assert::IsTrue(rathalosClawAttackScope["StatusEffect"].Get<string>(0) == "poison");
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(0) == rathalosDrops[0]);
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(1) == rathalosDrops[1]);
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(2) == rathalosDrops[2]);
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(3) == rathalosDrops[3]);
			Assert::IsTrue(rathalosScope["Health"] == 8000);
			Assert::IsTrue(rathalosScope["Size"] == 7777.7777f);
			Assert::IsTrue(rathalosScope["Position"] == vec4(1.0f, 2.0f, 3.0f, 4.0f));
			Assert::IsTrue(rathalosScope["Rotation"] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));

			Assert::IsTrue(rathianFireballScope["Damage"].Get<int>(0) == 444);
			Assert::IsTrue(rathianFireballScope["KnockBack"].Get<float>(0) == 444.f);
			Assert::IsTrue(rathianFireballScope["StatusEffect"].Get<string>(0) == "burning");
			Assert::IsTrue(rathianTailSpinScope["Damage"].Get<int>(0) == 555);
			Assert::IsTrue(rathianTailSpinScope["KnockBack"].Get<float>(0) == 555.f);
			Assert::IsTrue(rathianTailSpinScope["StatusEffect"].Get<string>(0) == "poison");
			Assert::IsTrue(rathianClawAttackScope["Damage"].Get<int>(0) == 666);
			Assert::IsTrue(rathianClawAttackScope["KnockBack"].Get<float>(0) == 666.f);
			Assert::IsTrue(rathianClawAttackScope["StatusEffect"].Get<string>(0) == "none");
			Assert::IsTrue(rathianScope["Drops"].Get<string>(0) == rathianDrops[0]);
			Assert::IsTrue(rathianScope["Drops"].Get<string>(1) == rathianDrops[1]);
			Assert::IsTrue(rathianScope["Drops"].Get<string>(2) == rathianDrops[2]);
			Assert::IsTrue(rathianScope["Drops"].Get<string>(3) == rathianDrops[3]);
			Assert::IsTrue(rathianScope["Health"] == 9000);
			Assert::IsTrue(rathianScope["Size"] == 8888.8888f);
			Assert::IsTrue(rathianScope["Position"] == vec4(1.0f, 2.0f, 3.0f, 4.0f));
			Assert::IsTrue(rathianScope["Rotation"] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));
		}

		TEST_METHOD(TestArrayScopeParser)
		{
			shared_ptr sharedScope = make_shared<Scope>();
			ScopeJsonParseHelper::SharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			master.Initialize();

			Assert::IsFalse(master.ParseFromFile("Content/monsterArray.json"));

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/monsterArray.json"));

			Scope & ourScope = sharedData.GetScope();

			Scope & rathalosScope = ourScope["Monsters"][0]["Rathalos"][0];

			Scope & rathalosAttacksScope = rathalosScope["Attacks"][0];

			Scope & rathalosFireballScope = rathalosAttacksScope["Fireball"][0];

			Scope & rathalosTailSpinScope = rathalosAttacksScope["TailSpin"][0];

			Scope & rathalosClawAttackScope = rathalosAttacksScope["ClawAttack"][0];

			Scope & rathianScope = ourScope["Monsters"][1]["Rathian"][0];

			Scope & rathianAttacksScope = rathianScope["Attacks"][0];

			Scope & rathianFireballScope = rathianAttacksScope["Fireball"][0];

			Scope & rathianTailSpinScope = rathianAttacksScope["TailSpin"][0];

			Scope & rathianClawAttackScope = rathianAttacksScope["ClawAttack"][0];

			string rathalosDrops[4] = { "Rathalos Plate", "Rathalos Webbing", "Wing Talon", "Rathalos Tail" };

			string rathianDrops[4] = { "Rathian Plate", "Rathian Webbing", "Wing Talon", "Rathian Tail" };


			Assert::IsTrue(rathalosFireballScope["Damage"].Get<int>(0) == 111);
			Assert::IsTrue(rathalosFireballScope["KnockBack"].Get<float>(0) == 111.f);
			Assert::IsTrue(rathalosFireballScope["StatusEffect"].Get<string>(0) == "burning");
			Assert::IsTrue(rathalosTailSpinScope["Damage"].Get<int>(0) == 222);
			Assert::IsTrue(rathalosTailSpinScope["KnockBack"].Get<float>(0) == 222.f);
			Assert::IsTrue(rathalosTailSpinScope["StatusEffect"].Get<string>(0) == "none");
			Assert::IsTrue(rathalosClawAttackScope["Damage"].Get<int>(0) == 333);
			Assert::IsTrue(rathalosClawAttackScope["KnockBack"].Get<float>(0) == 333.f);
			Assert::IsTrue(rathalosClawAttackScope["StatusEffect"].Get<string>(0) == "poison");
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(0) == rathalosDrops[0]);
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(1) == rathalosDrops[1]);
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(2) == rathalosDrops[2]);
			Assert::IsTrue(rathalosScope["Drops"].Get<string>(3) == rathalosDrops[3]);
			Assert::IsTrue(rathalosScope["Health"] == 8000);
			Assert::IsTrue(rathalosScope["Size"] == 7777.7777f);
			Assert::IsTrue(rathalosScope["Position"] == vec4(1.0f, 2.0f, 3.0f, 4.0f));
			Assert::IsTrue(rathalosScope["Rotation"] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));

			Assert::IsTrue(rathianFireballScope["Damage"].Get<int>(0) == 444);
			Assert::IsTrue(rathianFireballScope["KnockBack"].Get<float>(0) == 444.f);
			Assert::IsTrue(rathianFireballScope["StatusEffect"].Get<string>(0) == "burning");
			Assert::IsTrue(rathianTailSpinScope["Damage"].Get<int>(0) == 555);
			Assert::IsTrue(rathianTailSpinScope["KnockBack"].Get<float>(0) == 555.f);
			Assert::IsTrue(rathianTailSpinScope["StatusEffect"].Get<string>(0) == "poison");
			Assert::IsTrue(rathianClawAttackScope["Damage"].Get<int>(0) == 666);
			Assert::IsTrue(rathianClawAttackScope["KnockBack"].Get<float>(0) == 666.f);
			Assert::IsTrue(rathianClawAttackScope["StatusEffect"].Get<string>(0) == "none");
			Assert::IsTrue(rathianScope["Drops"].Get<string>(0) == rathianDrops[0]);
			Assert::IsTrue(rathianScope["Drops"].Get<string>(1) == rathianDrops[1]);
			Assert::IsTrue(rathianScope["Drops"].Get<string>(2) == rathianDrops[2]);
			Assert::IsTrue(rathianScope["Drops"].Get<string>(3) == rathianDrops[3]);
			Assert::IsTrue(rathianScope["Health"] == 9000);
			Assert::IsTrue(rathianScope["Size"] == 8888.8888f);
			Assert::IsTrue(rathianScope["Position"] == vec4(1.0f, 2.0f, 3.0f, 4.0f));
			Assert::IsTrue(rathianScope["Rotation"] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));
		}

		TEST_METHOD(TestAttributedFooParse)
		{
			AttributedFoo foo;
			shared_ptr sharedScope = make_shared<Scope>(foo);
			ScopeJsonParseHelper::SharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			master.Initialize();

			Assert::IsFalse(master.ParseFromFile("Content/AttributedFoo.json"));

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/AttributedFoo.json"));


			Assert::IsTrue(foo.ExternalInteger == 500);
			Assert::IsTrue(foo.ExternalFloat == 500.5);
			Assert::IsTrue(foo.ExternalString == "500.5");
			Assert::IsTrue(foo.ExternalVector == vec4(1.f,2.f,3.f,4.f));
			Assert::IsTrue(foo.ExternalMatrix == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));
			Assert::IsTrue(foo.ExternalIntegerArray[0] == 500);
			Assert::IsTrue(foo.ExternalIntegerArray[1] == 501);
			Assert::IsTrue(foo.ExternalIntegerArray[2] == 502);
			Assert::IsTrue(foo.ExternalIntegerArray[3] == 503);
			Assert::IsTrue(foo.ExternalIntegerArray[4] == 504);
			Assert::IsTrue(foo.ExternalFloatArray[0] == 500.5);
			Assert::IsTrue(foo.ExternalFloatArray[1] == 501.5);
			Assert::IsTrue(foo.ExternalFloatArray[2] == 502.5);
			Assert::IsTrue(foo.ExternalFloatArray[3] == 503.5);
			Assert::IsTrue(foo.ExternalFloatArray[4] == 504.5);
			Assert::IsTrue(foo.ExternalStringArray[0] == "500.5");
			Assert::IsTrue(foo.ExternalStringArray[1] == "501.5");
			Assert::IsTrue(foo.ExternalStringArray[2] == "502.5");
			Assert::IsTrue(foo.ExternalStringArray[3] == "503.5");
			Assert::IsTrue(foo.ExternalStringArray[4] == "504.5");
			Assert::IsTrue(foo.ExternalVectorArray[0] == vec4(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(foo.ExternalVectorArray[1] == vec4(2.f, 2.f, 2.f, 2.f));
			Assert::IsTrue(foo.ExternalVectorArray[2] == vec4(3.f, 3.f, 3.f, 3.f));
			Assert::IsTrue(foo.ExternalVectorArray[3] == vec4(4.f, 4.f, 4.f, 4.f));
			Assert::IsTrue(foo.ExternalVectorArray[4] == vec4(5.f, 5.f, 5.f, 5.f));
			Assert::IsTrue(foo.ExternalMatrixArray[0] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[1] == mat4x4(2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[2] == mat4x4(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[3] == mat4x4(4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[4] == mat4x4(5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f));
			//Assert::IsTrue(foo["NestedScope"][0]["NestedInteger"] == 0);
			//Assert::IsTrue(foo["NestedScopeArray"][0]["NestedInteger1"] == 1);
			//Assert::IsTrue(foo["NestedScopeArray"][1]["NestedInteger2"] == 2);
			//Assert::IsTrue(foo["NestedScopeArray"][2]["NestedInteger3"] == 3);
			//Assert::IsTrue(foo["NestedScopeArray"][3]["NestedInteger4"] == 4);
			//Assert::IsTrue(foo["NestedScopeArray"][4]["NestedInteger5"] == 5);
		}

		/*
		TEST_METHOD(TestCloneAndCreate)
		{
			AttributedFoo foo;
			shared_ptr sharedScope = make_shared<Scope>(foo);
			ScopeJsonParseHelper::SharedData sharedData(sharedScope);
			JsonParseMaster master(sharedData);
			ScopeJsonParseHelper scopeHelper;

			master.Initialize();

			Assert::IsFalse(master.ParseFromFile("Content/AttributedFoo.json"));

			master.AddHelper(scopeHelper);

			master.Initialize();

			Assert::IsTrue(master.ParseFromFile("Content/AttributedFoo.json"));

			Assert::IsTrue(foo.ExternalInteger == 500);
			Assert::IsTrue(foo.ExternalFloat == 500.5);
			Assert::IsTrue(foo.ExternalString == "500.5");
			Assert::IsTrue(foo.ExternalVector == vec4(1.f, 2.f, 3.f, 4.f));
			Assert::IsTrue(foo.ExternalMatrix == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));
			Assert::IsTrue(foo.ExternalIntegerArray[0] == 500);
			Assert::IsTrue(foo.ExternalIntegerArray[1] == 501);
			Assert::IsTrue(foo.ExternalIntegerArray[2] == 502);
			Assert::IsTrue(foo.ExternalIntegerArray[3] == 503);
			Assert::IsTrue(foo.ExternalIntegerArray[4] == 504);
			Assert::IsTrue(foo.ExternalFloatArray[0] == 500.5);
			Assert::IsTrue(foo.ExternalFloatArray[1] == 501.5);
			Assert::IsTrue(foo.ExternalFloatArray[2] == 502.5);
			Assert::IsTrue(foo.ExternalFloatArray[3] == 503.5);
			Assert::IsTrue(foo.ExternalFloatArray[4] == 504.5);
			Assert::IsTrue(foo.ExternalStringArray[0] == "500.5");
			Assert::IsTrue(foo.ExternalStringArray[1] == "501.5");
			Assert::IsTrue(foo.ExternalStringArray[2] == "502.5");
			Assert::IsTrue(foo.ExternalStringArray[3] == "503.5");
			Assert::IsTrue(foo.ExternalStringArray[4] == "504.5");
			Assert::IsTrue(foo.ExternalVectorArray[0] == vec4(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(foo.ExternalVectorArray[1] == vec4(2.f, 2.f, 2.f, 2.f));
			Assert::IsTrue(foo.ExternalVectorArray[2] == vec4(3.f, 3.f, 3.f, 3.f));
			Assert::IsTrue(foo.ExternalVectorArray[3] == vec4(4.f, 4.f, 4.f, 4.f));
			Assert::IsTrue(foo.ExternalVectorArray[4] == vec4(5.f, 5.f, 5.f, 5.f));
			Assert::IsTrue(foo.ExternalMatrixArray[0] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[1] == mat4x4(2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[2] == mat4x4(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[3] == mat4x4(4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f));
			Assert::IsTrue(foo.ExternalMatrixArray[4] == mat4x4(5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f));
			//Assert::IsTrue(foo["NestedScope"][0]["NestedInteger"] == 0);
			//Assert::IsTrue(foo["NestedScopeArray"][0]["NestedInteger1"] == 1);
			//Assert::IsTrue(foo["NestedScopeArray"][1]["NestedInteger2"] == 2);
			//Assert::IsTrue(foo["NestedScopeArray"][2]["NestedInteger3"] == 3);
			//Assert::IsTrue(foo["NestedScopeArray"][3]["NestedInteger4"] == 4);
			//Assert::IsTrue(foo["NestedScopeArray"][4]["NestedInteger5"] == 5);

			JsonParseMaster* clonedMaster = master.Clone();

			

			clonedMaster->Initialize();

			Assert::IsTrue(clonedMaster->ParseFromFile("Content/AttributedFoo.json"));

			
			Assert::IsTrue(clonedFoo.ExternalInteger == 500);
			Assert::IsTrue(clonedFoo.ExternalFloat == 500.5);
			Assert::IsTrue(clonedFoo.ExternalString == "500.5");
			Assert::IsTrue(clonedFoo.ExternalVector == vec4(1.f, 2.f, 3.f, 4.f));
			Assert::IsTrue(clonedFoo.ExternalMatrix == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f));
			Assert::IsTrue(clonedFoo.ExternalIntegerArray[0] == 500);
			Assert::IsTrue(clonedFoo.ExternalIntegerArray[1] == 501);
			Assert::IsTrue(clonedFoo.ExternalIntegerArray[2] == 502);
			Assert::IsTrue(clonedFoo.ExternalIntegerArray[3] == 503);
			Assert::IsTrue(clonedFoo.ExternalIntegerArray[4] == 504);
			Assert::IsTrue(clonedFoo.ExternalFloatArray[0] == 500.5);
			Assert::IsTrue(clonedFoo.ExternalFloatArray[1] == 501.5);
			Assert::IsTrue(clonedFoo.ExternalFloatArray[2] == 502.5);
			Assert::IsTrue(clonedFoo.ExternalFloatArray[3] == 503.5);
			Assert::IsTrue(clonedFoo.ExternalFloatArray[4] == 504.5);
			Assert::IsTrue(clonedFoo.ExternalStringArray[0] == "500.5");
			Assert::IsTrue(clonedFoo.ExternalStringArray[1] == "501.5");
			Assert::IsTrue(clonedFoo.ExternalStringArray[2] == "502.5");
			Assert::IsTrue(clonedFoo.ExternalStringArray[3] == "503.5");
			Assert::IsTrue(clonedFoo.ExternalStringArray[4] == "504.5");
			Assert::IsTrue(clonedFoo.ExternalVectorArray[0] == vec4(1.f, 1.f, 1.f, 1.f));
			Assert::IsTrue(clonedFoo.ExternalVectorArray[1] == vec4(2.f, 2.f, 2.f, 2.f));
			Assert::IsTrue(clonedFoo.ExternalVectorArray[2] == vec4(3.f, 3.f, 3.f, 3.f));
			Assert::IsTrue(clonedFoo.ExternalVectorArray[3] == vec4(4.f, 4.f, 4.f, 4.f));
			Assert::IsTrue(clonedFoo.ExternalVectorArray[4] == vec4(5.f, 5.f, 5.f, 5.f));
			Assert::IsTrue(clonedFoo.ExternalMatrixArray[0] == mat4x4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
			Assert::IsTrue(clonedFoo.ExternalMatrixArray[1] == mat4x4(2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f));
			Assert::IsTrue(clonedFoo.ExternalMatrixArray[2] == mat4x4(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f));
			Assert::IsTrue(clonedFoo.ExternalMatrixArray[3] == mat4x4(4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f));
			Assert::IsTrue(clonedFoo.ExternalMatrixArray[4] == mat4x4(5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f));
			

			delete clonedMaster;
		}
		*/


	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ParsingTest::sStartMemState;
}