#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "DefaultHashFunctor.h"
#include "DefaultHashFunctorTemplates.h"
#include <random>
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DefaultHashFunctorTest)
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
				_CrtDumpMemoryLeaks();
				Assert::Fail(L"Memory leak detected!\nIf a static object is dynamically allocating memory this may be a false positive.");
			}
#endif
		}

		TEST_METHOD(ExpectedHashFunctorValues)
		{
			srand(static_cast<unsigned int>(time(NULL)));
			
			DefaultHashFunctor<int> intFunctor;
			
			int testInt1 = rand();
			int testInt2 = testInt1;
			int testInt3 = rand();
			size_t testInt1Hash = intFunctor(testInt1);
			size_t testInt2Hash = intFunctor(testInt2);
			size_t testInt3Hash = intFunctor(testInt3);

			Assert::IsTrue(testInt1Hash == testInt2Hash);
			Assert::IsTrue(testInt3Hash != testInt1Hash);
			Assert::IsTrue(testInt3Hash != testInt2Hash);

			DefaultHashFunctor<char*> cStringFunctor;
			
			char* testCString1 = "Hello";
			char testCString2[6];
			strcpy_s(testCString2, testCString1);
			char* testCString3 = "Goodbye";
			size_t testCString1Hash = cStringFunctor(testCString1);
			size_t testCString2Hash = cStringFunctor(testCString2);
			size_t testCString3Hash = cStringFunctor(testCString3);

			Assert::IsTrue(testCString1Hash == testCString2Hash);
			Assert::IsTrue(testCString3Hash != testCString1Hash);
			Assert::IsTrue(testCString3Hash != testCString2Hash);

			DefaultHashFunctor<std::string> stringFunctor;
			
			std::string testString1 = "Hello";
			std::string testString2 = testCString1;
			std::string testString3 = "Goodbye";
			size_t testString1Hash = stringFunctor(testString1);
			size_t testString2Hash = stringFunctor(testString2);
			size_t testString3Hash = stringFunctor(testString3);

			Assert::IsTrue(testString1Hash == testString2Hash);
			Assert::IsTrue(testString3Hash != testString1Hash);
			Assert::IsTrue(testString3Hash != testString2Hash);

			DefaultHashFunctor<Foo> fooFunctor;

			Foo testFoo1 = Foo(rand());
			Foo testFoo2 = Foo(testFoo1);
			Foo testFoo3 = Foo(rand());
			size_t testFoo1Hash = fooFunctor(testFoo1);
			size_t testFoo2Hash = fooFunctor(testFoo2);
			size_t testFoo3Hash = fooFunctor(testFoo3);

			Assert::IsTrue(testFoo1Hash == testFoo2Hash);
			Assert::IsTrue(testFoo3Hash != testFoo1Hash);
			Assert::IsTrue(testFoo3Hash != testFoo2Hash);

		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState DefaultHashFunctorTest::sStartMemState;
}