#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "UnorderedMap.h"
#include "DefaultHashFunctorTemplates.h"

//TODO Hash map Resize test

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace UnitTests;

using UnorderedMapCharFoo = UnorderedMap<char*, Foo>;
using UnorderedMapFooString = UnorderedMap<Foo, std::string>;
using UnorderedMapString2 = UnorderedMap<std::string, std::string>;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(UnorderedMapTest)
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

		TEST_METHOD(DefaultConstructorAndDestructorTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap;
			UnorderedMapFooString fooStringUnorderedMap;
			UnorderedMapString2 stringStringUnorderedMap;
		}

		TEST_METHOD(InitializerListConstructorTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooUnorderedMap.Size() == 5);
			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "")};
			Assert::IsTrue(fooStringUnorderedMap.Size() == 5);
			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2UnorderedMap.Size() == 5);
		}

		TEST_METHOD(IteratorExceptionsTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap;

			UnorderedMapCharFoo::Iterator charFooBeginning = charFooUnorderedMap.begin();
			UnorderedMapCharFoo::Iterator ending = charFooUnorderedMap.end();
			UnorderedMapCharFoo::ConstIterator charFooCBeginning = charFooUnorderedMap.cbegin();
			UnorderedMapCharFoo::ConstIterator charFooCBeginningAssignment = charFooBeginning;
			UnorderedMapCharFoo::ConstIterator charFooCEnding = charFooUnorderedMap.cend();

			Assert::IsTrue(charFooBeginning == ending);
			Assert::IsTrue(charFooCBeginning == charFooCEnding);

			auto charFooDereferenceEndException = [&charFooUnorderedMap] { *charFooUnorderedMap.end(); };
			auto charFooArrowOperatorEndException = [&charFooUnorderedMap] { charFooUnorderedMap.end()->first; };
			auto charFooPreIncrementPastEndException = [&charFooUnorderedMap] { ++charFooUnorderedMap.end(); };
			auto charFooPostIncrementPastEndException = [&charFooUnorderedMap] { charFooUnorderedMap.end()++; };
			auto charFooBeginEqualEndAndIncrementPastEndException = [&charFooUnorderedMap] { ++charFooUnorderedMap.begin(); };
			auto charFooDereferenceCEndException = [&charFooUnorderedMap] { *charFooUnorderedMap.cend(); };
			auto charFooIncrementPastCEndException = [&charFooUnorderedMap] { ++charFooUnorderedMap.cend(); };
			auto charFooCBeginEqualCEndAndIncrementPastCEndException = [&charFooUnorderedMap] { ++charFooUnorderedMap.cbegin(); };

			Assert::ExpectException<std::exception>(charFooDereferenceEndException);
			Assert::ExpectException<std::exception>(charFooArrowOperatorEndException);
			Assert::ExpectException<std::exception>(charFooPreIncrementPastEndException);
			Assert::ExpectException<std::exception>(charFooPostIncrementPastEndException);
			Assert::ExpectException<std::exception>(charFooBeginEqualEndAndIncrementPastEndException);
			Assert::ExpectException<std::exception>(charFooDereferenceCEndException );
			Assert::ExpectException<std::exception>(charFooIncrementPastCEndException);
			Assert::ExpectException<std::exception>(charFooCBeginEqualCEndAndIncrementPastCEndException);
			


			UnorderedMapFooString fooStringUnorderedMap;

			UnorderedMapFooString::Iterator fooStringBeginning = fooStringUnorderedMap.begin();
			UnorderedMapFooString::Iterator fooStringEnding = fooStringUnorderedMap.end();
			UnorderedMapFooString::ConstIterator fooStringCBeginning = fooStringUnorderedMap.cbegin();
			UnorderedMapFooString::ConstIterator fooStringCEnding = fooStringUnorderedMap.cend();

			auto fooStringDereferenceEndException = [&fooStringUnorderedMap] { *fooStringUnorderedMap.end(); };
			auto fooStringArrowOperatorEndException = [&fooStringUnorderedMap] { fooStringUnorderedMap.end()->first; };
			auto fooStringIncrementPastEndException = [&fooStringUnorderedMap] { ++fooStringUnorderedMap.end(); };
			auto fooStringBeginEqualEndAndIncrementPastEndException = [&fooStringUnorderedMap] { ++fooStringUnorderedMap.begin(); };
			auto fooStringDereferenceCEndException = [&fooStringUnorderedMap] { *fooStringUnorderedMap.cend(); };
			auto fooStringIncrementPastCEndException = [&fooStringUnorderedMap] { ++fooStringUnorderedMap.cend(); };
			auto fooStringCBeginEqualCEndAndIncrementPastCEndException = [&fooStringUnorderedMap] { ++fooStringUnorderedMap.cbegin(); };

			Assert::ExpectException<std::exception>(fooStringDereferenceEndException);
			Assert::ExpectException<std::exception>(fooStringArrowOperatorEndException);
			Assert::ExpectException<std::exception>(fooStringIncrementPastEndException);
			Assert::ExpectException<std::exception>(fooStringBeginEqualEndAndIncrementPastEndException);
			Assert::ExpectException<std::exception>(fooStringDereferenceCEndException);
			Assert::ExpectException<std::exception>(fooStringIncrementPastCEndException);
			Assert::ExpectException<std::exception>(fooStringCBeginEqualCEndAndIncrementPastCEndException);



			UnorderedMapString2 string2UnorderedMap;

			UnorderedMapString2::Iterator string2Beginning = string2UnorderedMap.begin();
			UnorderedMapString2::Iterator string2Ending = string2UnorderedMap.end();
			UnorderedMapString2::ConstIterator string2CBeginning = string2UnorderedMap.cbegin();
			UnorderedMapString2::ConstIterator string2CEnding = string2UnorderedMap.cend();
			
			auto string2DereferenceEndException = [&string2UnorderedMap] { *string2UnorderedMap.end(); };
			auto string2ArrowOperatorEndException = [&string2UnorderedMap] { string2UnorderedMap.end()->first; };
			auto string2IncrementPastEndException = [&string2UnorderedMap] { ++string2UnorderedMap.end(); };
			auto string2BeginEqualEndAndIncrementPastEndException = [&string2UnorderedMap] { ++string2UnorderedMap.begin(); };
			auto string2DereferenceCEndException = [&string2UnorderedMap] { *string2UnorderedMap.cend(); };
			auto string2IncrementPastCEndException = [&string2UnorderedMap] { ++string2UnorderedMap.cend(); };
			auto string2CBeginEqualCEndAndIncrementPastCEndException = [&string2UnorderedMap] { ++string2UnorderedMap.cbegin(); };

			Assert::ExpectException<std::exception>(string2DereferenceEndException);
			Assert::ExpectException<std::exception>(string2ArrowOperatorEndException);
			Assert::ExpectException<std::exception>(string2IncrementPastEndException);
			Assert::ExpectException<std::exception>(string2BeginEqualEndAndIncrementPastEndException);
			Assert::ExpectException<std::exception>(string2DereferenceCEndException);
			Assert::ExpectException<std::exception>(string2IncrementPastCEndException);
			Assert::ExpectException<std::exception>(string2CBeginEqualCEndAndIncrementPastCEndException);
						
		}

		TEST_METHOD(IteratorsTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooUnorderedMap.Size() == 5);
			Assert::IsTrue(charFooUnorderedMap.begin() != charFooUnorderedMap.end());
			Assert::IsTrue(++(charFooUnorderedMap.begin()) != charFooUnorderedMap.end());
			Assert::IsTrue(++(charFooUnorderedMap.cbegin()) != charFooUnorderedMap.cend());

			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringUnorderedMap.Size() == 5);
			Assert::IsTrue(fooStringUnorderedMap.begin() != fooStringUnorderedMap.end());
			Assert::IsTrue(++(fooStringUnorderedMap.begin()) != fooStringUnorderedMap.end());
			Assert::IsTrue(++(fooStringUnorderedMap.cbegin()) != fooStringUnorderedMap.cend());

			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2UnorderedMap.Size() == 5);
			Assert::IsTrue(string2UnorderedMap.begin() != string2UnorderedMap.end());
			Assert::IsTrue(++(string2UnorderedMap.begin()) != string2UnorderedMap.end());
			Assert::IsTrue(++(string2UnorderedMap.cbegin()) != string2UnorderedMap.cend());
		}
		
		TEST_METHOD(InsertTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap;
			Assert::IsTrue(charFooUnorderedMap.Size() == 0);
			charFooUnorderedMap.Insert(std::pair<char*, Foo>("Up", Foo(1)));
			Assert::IsTrue(charFooUnorderedMap.Size() == 1);
			charFooUnorderedMap.Insert(std::pair<char*, Foo>("Down", Foo(2)));
			Assert::IsTrue(charFooUnorderedMap.Size() == 2);
			charFooUnorderedMap.Insert(std::pair<char*, Foo>("Left", Foo(3)));
			Assert::IsTrue(charFooUnorderedMap.Size() == 3);
			charFooUnorderedMap.Insert(std::pair<char*, Foo>("Left", Foo(3)));
			Assert::IsTrue(charFooUnorderedMap.Size() == 3);
			charFooUnorderedMap.Insert(std::pair<char*, Foo>("A", Foo(4)));
			Assert::IsTrue(charFooUnorderedMap.Size() == 4);
			charFooUnorderedMap.Insert(std::pair<char*, Foo>("Start", Foo(5)));
			Assert::IsTrue(charFooUnorderedMap.Size() == 5);



			UnorderedMapFooString fooStringUnorderedMap;
			Assert::IsTrue(fooStringUnorderedMap.Size() == 0);
			fooStringUnorderedMap.Insert(std::pair<Foo, std::string>(Foo(1), "Up"));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 1);
			fooStringUnorderedMap.Insert(std::pair<Foo, std::string>(Foo(2), "Down"));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 2);
			fooStringUnorderedMap.Insert(std::pair<Foo, std::string>(Foo(3), "Right"));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 3);
			fooStringUnorderedMap.Insert(std::pair<Foo, std::string>(Foo(3), "Right"));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 3);
			fooStringUnorderedMap.Insert(std::pair<Foo, std::string>(Foo(4), "B"));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 4);
			fooStringUnorderedMap.Insert(std::pair<Foo, std::string>(Foo(5), ""));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 5);



			UnorderedMapString2 string2UnorderedMap;
			Assert::IsTrue(string2UnorderedMap.Size() == 0);
			string2UnorderedMap.Insert(std::pair<std::string, std::string>("Up", "Up"));
			Assert::IsTrue(string2UnorderedMap.Size() == 1);
			string2UnorderedMap.Insert(std::pair<std::string, std::string>("Down", "Down"));
			Assert::IsTrue(string2UnorderedMap.Size() == 2);
			string2UnorderedMap.Insert(std::pair<std::string, std::string>("Left", "Right"));
			Assert::IsTrue(string2UnorderedMap.Size() == 3);
			string2UnorderedMap.Insert(std::pair<std::string, std::string>("Left", "Right"));
			Assert::IsTrue(string2UnorderedMap.Size() == 3);
			string2UnorderedMap.Insert(std::pair<std::string, std::string>("A", "B"));
			Assert::IsTrue(string2UnorderedMap.Size() == 4);
			string2UnorderedMap.Insert(std::pair<std::string, std::string>("Start", ""));
			Assert::IsTrue(string2UnorderedMap.Size() == 5);
		}

		TEST_METHOD(CopyConstructorAndAssignmentOperatorTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			UnorderedMapCharFoo charFooUnorderedMap2(charFooUnorderedMap);
			UnorderedMapCharFoo charFooUnorderedMap3 = charFooUnorderedMap;
			UnorderedMapCharFoo charFooUnorderedMap4 = { std::pair<char*,Foo>("Up", Foo(1)) };
			Assert::IsTrue(charFooUnorderedMap == charFooUnorderedMap2);
			Assert::IsTrue(charFooUnorderedMap2 == charFooUnorderedMap3);
			Assert::IsTrue(charFooUnorderedMap3 != charFooUnorderedMap4);
			
			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			UnorderedMapFooString fooStringUnorderedMap2(fooStringUnorderedMap);
			UnorderedMapFooString fooStringUnorderedMap3 = fooStringUnorderedMap;
			UnorderedMapFooString fooStringUnorderedMap4 = { std::pair<Foo,std::string>(Foo(1), "Up") };
			Assert::IsTrue(fooStringUnorderedMap == fooStringUnorderedMap2);
			Assert::IsTrue(fooStringUnorderedMap2 == fooStringUnorderedMap3);
			Assert::IsTrue(fooStringUnorderedMap3 != fooStringUnorderedMap4);

			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			UnorderedMapString2 string2UnorderedMap2(string2UnorderedMap);
			UnorderedMapString2 string2UnorderedMap3 = string2UnorderedMap;
			UnorderedMapString2 string2UnorderedMap4 = { std::pair<std::string,std::string>("Up", "Up") };
			Assert::IsTrue(string2UnorderedMap == string2UnorderedMap2);
			Assert::IsTrue(string2UnorderedMap2 == string2UnorderedMap3);
			Assert::IsTrue(string2UnorderedMap3 != string2UnorderedMap4);
		}

		TEST_METHOD(FindTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(*(charFooUnorderedMap.Find("Up")) == std::pair<char* const, Foo>("Up", Foo(1)));
			Assert::IsTrue(*(charFooUnorderedMap.Find("Down")) == std::pair<char* const, Foo>("Down", Foo(2)));
			Assert::IsTrue(*(charFooUnorderedMap.Find("Left")) == std::pair<char* const, Foo>("Left", Foo(3)));
			Assert::IsTrue(*(charFooUnorderedMap.Find("A")) == std::pair<char* const, Foo>("A", Foo(4)));
			Assert::IsTrue(*(charFooUnorderedMap.Find("Start")) == std::pair<char* const, Foo>("Start", Foo(5)));
			Assert::IsTrue(charFooUnorderedMap.Find("B") == charFooUnorderedMap.end());
			Assert::IsTrue(charFooUnorderedMap.Find("C") == charFooUnorderedMap.end());

			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(*(fooStringUnorderedMap.Find(Foo(1))) == std::pair<Foo const, std::string>(Foo(1), "Up"));
			Assert::IsTrue(*(fooStringUnorderedMap.Find(Foo(2))) == std::pair<Foo const, std::string>(Foo(2), "Down"));
			Assert::IsTrue(*(fooStringUnorderedMap.Find(Foo(3))) == std::pair<Foo const, std::string>(Foo(3), "Right"));
			Assert::IsTrue(*(fooStringUnorderedMap.Find(Foo(4))) == std::pair<Foo const, std::string>(Foo(4), "B"));
			Assert::IsTrue(*(fooStringUnorderedMap.Find(Foo(5))) == std::pair<Foo const, std::string>(Foo(5), ""));
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(6)) == fooStringUnorderedMap.end());
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(7)) == fooStringUnorderedMap.end());


			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(*(string2UnorderedMap.Find("Up")) == std::pair<const std::string, std::string>("Up", "Up"));
			Assert::IsTrue(*(string2UnorderedMap.Find("Down")) == std::pair<const std::string, std::string>("Down", "Down"));
			Assert::IsTrue(*(string2UnorderedMap.Find("Left")) == std::pair<const std::string, std::string>("Left", "Right"));
			Assert::IsTrue(*(string2UnorderedMap.Find("A")) == std::pair<const std::string, std::string>("A", "B"));
			Assert::IsTrue(*(string2UnorderedMap.Find("Start")) == std::pair<const std::string, std::string>("Start", ""));
			Assert::IsTrue(string2UnorderedMap.Find("B") == string2UnorderedMap.end());
			Assert::IsTrue(string2UnorderedMap.Find("C") == string2UnorderedMap.end());
		}

		TEST_METHOD(ContainsKeyTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooUnorderedMap.ContainsKey("Up").first);
			Assert::IsTrue(charFooUnorderedMap.ContainsKey("Down").first);
			Assert::IsTrue(charFooUnorderedMap.ContainsKey("Left").first);
			Assert::IsTrue(charFooUnorderedMap.ContainsKey("A").first);
			Assert::IsTrue(charFooUnorderedMap.ContainsKey("Start").first);
			Assert::IsTrue(!charFooUnorderedMap.ContainsKey("B").first);
			Assert::IsTrue(!charFooUnorderedMap.ContainsKey("C").first);

			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringUnorderedMap.ContainsKey(Foo(1)).first);
			Assert::IsTrue(fooStringUnorderedMap.ContainsKey(Foo(2)).first);
			Assert::IsTrue(fooStringUnorderedMap.ContainsKey(Foo(3)).first);
			Assert::IsTrue(fooStringUnorderedMap.ContainsKey(Foo(4)).first);
			Assert::IsTrue(fooStringUnorderedMap.ContainsKey(Foo(5)).first);
			Assert::IsTrue(!fooStringUnorderedMap.ContainsKey(Foo(6)).first);
			Assert::IsTrue(!fooStringUnorderedMap.ContainsKey(Foo(7)).first);


			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2UnorderedMap.ContainsKey("Up").first);
			Assert::IsTrue(string2UnorderedMap.ContainsKey("Down").first);
			Assert::IsTrue(string2UnorderedMap.ContainsKey("Left").first);
			Assert::IsTrue(string2UnorderedMap.ContainsKey("A").first);
			Assert::IsTrue(string2UnorderedMap.ContainsKey("Start").first);
			Assert::IsTrue(!string2UnorderedMap.ContainsKey("B").first);
			Assert::IsTrue(!string2UnorderedMap.ContainsKey("C").first);
		}
		TEST_METHOD(RemoveTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooUnorderedMap.Size() == 5);
			charFooUnorderedMap.Remove("Up");
			Assert::IsTrue(charFooUnorderedMap.Size() == 4);
			charFooUnorderedMap.Remove("Down");
			Assert::IsTrue(charFooUnorderedMap.Size() == 3);
			charFooUnorderedMap.Remove("Left");
			Assert::IsTrue(charFooUnorderedMap.Size() == 2);
			charFooUnorderedMap.Remove("A");
			Assert::IsTrue(charFooUnorderedMap.Size() == 1);
			charFooUnorderedMap.Remove("Start");
			Assert::IsTrue(charFooUnorderedMap.Size() == 0);
			charFooUnorderedMap.Remove("B");
			Assert::IsTrue(charFooUnorderedMap.Size() == 0);
			charFooUnorderedMap.Remove("C");
			Assert::IsTrue(charFooUnorderedMap.Size() == 0);

			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringUnorderedMap.Size() == 5);
			fooStringUnorderedMap.Remove(Foo(1));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 4);
			fooStringUnorderedMap.Remove(Foo(2));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 3);
			fooStringUnorderedMap.Remove(Foo(3));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 2);
			fooStringUnorderedMap.Remove(Foo(4));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 1);
			fooStringUnorderedMap.Remove(Foo(5));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 0);
			fooStringUnorderedMap.Remove(Foo(6));
			Assert::IsTrue(fooStringUnorderedMap.Size() == 0);
			fooStringUnorderedMap.Remove(Foo(7));;
			Assert::IsTrue(fooStringUnorderedMap.Size() == 0);

			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2UnorderedMap.Size() == 5);
			string2UnorderedMap.Remove("Up");
			Assert::IsTrue(string2UnorderedMap.Size() == 4);
			string2UnorderedMap.Remove("Down");
			Assert::IsTrue(string2UnorderedMap.Size() == 3);
			string2UnorderedMap.Remove("Left");
			Assert::IsTrue(string2UnorderedMap.Size() == 2);
			string2UnorderedMap.Remove("A");
			Assert::IsTrue(string2UnorderedMap.Size() == 1);
			string2UnorderedMap.Remove("Start");
			Assert::IsTrue(string2UnorderedMap.Size() == 0);
			string2UnorderedMap.Remove("B");
			Assert::IsTrue(string2UnorderedMap.Size() == 0);
			string2UnorderedMap.Remove("C");
			Assert::IsTrue(string2UnorderedMap.Size() == 0);
		}

		TEST_METHOD(ClearTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooUnorderedMap.Size() == 5);
			charFooUnorderedMap.Clear();
			Assert::IsTrue(charFooUnorderedMap.begin() == charFooUnorderedMap.end());
			Assert::IsTrue(charFooUnorderedMap.Size() == 0);

			UnorderedMapFooString fooStringUnorderedMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringUnorderedMap.Size() == 5);
			fooStringUnorderedMap.Clear();
			Assert::IsTrue(fooStringUnorderedMap.begin() == fooStringUnorderedMap.end());
			Assert::IsTrue(fooStringUnorderedMap.Size() == 0);

			UnorderedMapString2 string2UnorderedMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2UnorderedMap.Size() == 5);
			string2UnorderedMap.Clear();
			Assert::IsTrue(string2UnorderedMap.begin() == string2UnorderedMap.end());
			Assert::IsTrue(string2UnorderedMap.Size() == 0);
		}
		TEST_METHOD(BracketOperatorTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap;
			Assert::IsTrue(charFooUnorderedMap.Size() == 0);
			charFooUnorderedMap["Up"];
			Assert::IsTrue(charFooUnorderedMap.Size() == 1);
			Assert::IsTrue(charFooUnorderedMap.Find("Up")->second == charFooUnorderedMap["Up"]);
			charFooUnorderedMap["Down"];
			Assert::IsTrue(charFooUnorderedMap.Size() == 2);
			Assert::IsTrue(charFooUnorderedMap.Find("Down")->second == charFooUnorderedMap["Down"]);
			charFooUnorderedMap["Left"];
			Assert::IsTrue(charFooUnorderedMap.Size() == 3);
			Assert::IsTrue(charFooUnorderedMap.Find("Left")->second == charFooUnorderedMap["Left"]);
			charFooUnorderedMap["Left"];
			Assert::IsTrue(charFooUnorderedMap.Size() == 3);
			charFooUnorderedMap["A"];
			Assert::IsTrue(charFooUnorderedMap.Find("A")->second == charFooUnorderedMap["A"]);
			Assert::IsTrue(charFooUnorderedMap.Size() == 4);
			charFooUnorderedMap["Start"];
			Assert::IsTrue(charFooUnorderedMap.Find("Start")->second == charFooUnorderedMap["Start"]);
			Assert::IsTrue(charFooUnorderedMap.Size() == 5);

			

			UnorderedMapFooString fooStringUnorderedMap;
			Assert::IsTrue(fooStringUnorderedMap.Size() == 0);
			fooStringUnorderedMap[Foo(1)];
			Assert::IsTrue(fooStringUnorderedMap.Size() == 1);
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(1))->second == fooStringUnorderedMap[Foo(1)]);
			fooStringUnorderedMap[Foo(2)];
			Assert::IsTrue(fooStringUnorderedMap.Size() == 2);
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(2))->second == fooStringUnorderedMap[Foo(2)]);
			fooStringUnorderedMap[Foo(3)];
			Assert::IsTrue(fooStringUnorderedMap.Size() == 3);
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(3))->second == fooStringUnorderedMap[Foo(3)]);
			fooStringUnorderedMap[Foo(3)];
			Assert::IsTrue(fooStringUnorderedMap.Size() == 3);
			fooStringUnorderedMap[Foo(4)];
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(4))->second == fooStringUnorderedMap[Foo(4)]);
			Assert::IsTrue(fooStringUnorderedMap.Size() == 4);
			fooStringUnorderedMap[Foo(5)];
			Assert::IsTrue(fooStringUnorderedMap.Find(Foo(5))->second == fooStringUnorderedMap[Foo(5)]);
			Assert::IsTrue(fooStringUnorderedMap.Size() == 5);



			UnorderedMapString2 string2UnorderedMap;
			Assert::IsTrue(string2UnorderedMap.Size() == 0);
			string2UnorderedMap["Up"];
			Assert::IsTrue(string2UnorderedMap.Size() == 1);
			Assert::IsTrue(string2UnorderedMap.Find("Up")->second == string2UnorderedMap["Up"]);
			string2UnorderedMap["Down"];
			Assert::IsTrue(string2UnorderedMap.Size() == 2);
			Assert::IsTrue(string2UnorderedMap.Find("Down")->second == string2UnorderedMap["Down"]);
			string2UnorderedMap["Left"];
			Assert::IsTrue(string2UnorderedMap.Size() == 3);
			Assert::IsTrue(string2UnorderedMap.Find("Left")->second == string2UnorderedMap["Left"]);
			string2UnorderedMap["Left"];
			Assert::IsTrue(string2UnorderedMap.Size() == 3);
			string2UnorderedMap["A"];
			Assert::IsTrue(string2UnorderedMap.Find("A")->second == string2UnorderedMap["A"]);
			Assert::IsTrue(string2UnorderedMap.Size() == 4);
			string2UnorderedMap["Start"];
			Assert::IsTrue(string2UnorderedMap.Find("Start")->second == string2UnorderedMap["Start"]);
			Assert::IsTrue(string2UnorderedMap.Size() == 5);
		}
		TEST_METHOD(AtTest)
		{
			UnorderedMapCharFoo charFooUnorderedMap;
			auto charFooAtException = [&charFooUnorderedMap] { charFooUnorderedMap.At("Up"); };
			Assert::ExpectException<std::exception>(charFooAtException);
			charFooUnorderedMap["Up"];
			Assert::IsTrue(charFooUnorderedMap["Up"] == charFooUnorderedMap.At("Up"));

			UnorderedMapFooString fooStringUnorderedMap;
			auto fooStringAtException = [&fooStringUnorderedMap] { fooStringUnorderedMap.At(Foo(1)); };
			Assert::ExpectException<std::exception>(fooStringAtException);
			fooStringUnorderedMap[Foo(1)];
			fooStringUnorderedMap.At(Foo(1));
			UnorderedMapFooString constFooStringUnorderedMap = *const_cast<UnorderedMapFooString*>(&fooStringUnorderedMap);
			constFooStringUnorderedMap.At(Foo(1));
			Assert::IsTrue(fooStringUnorderedMap[Foo(1)] == fooStringUnorderedMap.At(Foo(1)));

			UnorderedMapString2 string2UnorderedMap;
			auto string2AtException = [&string2UnorderedMap] { string2UnorderedMap.At("Up"); };
			Assert::ExpectException<std::exception>(string2AtException);
			string2UnorderedMap["Up"];
			Assert::IsTrue(string2UnorderedMap["Up"] == string2UnorderedMap.At("Up"));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState UnorderedMapTest::sStartMemState;
}