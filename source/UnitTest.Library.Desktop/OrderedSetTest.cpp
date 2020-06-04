#include "pch.h"
#include "CppUnitTest.h"
#include "TestModuleConstants.h"
#include "Foo.h"
#include "OrderedSet.h"
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
	TEST_CLASS(OrderedSetTest)
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

		TEST_METHOD(OrderedSetConstructorTest)
		{
			OrderedSet<Foo> orderedSet;
			Assert::IsTrue(orderedSet.Size() == 0);
			Assert::IsTrue(orderedSet.IsEmpty());
		}

		TEST_METHOD(OrderedSetInitializerListConstructorTest)
		{
			OrderedSet<Foo> orderedSet
			{ 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
				4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7,
				8, 8, 8, 9, 9, 9, 10, 10, 10, 11 ,11, 11,
				12, 12, 12, 13, 13, 13, 14 ,14 ,14, 15, 15, 15
			};
			Assert::IsTrue(orderedSet.Size() == 16);
			Assert::IsFalse(orderedSet.IsEmpty());
			Assert::IsTrue(orderedSet.VerifyRedBlackTree());
			Assert::IsTrue(orderedSet.VerifySize());
		}

		TEST_METHOD(OrderedSetIteratorIncrementTest)
		{
			OrderedSet<Foo> orderedSet;
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedSet.Insert(i);
				}
			}
			int i = 0;
			for (OrderedSet<Foo>::Iterator it = orderedSet.begin(); it != orderedSet.end(); i++, it++)
			{
				Assert::IsTrue(i == *it);
			}
		}

		TEST_METHOD(OrderedSetFindAndContainsTest)
		{
			OrderedSet<Foo> orderedSet;
			Assert::IsTrue(orderedSet.Find(0) == orderedSet.end());
			Assert::IsFalse(orderedSet.Contains(0));
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedSet.Insert(i);
				}
			}
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedSet.Contains(i));
				OrderedSet<Foo>::Iterator foundValue = orderedSet.Find(i);
				Assert::IsTrue(*foundValue == i);
				orderedSet.Remove(foundValue);
				Assert::IsFalse(orderedSet.Contains(i));
				Assert::IsTrue(orderedSet.Find(i) == orderedSet.end());
			}
		}

		TEST_METHOD(OrderedSetLowerBoundTest)
		{
			OrderedSet<Foo> orderedSet;
			Assert::IsTrue(orderedSet.LowerBound(0) == orderedSet.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedSet.Insert(i * 2);
				}
			}

			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{

				OrderedSet<Foo>::Iterator lowerBound = orderedSet.LowerBound(i * 2 - 1);
				Assert::IsTrue(*lowerBound == i * 2);
				orderedSet.Remove(lowerBound);
			}

			OrderedSet<Foo>::Iterator allElementsLower = orderedSet.LowerBound(static_cast<int>(treeSize));
			Assert::IsTrue(allElementsLower == orderedSet.end());
		}

		TEST_METHOD(OrderedSetUpperBoundTest)
		{
			OrderedSet<Foo> orderedSet;
			Assert::IsTrue(orderedSet.UpperBound(0) == orderedSet.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedSet.Insert(i * 2);
				}
			}
			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{
				OrderedSet<Foo>::Iterator upperBound = orderedSet.UpperBound(i * 2);
				Assert::IsTrue(*upperBound == (i + 1) * 2);
				orderedSet.Remove(--upperBound);
			}
			OrderedSet<Foo>::Iterator allElementsLower = orderedSet.UpperBound(static_cast<int>(treeSize - 1));
			Assert::IsTrue(allElementsLower == orderedSet.end());
		}

		TEST_METHOD(OrderedSetCountTest)
		{
			OrderedSet<Foo> orderedSet;
			Assert::IsTrue(orderedSet.Count(0) == 0);
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedSet.Count(i) == 0);
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedSet.Insert(i);
					Assert::IsTrue(orderedSet.Count(i) == 1);
				}
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedSet.Count(i) == 1);
				orderedSet.Remove(i);
				Assert::IsTrue(orderedSet.Count(i) == 0);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedSet.Count(i) == 0);
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedSet.Insert(i);
					Assert::IsTrue(orderedSet.Count(i) == 1);
				}
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedSet.Count(i) == 1);
				orderedSet.Remove(orderedSet.Find(i));
				Assert::IsTrue(orderedSet.Count(i) == 0);
			}
		}

		TEST_METHOD(OrderedSetInsertTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> orderedSet;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				size_t currentSize = 0;
				for (Foo element : insertOrder)
				{
					Assert::IsFalse(orderedSet.Contains(element));
					currentSize++;
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedSet.Insert(element);
						Assert::IsTrue(orderedSet.Contains(element));
						Assert::IsTrue(currentSize == orderedSet.Size());
						Assert::IsTrue(orderedSet.VerifyRedBlackTree());
						Assert::IsTrue(orderedSet.VerifySize());
					}
				}
			}
		}

		TEST_METHOD(OrderedSetRemoveByValueTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> orderedSet;
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
						orderedSet.Insert(element);
					}
				}

				size_t currentSize = orderedSet.Size();
				for (Foo element : removeOrder)
				{
					orderedSet.Remove(element);
					Assert::IsFalse(orderedSet.Contains(element));
					currentSize--;
					Assert::IsTrue(currentSize == orderedSet.Size());
					Assert::IsTrue(orderedSet.VerifyRedBlackTree());
					Assert::IsTrue(orderedSet.VerifySize());
				}
			}
		}

		TEST_METHOD(OrderedSetRemoveByIteratorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> orderedSet;
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
						orderedSet.Insert(element);
					}
				}

				size_t currentSize = orderedSet.Size();
				for (Foo element : removeOrder)
				{
					Assert::IsTrue(orderedSet.Contains(element));
					orderedSet.Remove(orderedSet.Find(element));
					Assert::IsFalse(orderedSet.Contains(element));
					--currentSize;
					Assert::IsTrue(currentSize == orderedSet.Size());
					Assert::IsTrue(orderedSet.VerifyRedBlackTree());
					Assert::IsTrue(orderedSet.VerifySize());
				}
			}
		}

		TEST_METHOD(OrderedSetCopyConstructorAndAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> orderedSet;
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
						orderedSet.Insert(element);
					}
				}

				OrderedSet<Foo> orderedSetCopy(orderedSet);

				Assert::IsTrue(orderedSetCopy == orderedSet);

				orderedSet.Remove(rand() % (uniqueTreeElements - 1));

				Assert::IsFalse(orderedSetCopy == orderedSet);
			}
		}

		TEST_METHOD(OrderedSetMoveConstructorAndMoveAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> movedOrderedSet;
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
						movedOrderedSet.Insert(element);
					}
				}

				OrderedSet<Foo> orderedSet(std::move(movedOrderedSet));

				Assert::IsTrue(movedOrderedSet.IsEmpty());
				Assert::IsTrue(orderedSet.Size() == uniqueTreeElements);
			}
		}

		TEST_METHOD(OrderedSetSwapTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> orderedSet;
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
						orderedSet.Insert(element);
					}
				}

				OrderedSet<Foo> orderedSet2(orderedSet);

				orderedSet2.Remove(rand() % (uniqueTreeElements - 1));

				OrderedSet<Foo> orderedSetCopy(orderedSet);
				OrderedSet<Foo> orderedSet2Copy(orderedSet2);

				Assert::IsTrue(orderedSet == orderedSetCopy);
				Assert::IsFalse(orderedSet == orderedSet2Copy);
				Assert::IsTrue(orderedSet2 == orderedSet2Copy);
				Assert::IsFalse(orderedSet2 == orderedSetCopy);

				orderedSet.Swap(orderedSet2);

				Assert::IsTrue(orderedSet == orderedSet2Copy);
				Assert::IsFalse(orderedSet == orderedSetCopy);
				Assert::IsTrue(orderedSet2 == orderedSetCopy);
				Assert::IsFalse(orderedSet2 == orderedSet2Copy);
			}
		}

		TEST_METHOD(OrderedSetComparisonOperatorsTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedSet<Foo> orderedSet;
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
						orderedSet.Insert(element);
					}
				}

				OrderedSet<Foo> orderedSetCopy(orderedSet);

				Assert::IsTrue(orderedSetCopy == orderedSet);

				Vector<Foo> removeOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					removeOrder.push_back(i);
				}

				removeOrder.Shuffle();

				int removeOrderIndex = 0;
				while (removeOrderIndex < removeOrder.Size() - 1)
				{
					Assert::IsTrue(orderedSetCopy == orderedSet);

					orderedSet.Remove(removeOrder[removeOrderIndex]);
					Assert::IsFalse(orderedSetCopy == orderedSet);

					orderedSetCopy.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedSetCopy == orderedSet);

					orderedSet.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedSetCopy == orderedSet);

					orderedSetCopy.Remove(removeOrder[removeOrderIndex]);
					Assert::IsTrue(orderedSetCopy == orderedSet);

					removeOrderIndex += 2;
				}
			}
		}

	private:

		static _CrtMemState sStartMemState;
	};

	_CrtMemState OrderedSetTest::sStartMemState;
}
