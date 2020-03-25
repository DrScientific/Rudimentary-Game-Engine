#pragma once

#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "Factory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FooFactoryTest)
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

		TEST_METHOD(FooFactoryConstructorTest)
		{
			FooFactory fooFactory;
		}

		TEST_METHOD(FooFactoryCreateTest)
		{
			FooFactory fooFactory;
			RTTI * newFoo = fooFactory.Create();
			newFoo->As<Foo>()->SetData(100);
			Assert::IsTrue(newFoo->As<Foo>()->Data() == 100);
			delete newFoo;
		}

		TEST_METHOD(FooFactoryGetNameTest)
		{
			FooFactory fooFactory;
			
			Assert::IsTrue(fooFactory.GetClassName() == "Foo");
		}

		TEST_METHOD(FooFactoryExceptionTest)
		{
			FooFactory fooFactory;
			auto multipleFooFactoriesException = [&fooFactory] { FooFactory newFooFactory; };
			Assert::ExpectException<std::exception>(multipleFooFactoriesException);
		}

		TEST_METHOD(AbstractFactoryCreateTest)
		{
			FooFactory fooFactory;
			RTTI * newFoo = FIEAGameEngine::Factory<RTTI>::Create(fooFactory.GetClassName());
			newFoo->As<Foo>()->SetData(100);
			Assert::IsTrue(newFoo->As<Foo>()->Data() == 100);
			delete newFoo;
		}

		TEST_METHOD(FactoryFindTest)
		{
			Factory<RTTI> const * factory = Factory<RTTI>::Find("Foo");

			Assert::IsNull(factory);

			{

				FooFactory foofactory;

				Assert::IsNotNull(Factory<RTTI>::Find("Foo"));

			}

			Assert::IsNull(Factory<RTTI>::Find("Foo"));
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState FooFactoryTest::sStartMemState;
}