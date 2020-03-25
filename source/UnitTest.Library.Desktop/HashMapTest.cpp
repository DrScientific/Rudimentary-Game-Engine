#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "HashMap.h"
#include "DefaultHashFunctorTemplates.h"

//TODO Hash map Resize test

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace UnitTests;

using HashMapCharFoo = HashMap<char*, Foo>;
using HashMapFooString = HashMap<Foo, std::string>;
using HashMapString2 = HashMap<std::string, std::string>;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashMapTest)
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

		TEST_METHOD(TestDefaultConstructorAndDestructor)
		{
			HashMapCharFoo charFooHashMap;
			HashMapFooString fooStringHashMap;
			HashMapString2 stringStringHashMap;
		}

		TEST_METHOD(TestInitializerListConstructor)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooHashMap.Size() == 5);
			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "")};
			Assert::IsTrue(fooStringHashMap.Size() == 5);
			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2HashMap.Size() == 5);
		}

		TEST_METHOD(TestIteratorExceptions)
		{
			HashMapCharFoo charFooHashMap;

			HashMapCharFoo::Iterator charFooBeginning = charFooHashMap.begin();
			HashMapCharFoo::Iterator ending = charFooHashMap.end();
			HashMapCharFoo::const_Iterator charFooCBeginning = charFooHashMap.cbegin();
			HashMapCharFoo::const_Iterator charFooCEnding = charFooHashMap.cend();

			Assert::IsTrue(charFooBeginning == ending);
			Assert::IsTrue(charFooCBeginning == charFooCEnding);

			auto charFooDereferenceEndException = [&charFooHashMap] { *charFooHashMap.end(); };
			auto charFooArrowOperatorEndException = [&charFooHashMap] { charFooHashMap.end()->first; };
			auto charFooIncrementPastEndException = [&charFooHashMap] { ++charFooHashMap.end(); };
			auto charFooBeginEqualEndAndIncrementPastEndException = [&charFooHashMap] { ++charFooHashMap.begin(); };
			auto charFooDereferenceCEndException = [&charFooHashMap] { *charFooHashMap.cend(); };
			auto charFooIncrementPastCEndException = [&charFooHashMap] { ++charFooHashMap.cend(); };
			auto charFooCBeginEqualCEndAndIncrementPastCEndException = [&charFooHashMap] { ++charFooHashMap.cbegin(); };

			Assert::ExpectException<std::exception>(charFooDereferenceEndException);
			Assert::ExpectException<std::exception>(charFooArrowOperatorEndException);
			Assert::ExpectException<std::exception>(charFooIncrementPastEndException);
			Assert::ExpectException<std::exception>(charFooBeginEqualEndAndIncrementPastEndException);
			Assert::ExpectException<std::exception>(charFooDereferenceCEndException );
			Assert::ExpectException<std::exception>(charFooIncrementPastCEndException);
			Assert::ExpectException<std::exception>(charFooCBeginEqualCEndAndIncrementPastCEndException);
			


			HashMapFooString fooStringHashMap;

			HashMapFooString::Iterator fooStringBeginning = fooStringHashMap.begin();
			HashMapFooString::Iterator fooStringEnding = fooStringHashMap.end();
			HashMapFooString::const_Iterator fooStringCBeginning = fooStringHashMap.cbegin();
			HashMapFooString::const_Iterator fooStringCEnding = fooStringHashMap.cend();

			auto fooStringDereferenceEndException = [&fooStringHashMap] { *fooStringHashMap.end(); };
			auto fooStringArrowOperatorEndException = [&fooStringHashMap] { fooStringHashMap.end()->first; };
			auto fooStringIncrementPastEndException = [&fooStringHashMap] { ++fooStringHashMap.end(); };
			auto fooStringBeginEqualEndAndIncrementPastEndException = [&fooStringHashMap] { ++fooStringHashMap.begin(); };
			auto fooStringDereferenceCEndException = [&fooStringHashMap] { *fooStringHashMap.cend(); };
			auto fooStringIncrementPastCEndException = [&fooStringHashMap] { ++fooStringHashMap.cend(); };
			auto fooStringCBeginEqualCEndAndIncrementPastCEndException = [&fooStringHashMap] { ++fooStringHashMap.cbegin(); };

			Assert::ExpectException<std::exception>(fooStringDereferenceEndException);
			Assert::ExpectException<std::exception>(fooStringArrowOperatorEndException);
			Assert::ExpectException<std::exception>(fooStringIncrementPastEndException);
			Assert::ExpectException<std::exception>(fooStringBeginEqualEndAndIncrementPastEndException);
			Assert::ExpectException<std::exception>(fooStringDereferenceCEndException);
			Assert::ExpectException<std::exception>(fooStringIncrementPastCEndException);
			Assert::ExpectException<std::exception>(fooStringCBeginEqualCEndAndIncrementPastCEndException);



			HashMapString2 string2HashMap;

			HashMapString2::Iterator string2Beginning = string2HashMap.begin();
			HashMapString2::Iterator string2Ending = string2HashMap.end();
			HashMapString2::const_Iterator string2CBeginning = string2HashMap.cbegin();
			HashMapString2::const_Iterator string2CEnding = string2HashMap.cend();
			
			auto string2DereferenceEndException = [&string2HashMap] { *string2HashMap.end(); };
			auto string2ArrowOperatorEndException = [&string2HashMap] { string2HashMap.end()->first; };
			auto string2IncrementPastEndException = [&string2HashMap] { ++string2HashMap.end(); };
			auto string2BeginEqualEndAndIncrementPastEndException = [&string2HashMap] { ++string2HashMap.begin(); };
			auto string2DereferenceCEndException = [&string2HashMap] { *string2HashMap.cend(); };
			auto string2IncrementPastCEndException = [&string2HashMap] { ++string2HashMap.cend(); };
			auto string2CBeginEqualCEndAndIncrementPastCEndException = [&string2HashMap] { ++string2HashMap.cbegin(); };

			Assert::ExpectException<std::exception>(string2DereferenceEndException);
			Assert::ExpectException<std::exception>(string2ArrowOperatorEndException);
			Assert::ExpectException<std::exception>(string2IncrementPastEndException);
			Assert::ExpectException<std::exception>(string2BeginEqualEndAndIncrementPastEndException);
			Assert::ExpectException<std::exception>(string2DereferenceCEndException);
			Assert::ExpectException<std::exception>(string2IncrementPastCEndException);
			Assert::ExpectException<std::exception>(string2CBeginEqualCEndAndIncrementPastCEndException);
						
		}

		TEST_METHOD(TestIterators)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooHashMap.Size() == 5);
			Assert::IsTrue(charFooHashMap.begin() != charFooHashMap.end());
			Assert::IsTrue(++(charFooHashMap.begin()) != charFooHashMap.end());
			Assert::IsTrue(++(charFooHashMap.cbegin()) != charFooHashMap.cend());

			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringHashMap.Size() == 5);
			Assert::IsTrue(fooStringHashMap.begin() != fooStringHashMap.end());
			Assert::IsTrue(++(fooStringHashMap.begin()) != fooStringHashMap.end());
			Assert::IsTrue(++(fooStringHashMap.cbegin()) != fooStringHashMap.cend());

			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2HashMap.Size() == 5);
			Assert::IsTrue(string2HashMap.begin() != string2HashMap.end());
			Assert::IsTrue(++(string2HashMap.begin()) != string2HashMap.end());
			Assert::IsTrue(++(string2HashMap.cbegin()) != string2HashMap.cend());
		}
		
		TEST_METHOD(TestInsert)
		{
			HashMapCharFoo charFooHashMap;
			Assert::IsTrue(charFooHashMap.Size() == 0);
			charFooHashMap.Insert(std::pair<char*, Foo>("Up", Foo(1)));
			Assert::IsTrue(charFooHashMap.Size() == 1);
			charFooHashMap.Insert(std::pair<char*, Foo>("Down", Foo(2)));
			Assert::IsTrue(charFooHashMap.Size() == 2);
			charFooHashMap.Insert(std::pair<char*, Foo>("Left", Foo(3)));
			Assert::IsTrue(charFooHashMap.Size() == 3);
			charFooHashMap.Insert(std::pair<char*, Foo>("Left", Foo(3)));
			Assert::IsTrue(charFooHashMap.Size() == 3);
			charFooHashMap.Insert(std::pair<char*, Foo>("A", Foo(4)));
			Assert::IsTrue(charFooHashMap.Size() == 4);
			charFooHashMap.Insert(std::pair<char*, Foo>("Start", Foo(5)));
			Assert::IsTrue(charFooHashMap.Size() == 5);



			HashMapFooString fooStringHashMap;
			Assert::IsTrue(fooStringHashMap.Size() == 0);
			fooStringHashMap.Insert(std::pair<Foo, std::string>(Foo(1), "Up"));
			Assert::IsTrue(fooStringHashMap.Size() == 1);
			fooStringHashMap.Insert(std::pair<Foo, std::string>(Foo(2), "Down"));
			Assert::IsTrue(fooStringHashMap.Size() == 2);
			fooStringHashMap.Insert(std::pair<Foo, std::string>(Foo(3), "Right"));
			Assert::IsTrue(fooStringHashMap.Size() == 3);
			fooStringHashMap.Insert(std::pair<Foo, std::string>(Foo(3), "Right"));
			Assert::IsTrue(fooStringHashMap.Size() == 3);
			fooStringHashMap.Insert(std::pair<Foo, std::string>(Foo(4), "B"));
			Assert::IsTrue(fooStringHashMap.Size() == 4);
			fooStringHashMap.Insert(std::pair<Foo, std::string>(Foo(5), ""));
			Assert::IsTrue(fooStringHashMap.Size() == 5);



			HashMapString2 string2HashMap;
			Assert::IsTrue(string2HashMap.Size() == 0);
			string2HashMap.Insert(std::pair<std::string, std::string>("Up", "Up"));
			Assert::IsTrue(string2HashMap.Size() == 1);
			string2HashMap.Insert(std::pair<std::string, std::string>("Down", "Down"));
			Assert::IsTrue(string2HashMap.Size() == 2);
			string2HashMap.Insert(std::pair<std::string, std::string>("Left", "Right"));
			Assert::IsTrue(string2HashMap.Size() == 3);
			string2HashMap.Insert(std::pair<std::string, std::string>("Left", "Right"));
			Assert::IsTrue(string2HashMap.Size() == 3);
			string2HashMap.Insert(std::pair<std::string, std::string>("A", "B"));
			Assert::IsTrue(string2HashMap.Size() == 4);
			string2HashMap.Insert(std::pair<std::string, std::string>("Start", ""));
			Assert::IsTrue(string2HashMap.Size() == 5);
		}

		TEST_METHOD(TestCopyConstructorAndAssignmentOperator)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			HashMapCharFoo charFooHashMap2(charFooHashMap);
			HashMapCharFoo charFooHashMap3 = charFooHashMap;
			HashMapCharFoo charFooHashMap4 = { std::pair<char*,Foo>("Up", Foo(1)) };
			Assert::IsTrue(charFooHashMap == charFooHashMap2);
			Assert::IsTrue(charFooHashMap2 == charFooHashMap3);
			Assert::IsTrue(charFooHashMap3 != charFooHashMap4);
			
			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			HashMapFooString fooStringHashMap2(fooStringHashMap);
			HashMapFooString fooStringHashMap3 = fooStringHashMap;
			HashMapFooString fooStringHashMap4 = { std::pair<Foo,std::string>(Foo(1), "Up") };
			Assert::IsTrue(fooStringHashMap == fooStringHashMap2);
			Assert::IsTrue(fooStringHashMap2 == fooStringHashMap3);
			Assert::IsTrue(fooStringHashMap3 != fooStringHashMap4);

			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			HashMapString2 string2HashMap2(string2HashMap);
			HashMapString2 string2HashMap3 = string2HashMap;
			HashMapString2 string2HashMap4 = { std::pair<std::string,std::string>("Up", "Up") };
			Assert::IsTrue(string2HashMap == string2HashMap2);
			Assert::IsTrue(string2HashMap2 == string2HashMap3);
			Assert::IsTrue(string2HashMap3 != string2HashMap4);
		}

		TEST_METHOD(TestFind)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(*(charFooHashMap.Find("Up")) == std::pair<char* const, Foo>("Up", Foo(1)));
			Assert::IsTrue(*(charFooHashMap.Find("Down")) == std::pair<char* const, Foo>("Down", Foo(2)));
			Assert::IsTrue(*(charFooHashMap.Find("Left")) == std::pair<char* const, Foo>("Left", Foo(3)));
			Assert::IsTrue(*(charFooHashMap.Find("A")) == std::pair<char* const, Foo>("A", Foo(4)));
			Assert::IsTrue(*(charFooHashMap.Find("Start")) == std::pair<char* const, Foo>("Start", Foo(5)));
			Assert::IsTrue(charFooHashMap.Find("B") == charFooHashMap.end());
			Assert::IsTrue(charFooHashMap.Find("C") == charFooHashMap.end());

			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(*(fooStringHashMap.Find(Foo(1))) == std::pair<Foo const, std::string>(Foo(1), "Up"));
			Assert::IsTrue(*(fooStringHashMap.Find(Foo(2))) == std::pair<Foo const, std::string>(Foo(2), "Down"));
			Assert::IsTrue(*(fooStringHashMap.Find(Foo(3))) == std::pair<Foo const, std::string>(Foo(3), "Right"));
			Assert::IsTrue(*(fooStringHashMap.Find(Foo(4))) == std::pair<Foo const, std::string>(Foo(4), "B"));
			Assert::IsTrue(*(fooStringHashMap.Find(Foo(5))) == std::pair<Foo const, std::string>(Foo(5), ""));
			Assert::IsTrue(fooStringHashMap.Find(Foo(6)) == fooStringHashMap.end());
			Assert::IsTrue(fooStringHashMap.Find(Foo(7)) == fooStringHashMap.end());


			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(*(string2HashMap.Find("Up")) == std::pair<const std::string, std::string>("Up", "Up"));
			Assert::IsTrue(*(string2HashMap.Find("Down")) == std::pair<const std::string, std::string>("Down", "Down"));
			Assert::IsTrue(*(string2HashMap.Find("Left")) == std::pair<const std::string, std::string>("Left", "Right"));
			Assert::IsTrue(*(string2HashMap.Find("A")) == std::pair<const std::string, std::string>("A", "B"));
			Assert::IsTrue(*(string2HashMap.Find("Start")) == std::pair<const std::string, std::string>("Start", ""));
			Assert::IsTrue(string2HashMap.Find("B") == string2HashMap.end());
			Assert::IsTrue(string2HashMap.Find("C") == string2HashMap.end());
		}

		TEST_METHOD(TestContainsKey)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooHashMap.ContainsKey("Up").first);
			Assert::IsTrue(charFooHashMap.ContainsKey("Down").first);
			Assert::IsTrue(charFooHashMap.ContainsKey("Left").first);
			Assert::IsTrue(charFooHashMap.ContainsKey("A").first);
			Assert::IsTrue(charFooHashMap.ContainsKey("Start").first);
			Assert::IsTrue(!charFooHashMap.ContainsKey("B").first);
			Assert::IsTrue(!charFooHashMap.ContainsKey("C").first);

			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringHashMap.ContainsKey(Foo(1)).first);
			Assert::IsTrue(fooStringHashMap.ContainsKey(Foo(2)).first);
			Assert::IsTrue(fooStringHashMap.ContainsKey(Foo(3)).first);
			Assert::IsTrue(fooStringHashMap.ContainsKey(Foo(4)).first);
			Assert::IsTrue(fooStringHashMap.ContainsKey(Foo(5)).first);
			Assert::IsTrue(!fooStringHashMap.ContainsKey(Foo(6)).first);
			Assert::IsTrue(!fooStringHashMap.ContainsKey(Foo(7)).first);


			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2HashMap.ContainsKey("Up").first);
			Assert::IsTrue(string2HashMap.ContainsKey("Down").first);
			Assert::IsTrue(string2HashMap.ContainsKey("Left").first);
			Assert::IsTrue(string2HashMap.ContainsKey("A").first);
			Assert::IsTrue(string2HashMap.ContainsKey("Start").first);
			Assert::IsTrue(!string2HashMap.ContainsKey("B").first);
			Assert::IsTrue(!string2HashMap.ContainsKey("C").first);
		}
		TEST_METHOD(TestRemove)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooHashMap.Size() == 5);
			charFooHashMap.Remove("Up");
			Assert::IsTrue(charFooHashMap.Size() == 4);
			charFooHashMap.Remove("Down");
			Assert::IsTrue(charFooHashMap.Size() == 3);
			charFooHashMap.Remove("Left");
			Assert::IsTrue(charFooHashMap.Size() == 2);
			charFooHashMap.Remove("A");
			Assert::IsTrue(charFooHashMap.Size() == 1);
			charFooHashMap.Remove("Start");
			Assert::IsTrue(charFooHashMap.Size() == 0);
			charFooHashMap.Remove("B");
			Assert::IsTrue(charFooHashMap.Size() == 0);
			charFooHashMap.Remove("C");
			Assert::IsTrue(charFooHashMap.Size() == 0);

			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringHashMap.Size() == 5);
			fooStringHashMap.Remove(Foo(1));
			Assert::IsTrue(fooStringHashMap.Size() == 4);
			fooStringHashMap.Remove(Foo(2));
			Assert::IsTrue(fooStringHashMap.Size() == 3);
			fooStringHashMap.Remove(Foo(3));
			Assert::IsTrue(fooStringHashMap.Size() == 2);
			fooStringHashMap.Remove(Foo(4));
			Assert::IsTrue(fooStringHashMap.Size() == 1);
			fooStringHashMap.Remove(Foo(5));
			Assert::IsTrue(fooStringHashMap.Size() == 0);
			fooStringHashMap.Remove(Foo(6));
			Assert::IsTrue(fooStringHashMap.Size() == 0);
			fooStringHashMap.Remove(Foo(7));;
			Assert::IsTrue(fooStringHashMap.Size() == 0);

			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2HashMap.Size() == 5);
			string2HashMap.Remove("Up");
			Assert::IsTrue(string2HashMap.Size() == 4);
			string2HashMap.Remove("Down");
			Assert::IsTrue(string2HashMap.Size() == 3);
			string2HashMap.Remove("Left");
			Assert::IsTrue(string2HashMap.Size() == 2);
			string2HashMap.Remove("A");
			Assert::IsTrue(string2HashMap.Size() == 1);
			string2HashMap.Remove("Start");
			Assert::IsTrue(string2HashMap.Size() == 0);
			string2HashMap.Remove("B");
			Assert::IsTrue(string2HashMap.Size() == 0);
			string2HashMap.Remove("C");
			Assert::IsTrue(string2HashMap.Size() == 0);
		}

		TEST_METHOD(TestClear)
		{
			HashMapCharFoo charFooHashMap = { std::pair<char*,Foo>("Up", Foo(1)), std::pair<char*,Foo>("Down", Foo(2)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("Left", Foo(3)), std::pair<char*,Foo>("A", Foo(4)), std::pair<char*,Foo>("Start", Foo(5)) };
			Assert::IsTrue(charFooHashMap.Size() == 5);
			charFooHashMap.Clear();
			Assert::IsTrue(charFooHashMap.begin() == charFooHashMap.end());
			Assert::IsTrue(charFooHashMap.Size() == 0);

			HashMapFooString fooStringHashMap = { std::pair<Foo,std::string>(Foo(1), "Up"),std::pair<Foo,std::string>(Foo(2), "Down"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(3), "Right"), std::pair<Foo,std::string>(Foo(4), "B"), std::pair<Foo,std::string>(Foo(5), "") };
			Assert::IsTrue(fooStringHashMap.Size() == 5);
			fooStringHashMap.Clear();
			Assert::IsTrue(fooStringHashMap.begin() == fooStringHashMap.end());
			Assert::IsTrue(fooStringHashMap.Size() == 0);

			HashMapString2 string2HashMap = { std::pair<std::string,std::string>("Up", "Up"), std::pair<std::string,std::string>("Down", "Down"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("Left", "Right"), std::pair<std::string,std::string>("A", "B"), std::pair<std::string,std::string>("Start", "") };
			Assert::IsTrue(string2HashMap.Size() == 5);
			string2HashMap.Clear();
			Assert::IsTrue(string2HashMap.begin() == string2HashMap.end());
			Assert::IsTrue(string2HashMap.Size() == 0);
		}
		TEST_METHOD(TestBracketOperator)
		{
			HashMapCharFoo charFooHashMap;
			Assert::IsTrue(charFooHashMap.Size() == 0);
			charFooHashMap["Up"];
			Assert::IsTrue(charFooHashMap.Size() == 1);
			Foo a = charFooHashMap.Find("Up")->second;
			Foo b = charFooHashMap["Up"];
			Assert::IsTrue(a == b);
			charFooHashMap["Down"];
			Assert::IsTrue(charFooHashMap.Size() == 2);
			Assert::IsTrue(charFooHashMap.Find("Down")->second == charFooHashMap["Down"]);
			charFooHashMap["Left"];
			Assert::IsTrue(charFooHashMap.Size() == 3);
			Assert::IsTrue(charFooHashMap.Find("Left")->second == charFooHashMap["Left"]);
			charFooHashMap["Left"];
			Assert::IsTrue(charFooHashMap.Size() == 3);
			charFooHashMap["A"];
			Assert::IsTrue(charFooHashMap.Find("A")->second == charFooHashMap["A"]);
			Assert::IsTrue(charFooHashMap.Size() == 4);
			charFooHashMap["Start"];
			Assert::IsTrue(charFooHashMap.Find("Start")->second == charFooHashMap["Start"]);
			Assert::IsTrue(charFooHashMap.Size() == 5);

			HashMapFooString fooStringHashMap;
			Assert::IsTrue(fooStringHashMap.Size() == 0);
			fooStringHashMap[Foo(1)];
			Assert::IsTrue(fooStringHashMap.Size() == 1);
			Assert::IsTrue(fooStringHashMap.Find(Foo(1))->second == fooStringHashMap[Foo(1)]);
			fooStringHashMap[Foo(2)];
			Assert::IsTrue(fooStringHashMap.Size() == 2);
			Assert::IsTrue(fooStringHashMap.Find(Foo(2))->second == fooStringHashMap[Foo(2)]);
			fooStringHashMap[Foo(3)];
			Assert::IsTrue(fooStringHashMap.Size() == 3);
			Assert::IsTrue(fooStringHashMap.Find(Foo(3))->second == fooStringHashMap[Foo(3)]);
			fooStringHashMap[Foo(3)];
			Assert::IsTrue(fooStringHashMap.Size() == 3);
			fooStringHashMap[Foo(4)];
			Assert::IsTrue(fooStringHashMap.Find(Foo(4))->second == fooStringHashMap[Foo(4)]);
			Assert::IsTrue(fooStringHashMap.Size() == 4);
			fooStringHashMap[Foo(5)];
			Assert::IsTrue(fooStringHashMap.Find(Foo(5))->second == fooStringHashMap[Foo(5)]);
			Assert::IsTrue(fooStringHashMap.Size() == 5);



			HashMapString2 string2HashMap;
			Assert::IsTrue(string2HashMap.Size() == 0);
			string2HashMap["Up"];
			Assert::IsTrue(string2HashMap.Size() == 1);
			Assert::IsTrue(string2HashMap.Find("Up")->second == string2HashMap["Up"]);
			string2HashMap["Down"];
			Assert::IsTrue(string2HashMap.Size() == 2);
			Assert::IsTrue(string2HashMap.Find("Down")->second == string2HashMap["Down"]);
			string2HashMap["Left"];
			Assert::IsTrue(string2HashMap.Size() == 3);
			Assert::IsTrue(string2HashMap.Find("Left")->second == string2HashMap["Left"]);
			string2HashMap["Left"];
			Assert::IsTrue(string2HashMap.Size() == 3);
			string2HashMap["A"];
			Assert::IsTrue(string2HashMap.Find("A")->second == string2HashMap["A"]);
			Assert::IsTrue(string2HashMap.Size() == 4);
			string2HashMap["Start"];
			Assert::IsTrue(string2HashMap.Find("Start")->second == string2HashMap["Start"]);
			Assert::IsTrue(string2HashMap.Size() == 5);
		}
		TEST_METHOD(TestAt)
		{
			HashMapCharFoo charFooHashMap;
			auto charFooAtException = [&charFooHashMap] { charFooHashMap.At("Up"); };
			Assert::ExpectException<std::exception>(charFooAtException);
			charFooHashMap["Up"];
			Assert::IsTrue(charFooHashMap["Up"] == charFooHashMap.At("Up"));

			HashMapFooString fooStringHashMap;
			auto fooStringAtException = [&fooStringHashMap] { fooStringHashMap.At(Foo(1)); };
			Assert::ExpectException<std::exception>(fooStringAtException);
			fooStringHashMap[Foo(1)];
			fooStringHashMap.At(Foo(1));
			Assert::IsTrue(fooStringHashMap[Foo(1)] == fooStringHashMap.At(Foo(1)));

			HashMapString2 string2HashMap;
			auto string2AtException = [&string2HashMap] { string2HashMap.At("Up"); };
			Assert::ExpectException<std::exception>(string2AtException);
			string2HashMap["Up"];
			Assert::IsTrue(string2HashMap["Up"] == string2HashMap.At("Up"));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState HashMapTest::sStartMemState;
}