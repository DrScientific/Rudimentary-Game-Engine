#include "pch.h"
#include "CppUnitTest.h"
#include "TestModuleConstants.h"
#include "Foo.h"
#include "OrderedMultiSet.h"
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
	TEST_CLASS(OrderedMultiSetTest)
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

		TEST_METHOD(ConstructorTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet;
			Assert::IsTrue(orderedMultiSet.Size() == 0);
			Assert::IsTrue(orderedMultiSet.IsEmpty());
			Assert::IsTrue(orderedMultiSet.VerifyRedBlackTree());
			Assert::IsTrue(orderedMultiSet.VerifySize());
		}

		TEST_METHOD(InitializerListConstructorTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet
			{	0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3,
				4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7,
				8, 8, 8, 9, 9, 9, 10, 10, 10, 11 ,11, 11,
				12, 12, 12, 13, 13, 13, 14 ,14 ,14, 15, 15, 15
			};
			Assert::IsTrue(orderedMultiSet.Size() == 16*3);
			Assert::IsFalse(orderedMultiSet.IsEmpty());
			Assert::IsTrue(orderedMultiSet.VerifyRedBlackTree());
			Assert::IsTrue(orderedMultiSet.VerifySize());
		}

		TEST_METHOD(IteratorIncrementTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet;
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiSet.Insert(i);
				}
			}
			int i = 0;
			for (OrderedMultiSet<Foo>::Iterator it = orderedMultiSet.begin(); it != orderedMultiSet.end(); i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(i == *it);
					it++;
				}
			}
		}

		TEST_METHOD(FindAndContainsTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet;
			Assert::IsTrue(orderedMultiSet.Find(0) == orderedMultiSet.end());
			Assert::IsFalse(orderedMultiSet.Contains(0));
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiSet.Insert(i);
				}
			}
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiSet.Contains(i));
					OrderedMultiSet<Foo>::Iterator foundValue = orderedMultiSet.Find(i);
					Assert::IsTrue(*foundValue == i);
					orderedMultiSet.Remove(foundValue);
				}
				Assert::IsFalse(orderedMultiSet.Contains(i));
				Assert::IsTrue(orderedMultiSet.Find(i) == orderedMultiSet.end());
			}
		}

		TEST_METHOD(LowerBoundTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet;
			Assert::IsTrue(orderedMultiSet.LowerBound(0) == orderedMultiSet.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiSet.Insert(i*2);
				}
			}

			for (int i = 0; i < uniqueTreeElements-1; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					OrderedMultiSet<Foo>::Iterator lowerBound = orderedMultiSet.LowerBound(i * 2 - 1);
					Assert::IsTrue(*lowerBound == i * 2);
					orderedMultiSet.Remove(lowerBound);
				}
				OrderedMultiSet<Foo>::Iterator lowerBound = orderedMultiSet.LowerBound(i * 2 - 1);
				Assert::IsTrue(*lowerBound == (i+1) * 2);
			}

			OrderedMultiSet<Foo>::Iterator allElementsLower = orderedMultiSet.LowerBound(static_cast<int>(treeSize));
			Assert::IsTrue(allElementsLower == orderedMultiSet.end());
		}

		TEST_METHOD(UpperBoundTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet;
			Assert::IsTrue(orderedMultiSet.UpperBound(0) == orderedMultiSet.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiSet.Insert(i * 2);
				}
			}
			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					OrderedMultiSet<Foo>::Iterator upperBound = orderedMultiSet.UpperBound(i * 2);
					Assert::IsTrue(*upperBound == (i + 1) * 2);
					orderedMultiSet.Remove(--upperBound);
				}
				OrderedMultiSet<Foo>::Iterator upperBound = orderedMultiSet.UpperBound(i * 2);
				Assert::IsTrue(*upperBound == (i + 1) * 2);
			}
			OrderedMultiSet<Foo>::Iterator allElementsLower = orderedMultiSet.UpperBound(static_cast<int>(treeSize - 1));
			Assert::IsTrue(allElementsLower == orderedMultiSet.end());
		}

		TEST_METHOD(CountTest)
		{
			OrderedMultiSet<Foo> orderedMultiSet;
			Assert::IsTrue(orderedMultiSet.Count(0) == 0);
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiSet.Count(i) == j);
					orderedMultiSet.Insert(i);
				}
				Assert::IsTrue(orderedMultiSet.Count(i) == numDuplicatesOfUniqueElement);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMultiSet.Count(i) == numDuplicatesOfUniqueElement);
				orderedMultiSet.Remove(i);
				Assert::IsTrue(orderedMultiSet.Count(i) == 0);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiSet.Count(i) == j);
					orderedMultiSet.Insert(i);
				}
				Assert::IsTrue(orderedMultiSet.Count(i) == numDuplicatesOfUniqueElement);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiSet.Count(i) == numDuplicatesOfUniqueElement - j);
					orderedMultiSet.Remove(orderedMultiSet.Find(i));
				}
				Assert::IsTrue(orderedMultiSet.Count(i) == 0);
			}
		}

		TEST_METHOD(InsertTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> orderedMultiSet;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				size_t currentSize = 0;
				for (Foo element : insertOrder)
				{
					Assert::IsFalse(orderedMultiSet.Contains(element));
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMultiSet.Insert(element);
						Assert::IsTrue(orderedMultiSet.Contains(element));
						currentSize++;
						Assert::IsTrue(currentSize == orderedMultiSet.Size());
						Assert::IsTrue(orderedMultiSet.VerifyRedBlackTree());
						Assert::IsTrue(orderedMultiSet.VerifySize());
					}
				}
			}
		}

		TEST_METHOD(RemoveByValueTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> orderedMultiSet;
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
						orderedMultiSet.Insert(element);
					}
				}

				size_t currentSize = orderedMultiSet.Size();
				for (Foo element : removeOrder)
				{
					orderedMultiSet.Remove(element);
					Assert::IsFalse(orderedMultiSet.Contains(element));
					currentSize -= numDuplicatesOfUniqueElement;
					Assert::IsTrue(currentSize == orderedMultiSet.Size());
					Assert::IsTrue(orderedMultiSet.VerifyRedBlackTree());
					Assert::IsTrue(orderedMultiSet.VerifySize());
				}
			}
		}

		TEST_METHOD(RemoveByIteratorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> orderedMultiSet;
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
						orderedMultiSet.Insert(element);
					}
				}

				size_t currentSize = orderedMultiSet.Size();
				for (Foo element : removeOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						Assert::IsTrue(orderedMultiSet.Contains(element));
						orderedMultiSet.Remove(orderedMultiSet.Find(element));
						Assert::IsTrue(--currentSize == orderedMultiSet.Size());
						Assert::IsTrue(orderedMultiSet.VerifyRedBlackTree());
						Assert::IsTrue(orderedMultiSet.VerifySize());
					}
					Assert::IsFalse(orderedMultiSet.Contains(element));
				}
			}
		}

		TEST_METHOD(CopyConstructorAndAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> orderedMultiSet;
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
						orderedMultiSet.Insert(element);
					}
				}

				OrderedMultiSet<Foo> orderedMultiSetCopy(orderedMultiSet);

				Assert::IsTrue(orderedMultiSetCopy == orderedMultiSet);

				orderedMultiSet.Remove(rand() % (uniqueTreeElements - 1));

				Assert::IsFalse(orderedMultiSetCopy == orderedMultiSet);
			}
		}

		TEST_METHOD(MoveConstructorAndMoveAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> movedOrderedMultiSet;
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
						movedOrderedMultiSet.Insert(element);
					}
				}

				OrderedMultiSet<Foo> orderedMultiSet(std::move(movedOrderedMultiSet));

				Assert::IsTrue(movedOrderedMultiSet.IsEmpty());
				Assert::IsTrue(orderedMultiSet.Size() == treeSize);
			}
		}

		TEST_METHOD(SwapTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> orderedMultiSet;
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
						orderedMultiSet.Insert(element);
					}
				}

				OrderedMultiSet<Foo> orderedMultiSet2(orderedMultiSet);

				orderedMultiSet2.Remove(rand() % (uniqueTreeElements - 1));

				OrderedMultiSet<Foo> orderedMultiSetCopy(orderedMultiSet);
				OrderedMultiSet<Foo> orderedMultiSet2Copy(orderedMultiSet2);

				Assert::IsTrue(orderedMultiSet == orderedMultiSetCopy);
				Assert::IsFalse(orderedMultiSet == orderedMultiSet2Copy);
				Assert::IsTrue(orderedMultiSet2 == orderedMultiSet2Copy);
				Assert::IsFalse(orderedMultiSet2 == orderedMultiSetCopy);

				orderedMultiSet.Swap(orderedMultiSet2);

				Assert::IsTrue(orderedMultiSet == orderedMultiSet2Copy);
				Assert::IsFalse(orderedMultiSet == orderedMultiSetCopy);
				Assert::IsTrue(orderedMultiSet2 == orderedMultiSetCopy);
				Assert::IsFalse(orderedMultiSet2 == orderedMultiSet2Copy);
			}
		}

		TEST_METHOD(ComparisonOperatorsTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiSet<Foo> orderedMultiSet;
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
						orderedMultiSet.Insert(element);
					}
				}

				OrderedMultiSet<Foo> orderedMultiSetCopy(orderedMultiSet);

				Assert::IsTrue(orderedMultiSetCopy == orderedMultiSet);

				Vector<Foo> removeOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					removeOrder.push_back(i);
				}

				removeOrder.Shuffle();

				size_t removeOrderIndex = 0;
				while (removeOrderIndex < removeOrder.Size() - 1)
				{
					Assert::IsTrue(orderedMultiSetCopy == orderedMultiSet);

					orderedMultiSet.Remove(removeOrder[removeOrderIndex]);
					Assert::IsFalse(orderedMultiSetCopy == orderedMultiSet);

					orderedMultiSetCopy.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedMultiSetCopy == orderedMultiSet);

					orderedMultiSet.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedMultiSetCopy == orderedMultiSet);

					orderedMultiSetCopy.Remove(removeOrder[removeOrderIndex]);
					Assert::IsTrue(orderedMultiSetCopy == orderedMultiSet);
					
					removeOrderIndex += 2;
				}
			}
		}

	private:

		static _CrtMemState sStartMemState;
	};

	_CrtMemState OrderedMultiSetTest::sStartMemState;
}
