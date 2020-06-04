#include "pch.h"
#include "CppUnitTest.h"
#include "TestModuleConstants.h"
#include "Foo.h"
#include "OrderedMap.h"
#include "Vector.h"
#include <random>
#include <chrono>

#define _DEBUG_FUNCTIONAL_MACHINERY = 1

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;
using namespace UnitTests;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(OrderedMapTest)
	{
	public:

		TEST_METHOD_INITIALIZE(Initialize)
		{
			auto now = std::chrono::system_clock::now();
			auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
			auto epoch = now_ms.time_since_epoch();
			unsigned int totalMilliseconds = static_cast<unsigned int>(epoch.count());
			srand(totalMilliseconds);
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

		TEST_METHOD(OrderedMapConstructorTest)
		{
			OrderedMap<Foo, std::string> orderedMap;
			Assert::IsTrue(orderedMap.Size() == 0);
			Assert::IsTrue(orderedMap.IsEmpty());
			Assert::IsTrue(orderedMap.VerifyRedBlackTree());
			Assert::IsTrue(orderedMap.VerifySize());
		}

		TEST_METHOD(OrderedMapInitializerListConstructorTest)
		{
			OrderedMap<Foo, std::string> orderedMap
			{ {0, "0"}, {0, "0"}, {0, "0"}, {1, "1"}, {1, "1"}, {1, "1"}, {2, "2"}, {2, "2"}, {2, "2"},{3, "3"}, {3, "3"}, {3, "3"},
				{4, "4"}, {4, "4"}, {4, "4"}, {5, "5"}, {5, "5"}, {5, "5"}, {6, "6"}, {6, "6"}, {6, "6"},{7, "7"}, {7, "7"}, {7, "7"},
				{8, "8"}, {8, "8"}, {8, "8"}, {9, "9"}, {9, "9"}, {9, "9"}, {10, "10"}, {10, "10"}, {10, "10"}, {11, "11"}, {11, "11"}, {11, "11"},
				{12, "12"}, {12, "12"}, {12, "12"}, {13, "13"}, {13, "13"}, {13, "13"}, {14, "14"}, {14, "14"}, {14, "14"}, {15, "15"}, {15, "15"}, {15, "15"}
			};
			Assert::IsTrue(orderedMap.Size() == 16);
			Assert::IsFalse(orderedMap.IsEmpty());
			Assert::IsTrue(orderedMap.VerifyRedBlackTree());
			Assert::IsTrue(orderedMap.VerifySize());
		}

		TEST_METHOD(OrderedMapIteratorIncrementTest)
		{
			OrderedMap<Foo, std::string> orderedMap;
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMap.Insert(i, std::to_string(i));
				}
			}
			int i = 0;
			for (OrderedMap<Foo, std::string>::Iterator it = orderedMap.begin(); it != orderedMap.end(); i++)
			{
				Assert::IsTrue(std::pair<Foo const, std::string>(i, std::to_string(i)) == *it);
				it++;
			}
		}

		TEST_METHOD(OrderedMapFindAndContainsTest)
		{
			OrderedMap<Foo, std::string> orderedMap;
			Assert::IsTrue(orderedMap.Find(0) == orderedMap.end());
			Assert::IsFalse(orderedMap.Contains(0));
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMap.Insert(i, std::to_string(i));
				}
			}
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMap.Contains(i));
				OrderedMap<Foo, std::string>::Iterator foundValue = orderedMap.Find(i);
				Assert::IsTrue(*foundValue == std::pair<Foo const, std::string>(i, std::to_string(i)));
				orderedMap.Remove(foundValue);
				Assert::IsFalse(orderedMap.Contains(i));
				Assert::IsTrue(orderedMap.Find(i) == orderedMap.end());
			}
		}

		TEST_METHOD(OrderedMapLowerBoundTest)
		{
			OrderedMap<Foo, std::string> orderedMap;
			Assert::IsTrue(orderedMap.LowerBound(0) == orderedMap.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMap.Insert(i * 2, std::to_string(i * 2));
				}
			}

			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{
				
				OrderedMap<Foo, std::string>::Iterator lowerBound = orderedMap.LowerBound(i * 2 - 1);
				Assert::IsTrue(*lowerBound == std::pair<Foo const, std::string>(i * 2, std::to_string(i * 2)));
				orderedMap.Remove(lowerBound);
			}

			OrderedMap<Foo, std::string>::Iterator allElementsLower = orderedMap.LowerBound(static_cast<int>(treeSize));
			Assert::IsTrue(allElementsLower == orderedMap.end());
		}

		TEST_METHOD(OrderedMapUpperBoundTest)
		{
			OrderedMap<Foo, std::string> orderedMap;
			Assert::IsTrue(orderedMap.UpperBound(0) == orderedMap.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMap.Insert(i * 2, std::to_string(i * 2));
				}
			}
			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{
				OrderedMap<Foo, std::string>::Iterator upperBound = orderedMap.UpperBound(i * 2);
				Assert::IsTrue(*upperBound == std::pair<Foo const, std::string>((i + 1) * 2, std::to_string((i + 1) * 2)));
				orderedMap.Remove(--upperBound);
			}
			OrderedMap<Foo, std::string>::Iterator allElementsLower = orderedMap.UpperBound(static_cast<int>(treeSize - 1));
			Assert::IsTrue(allElementsLower == orderedMap.end());
		}

		TEST_METHOD(OrderedMapCountTest)
		{
			OrderedMap<Foo, std::string> orderedMap;
			Assert::IsTrue(orderedMap.Count(0) == 0);
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMap.Count(i) == 0);
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMap.Insert(i, std::to_string(i));
					Assert::IsTrue(orderedMap.Count(i) == 1);
				}
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMap.Count(i) == 1);
				orderedMap.Remove(i);
				Assert::IsTrue(orderedMap.Count(i) == 0);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMap.Count(i) == 0);
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMap.Insert(i, std::to_string(i));
					Assert::IsTrue(orderedMap.Count(i) == 1);
				}
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMap.Count(i) == 1);
				orderedMap.Remove(orderedMap.Find(i));
				Assert::IsTrue(orderedMap.Count(i) == 0);
			}
		}

		TEST_METHOD(OrderedMapInsertTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> orderedMap;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				size_t currentSize = 0;
				for (Foo element : insertOrder)
				{
					Assert::IsFalse(orderedMap.Contains(element));
					currentSize++;
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMap.Insert(element, std::to_string(element.Data()));
						Assert::IsTrue(orderedMap.Contains(element));
						Assert::IsTrue(currentSize == orderedMap.Size());
						Assert::IsTrue(orderedMap.VerifyRedBlackTree());
						Assert::IsTrue(orderedMap.VerifySize());
					}
				}
			}
		}

		TEST_METHOD(OrderedMapRemoveByValueTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> orderedMap;
				Vector<Foo> insertOrder;
				Vector<Foo> removeOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
					removeOrder.push_back(i);
				}

				insertOrder.Shuffle();
				removeOrder.Shuffle();

				for (Foo element : insertOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMap.Insert(element, std::to_string(element.Data()));
					}
				}

				size_t currentSize = orderedMap.Size();
				for (Foo element : removeOrder)
				{
					orderedMap.Remove(element);
					Assert::IsFalse(orderedMap.Contains(element));
					currentSize--;
					Assert::IsTrue(currentSize == orderedMap.Size());
					Assert::IsTrue(orderedMap.VerifyRedBlackTree());
					Assert::IsTrue(orderedMap.VerifySize());
				}
			}
		}

		TEST_METHOD(OrderedMapRemoveByIteratorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> orderedMap;
				Vector<Foo> insertOrder;
				Vector<Foo> removeOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
					removeOrder.push_back(i);
				}

				insertOrder.Shuffle();
				removeOrder.Shuffle();

				for (Foo element : insertOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMap.Insert(element, std::to_string(element.Data()));
					}
				}

				size_t currentSize = orderedMap.Size();
				for (Foo element : removeOrder)
				{
					Assert::IsTrue(orderedMap.Contains(element));
					orderedMap.Remove(orderedMap.Find(element));
					Assert::IsFalse(orderedMap.Contains(element));
					--currentSize;
					Assert::IsTrue(currentSize == orderedMap.Size());
					Assert::IsTrue(orderedMap.VerifyRedBlackTree());
					Assert::IsTrue(orderedMap.VerifySize());					
				}
			}
		}

		TEST_METHOD(OrderedMapCopyConstructorAndAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> orderedMap;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				for (Foo element : insertOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMap<Foo, std::string> orderedMapCopy(orderedMap);

				Assert::IsTrue(orderedMapCopy == orderedMap);

				orderedMap.Remove(rand() % (uniqueTreeElements - 1));

				Assert::IsFalse(orderedMapCopy == orderedMap);
			}
		}

		TEST_METHOD(OrderedMapMoveConstructorAndMoveAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> movedOrderedMap;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				for (Foo element : insertOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						movedOrderedMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMap<Foo, std::string> orderedMap(std::move(movedOrderedMap));

				Assert::IsTrue(movedOrderedMap.IsEmpty());
				Assert::IsTrue(orderedMap.Size() == uniqueTreeElements);
			}
		}

		TEST_METHOD(OrderedMapSwapTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> orderedMap;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				for (Foo element : insertOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMap<Foo, std::string> orderedMap2(orderedMap);

				orderedMap2.Remove(rand() % (uniqueTreeElements - 1));

				OrderedMap<Foo, std::string> orderedMapCopy(orderedMap);
				OrderedMap<Foo, std::string> orderedMap2Copy(orderedMap2);

				Assert::IsTrue(orderedMap == orderedMapCopy);
				Assert::IsFalse(orderedMap == orderedMap2Copy);
				Assert::IsTrue(orderedMap2 == orderedMap2Copy);
				Assert::IsFalse(orderedMap2 == orderedMapCopy);

				orderedMap.Swap(orderedMap2);

				Assert::IsTrue(orderedMap == orderedMap2Copy);
				Assert::IsFalse(orderedMap == orderedMapCopy);
				Assert::IsTrue(orderedMap2 == orderedMapCopy);
				Assert::IsFalse(orderedMap2 == orderedMap2Copy);
			}
		}

		TEST_METHOD(OrderedMapComparisonOperatorsTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<Foo, std::string> orderedMap;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				for (Foo element : insertOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMap<Foo, std::string> orderedMapCopy(orderedMap);

				Assert::IsTrue(orderedMapCopy == orderedMap);

				Vector<Foo> removeOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					removeOrder.push_back(i);
				}

				removeOrder.Shuffle();

				int removeOrderIndex = 0;
				while (removeOrderIndex < removeOrder.Size() - 1)
				{
					Assert::IsTrue(orderedMapCopy == orderedMap);

					orderedMap.Remove(removeOrder[removeOrderIndex]);
					Assert::IsFalse(orderedMapCopy == orderedMap);

					orderedMapCopy.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedMapCopy == orderedMap);

					orderedMap.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedMapCopy == orderedMap);

					orderedMapCopy.Remove(removeOrder[removeOrderIndex]);
					Assert::IsTrue(orderedMapCopy == orderedMap);

					removeOrderIndex += 2;
				}
			}
		}

	private:

		static _CrtMemState sStartMemState;
	};

	_CrtMemState OrderedMapTest::sStartMemState;
}
