#include "pch.h"
#include "CppUnitTest.h"
#include "OrderedMap.h"
#include "Vector.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <set>
#include <map>

#define _DEBUG_FUNCTIONAL_MACHINERY = 1

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(OrderedMapTest)
	{
	public:

		size_t const treeSize = 256;
		size_t const testIterations = 1000;

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
			OrderedMap<int,int> orderedMap;
		}

		TEST_METHOD(OrderedMapInitializerListConstructorTest)
		{
			OrderedMap<int, int> orderedMap { {0,0}, {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {10,10}, {11,11}, {12,12}, {13,13}, {14,14}, {15,15}};
		}

		TEST_METHOD(OrderedMapIteratorIncrementTest)
		{
			OrderedMap<int,int> orderedMap{ {0,0}, {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {10,10}, {11,11}, {12,12}, {13,13}, {14,14}, {15,15} };
			int i = 0;
			for (OrderedMap<int, int>::Iterator it = orderedMap.begin(); it != orderedMap.end(); i++, it++)
			{
				Assert::IsTrue(std::pair<int const,int>(i,i) == *it);
			}
		}

		TEST_METHOD(OrderedMapFindTest)
		{
			OrderedMap<int, int> orderedMap{ {0,0}, {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {10,10}, {11,11}, {12,12}, {13,13}, {14,14}, {15,15} };
			for (int i = 0; i < 16; i++)
			{
				Assert::IsTrue(*(orderedMap.Find(i)) == std::pair<int const, int>(i,i));
			}
			Assert::IsTrue(orderedMap.Find(-1) == orderedMap.end());
			Assert::IsTrue(orderedMap.Find(16) == orderedMap.end());
		}

		TEST_METHOD(OrderedMapInsertTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<int, int> orderedMap;
				std::vector<int> insertOrder;
				std::vector<int> removeOrder;
				int currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					orderedMap.Insert(std::pair<int, int>(element, element));
					orderedMap.Insert(std::pair<int, int>(element, element));
					currentSize++;
					Assert::IsTrue(currentSize == orderedMap.Size());
					Assert::IsTrue(orderedMap.VerifyRedBlackTree());
				}

				int currentElement = 0;
				for (OrderedMap<int,int>::Iterator it = orderedMap.begin(); it != orderedMap.end(); currentElement++, it++)
				{
					Assert::IsTrue(std::pair<int const,int>(currentElement, currentElement) == *it);
				}
			}
		}

		TEST_METHOD(OrderedMapRemoveTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<int, int> orderedMap;
				std::vector<int> insertOrder;
				std::vector<int> removeOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
					removeOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					orderedMap.Insert(std::pair<int, int>(element, element));
					orderedMap.Insert(std::pair<int, int>(element, element + 1));
					currentSize++;
				}

				std::shuffle(removeOrder.begin(), removeOrder.end(), default_random_engine(rand()));

				currentSize = treeSize;
				for (int element : removeOrder)
				{
					orderedMap.Remove(element);
					orderedMap.Remove(element);
					currentSize--;
					Assert::IsTrue(currentSize == orderedMap.Size());
					Assert::IsTrue(orderedMap.VerifyRedBlackTree());
				}
			}
		}


		TEST_METHOD(OrderedMapCopyConstructorAndAssignmentOperatorTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<int, int> orderedMap;

				std::vector<int> insertOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					orderedMap.Insert(std::pair<int, int>(element, element));
					currentSize++;
				}

				OrderedMap<int, int> orderedMapCopy(orderedMap);

				Assert::IsTrue(orderedMapCopy.Size() == orderedMap.Size());

				OrderedMap<int, int>::Iterator orderedMapIterator = orderedMap.begin();
				OrderedMap<int, int>::Iterator orderedMapCopyIterator = orderedMapCopy.begin();
				bool bAreEqual = true;



				while (orderedMapIterator != orderedMap.end() && bAreEqual)
				{
					bAreEqual &= bAreEqual && orderedMapIterator != orderedMapCopyIterator && *orderedMapIterator == *orderedMapCopyIterator && &(*orderedMapIterator) != &(*orderedMapCopyIterator);
					orderedMapIterator++;
					orderedMapCopyIterator++;
				}

				Assert::IsTrue(bAreEqual);

				int removedVal1 = rand() % (treeSize - 1);
				int removedVal2 = rand() % (treeSize - 1);


				while (removedVal1 == removedVal2)
				{
					removedVal1 = rand() % (treeSize - 1);
					removedVal2 = rand() % (treeSize - 1);
				}

				orderedMap.Remove(removedVal1);
				orderedMapCopy.Remove(removedVal1);

				Assert::IsTrue(orderedMapCopy.Size() == orderedMap.Size());

				orderedMapIterator = orderedMap.begin();
				orderedMapCopyIterator = orderedMapCopy.begin();

				while (orderedMapIterator != orderedMap.end() && bAreEqual)
				{
					bAreEqual &= bAreEqual && orderedMapIterator != orderedMapCopyIterator && *orderedMapIterator == *orderedMapCopyIterator && &(*orderedMapIterator) != &(*orderedMapCopyIterator);
					orderedMapIterator++;
					orderedMapCopyIterator++;
				}

				Assert::IsTrue(bAreEqual);

				orderedMap.Remove(removedVal2);

				orderedMapIterator = orderedMap.begin();
				orderedMapCopyIterator = orderedMapCopy.begin();

				Assert::IsTrue(orderedMapCopy.Size() != orderedMap.Size());

				while (orderedMapIterator != orderedMap.end() && bAreEqual)
				{
					bAreEqual &= bAreEqual && orderedMapIterator != orderedMapCopyIterator && *orderedMapIterator == *orderedMapCopyIterator && &(*orderedMapIterator) != &(*orderedMapCopyIterator);
					orderedMapIterator++;
					orderedMapCopyIterator++;
				}

				Assert::IsFalse(bAreEqual);
			}
		}

		TEST_METHOD(OrderedMapMoveConstructorAndMoveAssignmentOperatorTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<int, int> movedOrderedMap;

				std::vector<int> insertOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					movedOrderedMap.Insert(std::pair<int, int>(element, element));
					currentSize++;
				}

				OrderedMap<int, int> orderedMap(std::move(movedOrderedMap));

				Assert::IsTrue(movedOrderedMap.IsEmpty());
				Assert::IsTrue(orderedMap.Size() == treeSize);
			}
		}

		TEST_METHOD(OrderedMapComparisonOperatorsTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMap<int, int> orderedMap;

				std::vector<int> insertOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					orderedMap.Insert(std::pair<int, int>(element, element));
					currentSize++;
				}

				OrderedMap<int, int> orderedMapCopy(orderedMap);

				Assert::IsTrue(orderedMapCopy == orderedMap);

				int removedVal1 = rand() % (treeSize - 1);
				int removedVal2 = rand() % (treeSize - 1);


				while (removedVal1 == removedVal2)
				{
					removedVal1 = rand() % (treeSize - 1);
					removedVal2 = rand() % (treeSize - 1);
				}

				orderedMap.Remove(removedVal1);
				orderedMapCopy.Remove(removedVal1);

				Assert::IsTrue(orderedMapCopy == orderedMap);

				orderedMap.Remove(removedVal2);

				Assert::IsTrue(orderedMapCopy != orderedMap);
			}
		}

	private:

		static _CrtMemState sStartMemState;
	};

	_CrtMemState OrderedMapTest::sStartMemState;
}
