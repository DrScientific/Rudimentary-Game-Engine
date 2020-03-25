#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "json/json.h"
#include <string>
#include <sstream>
#include "JsonParseMaster.h"
#include "IIntegerJsonParseHelper.h"
#include "IDepthTestParseHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(JsonCppTest)
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
			JsonParseMaster master;
			master.SetSharedData(&sharedInt);
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
			JsonParseMaster master(&sharedInt);
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
			JsonParseMaster master(&sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.Parse(R"({ "integer" : 100 })"s));

			master.AddHelper(intHandler);

			Assert::IsTrue(master.Parse(R"({ "integer" : 100 })"s));

			IIntegerJsonParseHelper::SharedData tempInt;
			tempInt.Initialize();
			JsonParseMaster movedMaster(&tempInt);
			movedMaster = std::move(master);

			Assert::IsTrue(movedMaster.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}

		TEST_METHOD(TestMoveConstructor)
		{
			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(&sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.AddHelper(intHandler);

			master.Initialize();
			master.Parse(R"({ "integer" : 100 })"s);

			JsonParseMaster movedMaster(std::move(master));

			Assert::IsTrue(movedMaster.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}


		TEST_METHOD(TestFileParsing)
		{
			string const fileName = "TestFile.json";
			string const inputString = R"({ "integer" : 100 })"s;

			ofstream outputFile(fileName);
			Assert::IsFalse(outputFile.bad());

			outputFile << inputString;
			outputFile.close();


			IIntegerJsonParseHelper::SharedData sharedInt;
			sharedInt.Initialize();
			JsonParseMaster master(&sharedInt);
			IIntegerJsonParseHelper intHandler;

			master.Initialize();
			Assert::IsFalse(master.ParseFromFile("TestFile.json"));

			master.AddHelper(intHandler);
			
			Assert::IsTrue(master.ParseFromFile("TestFile.json"));

			Assert::IsTrue(master.GetFileName() == "TestFile.json");

			Assert::IsTrue(master.GetSharedData()->As<IIntegerJsonParseHelper::SharedData>()->parsedInt == 100);
		}

		TEST_METHOD(TestParseIfStream)
		{
			string const fileName = "TestFile.json";
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
			JsonParseMaster master(&sharedInt);
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
			JsonParseMaster master(&sharedInt);
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
			JsonParseMaster master;
			master.SetSharedData(&sharedDepth);
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
			JsonParseMaster master;
			master.SetSharedData(&sharedDepth);
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



	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState JsonCppTest::sStartMemState;
}