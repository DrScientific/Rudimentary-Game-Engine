#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace FIEAGameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FooTest)
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

		TEST_METHOD(ConstructorTest)
		{
			Foo a;
			Assert::AreEqual(0, a.Data());

			const int data = 10;
			Foo b(data);
			Assert::AreEqual(data, b.Data());
			
		}
		TEST_METHOD(AssignmentOperatorTest)
		{
			Foo a;
			Assert::AreEqual(0, a.Data());

			const int data = 10;
			Foo b(data);
			Assert::AreEqual(data, b.Data());

			Assert::AreNotEqual(a.Data(), b.Data());

			a = b;
			Assert::AreEqual(a.Data(), b.Data());
		}

		TEST_METHOD(EquivalenceOperatorsTest)
		{
			Foo a;
			Assert::AreEqual(0, a.Data());

			const int data = 10;
			Foo b(data);
			Assert::AreEqual(data, b.Data());

			Assert::AreNotEqual(a.Data(), b.Data());
			Assert::IsFalse(a == b);
			Assert::IsTrue(a != b);

			a = b;
			Assert::AreEqual(a.Data(), b.Data());

			Assert::IsTrue(a == b);
			Assert::IsFalse(a != b);

		}

		

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FooTest::sStartMemState;
}