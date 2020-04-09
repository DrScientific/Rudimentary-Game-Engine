#include "pch.h"

#include "CppUnitTest.h"
#include "RedBlackTree.h"
#include "Vector.h"
#include <algorithm>
#include <random>
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;


namespace UnitTestLibraryDesktop
{
	TEST_CLASS(RedBlackTreeTest)
	{
	public:

		size_t const treeSize = 256;
		size_t const testIterations = 100000;

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
		TEST_METHOD(RedBlackTreeConstructorTest)
		{
			RedBlackTree<int> tree;
		}

		TEST_METHOD(RedBlackTreeInitializerListConstructorTest)
		{
			RedBlackTree<int> tree{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
		}

		TEST_METHOD(RedBlackTreeIteratorIncrementTest)
		{
			RedBlackTree<int> tree{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
			int i = 0;
			for (RedBlackTree<int>::Iterator it = tree.begin(); it != tree.end(); i++, it++)
			{
				Assert::AreEqual(i, *it);
			}
		}

		TEST_METHOD(RedBlackTreeFindTest)
		{
			RedBlackTree<int> tree{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
			int i = 0;
			
			for (int i = 0; i < 16; i++)
			{
				Assert::AreEqual(*(tree.Find(i)), i);
			}
			Assert::AreEqual(tree.Find(-1), tree.end());
			Assert::AreEqual(tree.Find(16), tree.end());
		}

		TEST_METHOD(RedBlackTreeInsertTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				RedBlackTree<int> tree;
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
					tree.Insert(element);
					currentSize++;
					Assert::IsTrue(currentSize == tree.Size());
					Assert::IsTrue(tree.VerifyRedBlackTree());
				}

				int currentElement = 0;
				for (RedBlackTree<int>::Iterator it = tree.begin(); it != tree.end(); currentElement++, it++)
				{
					Assert::AreEqual(currentElement, *it);
				}
			}
		}

		TEST_METHOD(RedBlackTreeRemoveTest)
		{
			for (int currentIteration = 0; currentIteration < testIterations; currentIteration++)
			{
				RedBlackTree<int> tree;
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
					tree.Insert(element);
					currentSize++;
					Assert::IsTrue(currentSize == tree.Size());
					Assert::IsTrue(tree.VerifyRedBlackTree());
				}


				int currentElement = 0;
				for (RedBlackTree<int>::Iterator it = tree.begin(); it != tree.end(); currentElement++, it++)
				{
					Assert::AreEqual(currentElement, *it);
				}

				std::shuffle(removeOrder.begin(), removeOrder.end(), default_random_engine(rand()));

				currentSize = treeSize;
				for (int element : removeOrder)
				{
					tree.Remove(element);
					currentSize--;
					Assert::IsTrue(currentSize == tree.Size());
					Assert::IsTrue(tree.VerifyRedBlackTree());
					
				}
			}
			
		}

	private:
		
		static _CrtMemState sStartMemState;
	};

	_CrtMemState RedBlackTreeTest::sStartMemState;
}