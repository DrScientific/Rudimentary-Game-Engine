#include "pch.h"
#include "CppUnitTest.h"
#include "Set.h"
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
	TEST_CLASS(SetTest)
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
		
		TEST_METHOD(StdSetTest)
		{
			//How is set's keys nonconst but they're always returned as const?
			std::set<int> set = { 1,2,3,4,5,6,7,8,9 };
			int const& ref = (*(set.find(6)));
			ref;
		}

		TEST_METHOD(StdMultisetTest)
		{
			std::multiset<int> multiset = { 1,2,3,4,5,6,6,7,8,9 };
			int const& ref = (*(multiset.find(6)));
			ref;
			auto range = (multiset.equal_range(6));
			range;
		}
		
		TEST_METHOD(StdMapTest)
		{
			std::map<int, int> map = { {1,1},{2,2},{3,3},{4,4},{5,5},{6,6} };
			auto& ref = (*(map.find(4)));
			ref;
		}

		TEST_METHOD(StdMultimapTest)
		{
			std::multimap<int, int> multimap = { {1,1},{2,2},{3,3},{4,4},{4,4},{4,5},{5,5},{6,6} };
			auto& ref = (*(multimap.find(4)));
			ref;
			auto range = (multimap.equal_range(4));
			range;
		}

		TEST_METHOD(SetConstructorTest)
		{
			Set<int> set;
		}
		
		TEST_METHOD(SetInitializerListConstructorTest)
		{
			Set<int> set{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		}
		
		TEST_METHOD(SetIteratorIncrementTest)
		{
			Set<int> set{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
			int i = 0;
			for (Set<int>::Iterator it = set.begin(); it != set.end(); i++, it++)
			{
				Assert::AreEqual(i, *it);
			}
		}
		
		TEST_METHOD(SetFindTest)
		{
			Set<int> set{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
			
			for (int i = 0; i < 16; i++)
			{
				Assert::IsTrue(*(set.Find(i)) == i);
			}
			Assert::IsTrue(set.Find(-1) == set.end());
			Assert::IsTrue(set.Find(16) == set.end());
		}
		
		TEST_METHOD(SetInsertTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				Set<int> set;
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
					set.Insert(element);
					set.Insert(element);
					currentSize++;
					Assert::IsTrue(currentSize == set.Size());
					Assert::IsTrue(set.VerifyRedBlackTree());
				}

				int currentElement = 0;
				for (Set<int>::Iterator it = set.begin(); it != set.end(); currentElement++, it++)
				{
					Assert::IsTrue(currentElement == *it);
				}
			}
		}

		TEST_METHOD(SetRemoveTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				Set<int> set;
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
					set.Insert(element);
					set.Insert(element);
					currentSize++;
				}

				std::shuffle(removeOrder.begin(), removeOrder.end(), default_random_engine(rand()));

				currentSize = treeSize;
				for (int element : removeOrder)
				{
					set.Remove(element);
					set.Remove(element);
					currentSize--;
					Assert::IsTrue(currentSize == set.Size());
					Assert::IsTrue(set.VerifyRedBlackTree());
					
				}
			}
		}


		TEST_METHOD(SetCopyConstructorAndAssignmentOperatorTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				Set<int> set;
				
				std::vector<int> insertOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					set.Insert(element);
					currentSize++;
				}

				Set<int> setCopy(set);

				Assert::IsTrue(setCopy.Size() == set.Size());

				Set<int>::Iterator setIterator = set.begin();
				Set<int>::Iterator setCopyIterator = setCopy.begin();
				bool bAreEqual = true;

				

				while (setIterator != set.end() && bAreEqual)
				{
					bAreEqual &= bAreEqual && setIterator != setCopyIterator && *setIterator == *setCopyIterator && &(*setIterator) != &(*setCopyIterator);
					setIterator++;
					setCopyIterator++;
				}
				
				Assert::IsTrue(bAreEqual);

				int removedVal1 = rand() % (treeSize - 1);
				int removedVal2 = rand() % (treeSize - 1);
			

				while (removedVal1 == removedVal2)
				{
					removedVal1 = rand() % (treeSize - 1);
					removedVal2 = rand() % (treeSize - 1);
				}

				set.Remove(removedVal1);
				setCopy.Remove(removedVal1);

				Assert::IsTrue(setCopy.Size() == set.Size());

				setIterator = set.begin();
				setCopyIterator = setCopy.begin();

				while (setIterator != set.end() && bAreEqual)
				{
					bAreEqual &= bAreEqual && setIterator != setCopyIterator && *setIterator == *setCopyIterator && &(*setIterator) != &(*setCopyIterator);
					setIterator++;
					setCopyIterator++;
				}

				Assert::IsTrue(bAreEqual);

				set.Remove(removedVal2);

				setIterator = set.begin();
				setCopyIterator = setCopy.begin();

				Assert::IsTrue(setCopy.Size() != set.Size());

				while (setIterator != set.end() && bAreEqual)
				{
					bAreEqual &= bAreEqual && setIterator != setCopyIterator && *setIterator == *setCopyIterator && &(*setIterator) != &(*setCopyIterator);
					setIterator++;
					setCopyIterator++;
				}

				Assert::IsFalse(bAreEqual);
			}
		}

		TEST_METHOD(SetMoveConstructorAndMoveAssignmentOperatorTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				Set<int> movedSet;

				std::vector<int> insertOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					movedSet.Insert(element);
					currentSize++;
				}

				Set<int> set(std::move(movedSet));

				Assert::IsTrue(movedSet.IsEmpty());
				Assert::IsTrue(set.Size() == treeSize);
			}
		}
		
		TEST_METHOD(SetComparisonOperatorsTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				Set<int> set;


				std::vector<int> insertOrder;
				size_t currentSize = 0;

				for (int i = 0; i < treeSize; i++)
				{
					insertOrder.push_back(i);
				}

				std::shuffle(insertOrder.begin(), insertOrder.end(), default_random_engine(rand()));

				for (int element : insertOrder)
				{
					set.Insert(element);
					currentSize++;
				}

				Set<int> setCopy(set);

				Assert::IsTrue(setCopy == set);

				int removedVal1 = rand() % (treeSize - 1);
				int removedVal2 = rand() % (treeSize - 1);


				while (removedVal1 == removedVal2)
				{
					removedVal1 = rand() % (treeSize - 1);
					removedVal2 = rand() % (treeSize - 1);
				}

				set.Remove(removedVal1);
				setCopy.Remove(removedVal1);

				Assert::IsTrue(setCopy == set);

				set.Remove(removedVal2);

				Assert::IsTrue(setCopy != set);
			}
		}
		
	private:
		
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SetTest::sStartMemState;
}
