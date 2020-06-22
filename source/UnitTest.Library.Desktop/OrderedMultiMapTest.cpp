#include "pch.h"
#include "CppUnitTest.h"
#include "TestModuleConstants.h"
#include "Foo.h"
#include "OrderedMultiMap.h"
#include "Vector.h"
#include <random>
#include <chrono>

#define _DEBUG_FUNCTIONAL_MACHINERY = 1

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;
using namespace UnitTests;

std::vector<int> k;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(OrderedMultiMapTest)
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
			OrderedMultiMap<Foo, std::string> orderedMultiMap;
			Assert::IsTrue(orderedMultiMap.Size() == 0);
			Assert::IsTrue(orderedMultiMap.IsEmpty());
			Assert::IsTrue(orderedMultiMap.VerifyRedBlackTree());
			Assert::IsTrue(orderedMultiMap.VerifySize());
		}

		TEST_METHOD(InitializerListConstructorTest)
		{
			OrderedMultiMap<Foo, std::string> orderedMultiMap
			{	{0, "0"}, {0, "0"}, {0, "0"}, {1, "1"}, {1, "1"}, {1, "1"}, {2, "2"}, {2, "2"}, {2, "2"},{3, "3"}, {3, "3"}, {3, "3"},
				{4, "4"}, {4, "4"}, {4, "4"}, {5, "5"}, {5, "5"}, {5, "5"}, {6, "6"}, {6, "6"}, {6, "6"},{7, "7"}, {7, "7"}, {7, "7"},
				{8, "8"}, {8, "8"}, {8, "8"}, {9, "9"}, {9, "9"}, {9, "9"}, {10, "10"}, {10, "10"}, {10, "10"}, {11, "11"}, {11, "11"}, {11, "11"},
				{12, "12"}, {12, "12"}, {12, "12"}, {13, "13"}, {13, "13"}, {13, "13"}, {14, "14"}, {14, "14"}, {14, "14"}, {15, "15"}, {15, "15"}, {15, "15"}
			};
			Assert::IsTrue(orderedMultiMap.Size() == 16 * 3);
			Assert::IsFalse(orderedMultiMap.IsEmpty());
			Assert::IsTrue(orderedMultiMap.VerifyRedBlackTree());
			Assert::IsTrue(orderedMultiMap.VerifySize());
		}

		TEST_METHOD(IteratorIncrementTest)
		{
			OrderedMultiMap<Foo, std::string> orderedMultiMap;
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiMap.Insert(i, std::to_string(i));
				}
			}
			int i = 0;
			for (OrderedMultiMap<Foo, std::string>::Iterator it = orderedMultiMap.begin(); it != orderedMultiMap.end(); i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(std::pair<Foo const,std::string>(i, std::to_string(i)) == *it);
					it++;
				}
			}
		}

		TEST_METHOD(FindAndContainsTest)
		{
			OrderedMultiMap<Foo, std::string> orderedMultiMap;
			Assert::IsTrue(orderedMultiMap.Find(0) == orderedMultiMap.end());
			Assert::IsFalse(orderedMultiMap.Contains(0));
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiMap.Insert(i, std::to_string(i));
				}
			}
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiMap.Contains(i));
					OrderedMultiMap<Foo, std::string>::Iterator foundValue = orderedMultiMap.Find(i);
					Assert::IsTrue(*foundValue == std::pair<Foo const,std::string>(i, std::to_string(i)));
					orderedMultiMap.Remove(foundValue);
				}
				Assert::IsFalse(orderedMultiMap.Contains(i));
				Assert::IsTrue(orderedMultiMap.Find(i) == orderedMultiMap.end());
			}
		}

		TEST_METHOD(LowerBoundTest)
		{
			OrderedMultiMap<Foo, std::string> orderedMultiMap;
			Assert::IsTrue(orderedMultiMap.LowerBound(0) == orderedMultiMap.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiMap.Insert(i * 2, std::to_string(i *2));
				}
			}

			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					OrderedMultiMap<Foo, std::string>::Iterator lowerBound = orderedMultiMap.LowerBound(i * 2 - 1);
					Assert::IsTrue(*lowerBound == std::pair<Foo const, std::string>(i * 2, std::to_string(i*2)));
					orderedMultiMap.Remove(lowerBound);
				}
				OrderedMultiMap<Foo, std::string>::Iterator lowerBound = orderedMultiMap.LowerBound(i * 2 - 1);
				Assert::IsTrue(*lowerBound == std::pair<Foo const, std::string>((i+1) * 2, std::to_string((i+1) * 2)));
			}

			OrderedMultiMap<Foo, std::string>::Iterator allElementsLower = orderedMultiMap.LowerBound(static_cast<int>(treeSize));
			Assert::IsTrue(allElementsLower == orderedMultiMap.end());
		}

		TEST_METHOD(UpperBoundTest)
		{
			OrderedMultiMap<Foo, std::string> orderedMultiMap;
			Assert::IsTrue(orderedMultiMap.UpperBound(0) == orderedMultiMap.end());
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					orderedMultiMap.Insert(i * 2, std::to_string(i *2));
				}
			}
			for (int i = 0; i < uniqueTreeElements - 1; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					OrderedMultiMap<Foo, std::string>::Iterator upperBound = orderedMultiMap.UpperBound(i * 2);
					Assert::IsTrue(*upperBound == std::pair<Foo const, std::string>((i + 1) * 2, std::to_string((i + 1) * 2)));
					orderedMultiMap.Remove(--upperBound);
				}
				OrderedMultiMap<Foo, std::string>::Iterator upperBound = orderedMultiMap.UpperBound(i * 2);
				Assert::IsTrue(*upperBound == std::pair<Foo const, std::string>((i + 1) * 2, std::to_string((i + 1) * 2)));
			}
			OrderedMultiMap<Foo, std::string>::Iterator allElementsLower = orderedMultiMap.UpperBound(static_cast<int>(treeSize - 1));
			Assert::IsTrue(allElementsLower == orderedMultiMap.end());
		}

		TEST_METHOD(CountTest)
		{
			OrderedMultiMap<Foo, std::string> orderedMultiMap;
			Assert::IsTrue(orderedMultiMap.Count(0) == 0);
			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiMap.Count(i) == j);
					orderedMultiMap.Insert(i, std::to_string(i));
				}
				Assert::IsTrue(orderedMultiMap.Count(i) == numDuplicatesOfUniqueElement);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				Assert::IsTrue(orderedMultiMap.Count(i) == numDuplicatesOfUniqueElement);
				orderedMultiMap.Remove(i);
				Assert::IsTrue(orderedMultiMap.Count(i) == 0);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiMap.Count(i) == j);
					orderedMultiMap.Insert(i, std::to_string(i));
				}
				Assert::IsTrue(orderedMultiMap.Count(i) == numDuplicatesOfUniqueElement);
			}

			for (int i = 0; i < uniqueTreeElements; i++)
			{
				for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
				{
					Assert::IsTrue(orderedMultiMap.Count(i) == numDuplicatesOfUniqueElement - j);
					orderedMultiMap.Remove(orderedMultiMap.Find(i));
				}
				Assert::IsTrue(orderedMultiMap.Count(i) == 0);
			}
		}

		TEST_METHOD(InsertTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> orderedMultiMap;
				Vector<Foo> insertOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					insertOrder.push_back(i);
				}

				insertOrder.Shuffle();

				size_t currentSize = 0;
				for (Foo element : insertOrder)
				{
					Assert::IsFalse(orderedMultiMap.Contains(element));
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						orderedMultiMap.Insert(element, std::to_string(element.Data()));
						Assert::IsTrue(orderedMultiMap.Contains(element));
						currentSize++;
						Assert::IsTrue(currentSize == orderedMultiMap.Size());
						Assert::IsTrue(orderedMultiMap.VerifyRedBlackTree());
						Assert::IsTrue(orderedMultiMap.VerifySize());
					}
				}
			}
		}

		TEST_METHOD(RemoveByValueTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> orderedMultiMap;
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
						orderedMultiMap.Insert(element, std::to_string(element.Data()));
					}
				}

				size_t currentSize = orderedMultiMap.Size();
				for (Foo element : removeOrder)
				{
					orderedMultiMap.Remove(element);
					Assert::IsFalse(orderedMultiMap.Contains(element));
					currentSize -= numDuplicatesOfUniqueElement;
					Assert::IsTrue(currentSize == orderedMultiMap.Size());
					Assert::IsTrue(orderedMultiMap.VerifyRedBlackTree());
					Assert::IsTrue(orderedMultiMap.VerifySize());
				}
			}
		}

		TEST_METHOD(RemoveByIteratorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> orderedMultiMap;
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
						orderedMultiMap.Insert(element, std::to_string(element.Data()));
					}
				}

				size_t currentSize = orderedMultiMap.Size();
				for (Foo element : removeOrder)
				{
					for (size_t j = 0; j < numDuplicatesOfUniqueElement; j++)
					{
						Assert::IsTrue(orderedMultiMap.Contains(element));
						orderedMultiMap.Remove(orderedMultiMap.Find(element));
						Assert::IsTrue(--currentSize == orderedMultiMap.Size());
						Assert::IsTrue(orderedMultiMap.VerifyRedBlackTree());
						Assert::IsTrue(orderedMultiMap.VerifySize());
					}
					Assert::IsFalse(orderedMultiMap.Contains(element));
				}
			}
		}

		TEST_METHOD(CopyConstructorAndAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> orderedMultiMap;
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
						orderedMultiMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMultiMap<Foo, std::string> orderedMultiMapCopy(orderedMultiMap);

				Assert::IsTrue(orderedMultiMapCopy == orderedMultiMap);

				orderedMultiMap.Remove(rand() % (uniqueTreeElements - 1));

				Assert::IsFalse(orderedMultiMapCopy == orderedMultiMap);
			}
		}

		TEST_METHOD(MoveConstructorAndMoveAssignmentOperatorTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> movedOrderedMultiMap;
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
						movedOrderedMultiMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMultiMap<Foo, std::string> orderedMultiMap(std::move(movedOrderedMultiMap));

				Assert::IsTrue(movedOrderedMultiMap.IsEmpty());
				Assert::IsTrue(orderedMultiMap.Size() == treeSize);
			}
		}

		TEST_METHOD(SwapTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> orderedMultiMap;
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
						orderedMultiMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMultiMap<Foo, std::string> orderedMultiMap2(orderedMultiMap);

				orderedMultiMap2.Remove(rand() % (uniqueTreeElements - 1));

				OrderedMultiMap<Foo, std::string> orderedMultiMapCopy(orderedMultiMap);
				OrderedMultiMap<Foo, std::string> orderedMultiMap2Copy(orderedMultiMap2);

				Assert::IsTrue(orderedMultiMap == orderedMultiMapCopy);
				Assert::IsFalse(orderedMultiMap == orderedMultiMap2Copy);
				Assert::IsTrue(orderedMultiMap2 == orderedMultiMap2Copy);
				Assert::IsFalse(orderedMultiMap2 == orderedMultiMapCopy);

				orderedMultiMap.Swap(orderedMultiMap2);

				Assert::IsTrue(orderedMultiMap == orderedMultiMap2Copy);
				Assert::IsFalse(orderedMultiMap == orderedMultiMapCopy);
				Assert::IsTrue(orderedMultiMap2 == orderedMultiMapCopy);
				Assert::IsFalse(orderedMultiMap2 == orderedMultiMap2Copy);
			}
		}

		TEST_METHOD(ComparisonOperatorsTest)
		{
			for (size_t currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				OrderedMultiMap<Foo, std::string> orderedMultiMap;
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
						orderedMultiMap.Insert(element, std::to_string(element.Data()));
					}
				}

				OrderedMultiMap<Foo, std::string> orderedMultiMapCopy(orderedMultiMap);

				Assert::IsTrue(orderedMultiMapCopy == orderedMultiMap);

				Vector<Foo> removeOrder;

				for (int i = 0; i < uniqueTreeElements; i++)
				{
					removeOrder.push_back(i);
				}

				removeOrder.Shuffle();

				size_t removeOrderIndex = 0;
				while (removeOrderIndex < removeOrder.Size() - 1)
				{
					Assert::IsTrue(orderedMultiMapCopy == orderedMultiMap);

					orderedMultiMap.Remove(removeOrder[removeOrderIndex]);
					Assert::IsFalse(orderedMultiMapCopy == orderedMultiMap);

					orderedMultiMapCopy.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedMultiMapCopy == orderedMultiMap);

					orderedMultiMap.Remove(removeOrder[removeOrderIndex + 1]);
					Assert::IsFalse(orderedMultiMapCopy == orderedMultiMap);

					orderedMultiMapCopy.Remove(removeOrder[removeOrderIndex]);
					Assert::IsTrue(orderedMultiMapCopy == orderedMultiMap);

					removeOrderIndex += 2;
				}
			}
		}

	private:

		static _CrtMemState sStartMemState;
	};

	_CrtMemState OrderedMultiMapTest::sStartMemState;
}
