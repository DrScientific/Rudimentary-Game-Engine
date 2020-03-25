#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "Vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
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

		TEST_METHOD(TestDefaultConstructorAndDestructor)
		{
			Vector <Foo> fooVector;
			Assert::IsTrue(fooVector.IsEmpty());
			Assert::IsTrue(fooVector.Size() == 0);

			Vector <Foo> const constFooVector;
			Assert::IsTrue(fooVector.IsEmpty());
			Assert::IsTrue(fooVector.Size() == 0);
		}
		
		TEST_METHOD(TestInitializerListConstructor)
		{
			
			Foo bar(0), car(1), dar(2);
			Vector<Foo> fooVector = { bar, car, dar };
			Assert::IsFalse(fooVector.IsEmpty());
			Assert::IsTrue(fooVector.Size() == 3);
			Assert::IsTrue(*fooVector.begin() == bar);
			Assert::IsTrue(fooVector[0] == bar);
			Assert::IsTrue(*(++fooVector.begin()) == car);
			Assert::IsTrue(fooVector[1] == car);
			Assert::IsTrue(*(--(fooVector.end())) == dar);
			Assert::IsTrue(fooVector[2] == dar);
			
			Vector<Foo> const constFooVector = { bar, car, dar };
			Assert::IsFalse(constFooVector.IsEmpty());
			Assert::IsTrue(constFooVector.Size() == 3);
			Assert::IsTrue(*constFooVector.cbegin() == bar);
			Assert::IsTrue(constFooVector[0] == bar);
			Assert::IsTrue(*(++(constFooVector.cbegin())) == car);
			Assert::IsTrue(constFooVector[1] == car);
			Assert::IsTrue(*(--(fooVector.cend())) == dar);
			Assert::IsTrue(constFooVector[2] == dar);
			
		}

		TEST_METHOD(IteratorsExceptions)
		{
			Foo bar(0), car(1), dar(2);
			Vector<Foo> fooVector = { bar, car, dar };

			auto dereferenceEndException = [&fooVector] { *fooVector.end(); };
			Assert::ExpectException<std::exception>(dereferenceEndException);

			auto incrementEndException = [&fooVector] { ++(fooVector.end()); };
			Assert::ExpectException<std::exception>(incrementEndException);

			auto decrementBeginException = [&fooVector] { --(fooVector.cbegin()); };
			Assert::ExpectException<std::exception>(decrementBeginException);

			Vector<Foo> const constFooVector = { bar, car, dar };

			auto dereferenceCEndException = [&constFooVector] { *constFooVector.end(); };
			Assert::ExpectException<std::exception>(dereferenceCEndException);

			auto incrementCEndException = [&constFooVector] { ++(constFooVector.cend()); };
			Assert::ExpectException<std::exception>(incrementCEndException);

			auto decrementCBeginException = [&constFooVector] { --(constFooVector.cbegin()); };
			Assert::ExpectException<std::exception>(decrementCBeginException);

			Vector<Foo> foo2Vector = { bar, car, dar };
			auto iteratorsFromDifferentListsException = [&fooVector, &foo2Vector] { fooVector.Remove(fooVector.begin(), foo2Vector.end()); };
			Assert::ExpectException<std::exception>(iteratorsFromDifferentListsException);

		}
		TEST_METHOD(ReserveException)
		{
			Foo bar(0), car(1), dar(2);
			Vector<Foo> fooVector = { bar, car, dar };
			auto reserveTooSmallException = [&fooVector] { fooVector.Reserve(2); };
			Assert::ExpectException<std::exception>(reserveTooSmallException);
		}
		TEST_METHOD(IndexOutOfBoundsException)
		{
			Foo bar(0), car(1), dar(2);
			Vector<Foo> fooVector = { bar, car, dar };
			auto indexOutOfBoundsOfSizeException = [&fooVector] { fooVector[4]; };
			Assert::ExpectException<std::exception>(indexOutOfBoundsOfSizeException);

			auto indexOutOfBoundsOfCapacityException = [&fooVector] { fooVector[100]; };
			Assert::ExpectException<std::exception>(indexOutOfBoundsOfCapacityException);

			Vector<Foo> const constFooVector = { bar, car, dar };
			auto constIndexOutOfBoundsException = [&constFooVector] { constFooVector[4]; };
			Assert::ExpectException<std::exception>(constIndexOutOfBoundsException);

			auto constIndexOutOfCapacityException = [&constFooVector] { constFooVector[100]; };
			Assert::ExpectException<std::exception>(constIndexOutOfCapacityException);
			

		}
		TEST_METHOD(TestFrontAndBack)
		{
			Vector <Foo> emptyFooVector;

			Assert::IsTrue(emptyFooVector.IsEmpty());

			auto frontFooVectorException = [&emptyFooVector] { emptyFooVector.Front(); };
			Assert::ExpectException<std::exception>(frontFooVectorException);

			auto backFooVectorException = [&emptyFooVector] { emptyFooVector.Back(); };
			Assert::ExpectException<std::exception>(backFooVectorException);

			Vector <Foo> fooVector;
			Foo bar(0), car(1), dar(2);
			fooVector.PushBack(bar);
			fooVector.PushBack(car);
			fooVector.PushBack(dar);
			Assert::IsTrue(fooVector.Front() == bar);
			Assert::IsTrue(fooVector.Back() == dar);

			Vector <Foo> const constFooVector = { bar, car, dar };
			Assert::IsTrue(constFooVector.Front() == *(constFooVector.cbegin()));
			Assert::IsTrue(constFooVector.Back() == *(--(constFooVector.cend())));
		}
		
		TEST_METHOD(TestPushBack)
		{
			Vector <Foo> fooVector;
			Foo bar(0), car(1), dar(2);

			Assert::IsTrue(fooVector.Size() == size_t(0));
			fooVector.PushBack(bar);
			Assert::IsTrue(fooVector.Front().Data() == bar.Data());
			Assert::IsTrue(fooVector.Back().Data() == bar.Data());
			Assert::IsTrue(fooVector.Size() == size_t(1));
			fooVector.PushBack(car);
			Assert::IsTrue(fooVector.Front().Data() == bar.Data());
			Assert::IsTrue(fooVector.Back().Data() == car.Data());
			Assert::IsTrue(fooVector.Size() == size_t(2));
			fooVector.PushBack(dar);
			Assert::IsTrue(fooVector.Front().Data() == bar.Data());
			Assert::IsTrue(fooVector.Back().Data() == dar.Data());
			Assert::IsTrue(fooVector.Size() == size_t(3));
		}
		
		TEST_METHOD(TestPopBack)
		{
			Vector <Foo> fooVector;
			Foo bar(0), car(1), dar(2);
			fooVector.PushBack(bar);
			fooVector.PushBack(car);
			fooVector.PushBack(dar);

			Assert::IsTrue((*fooVector.PopBack()).Data() == car.Data());
			Assert::IsTrue((*fooVector.PopBack()).Data() == bar.Data());
			Assert::IsTrue(fooVector.PopBack() == fooVector.begin());

			Assert::IsTrue(fooVector.IsEmpty());

			auto popBackFooVectorException = [&fooVector] { fooVector.PopBack(); };
			Assert::ExpectException<std::exception>(popBackFooVectorException);
		}		

		TEST_METHOD(TestEquivalenceOperators)
		{
			Vector <Foo> fooVectorABC, fooVectorDEF, fooVectorGHI;

			Assert::IsTrue(fooVectorABC == fooVectorDEF);
			Assert::IsTrue(fooVectorABC == fooVectorGHI);
			Assert::IsTrue(fooVectorDEF == fooVectorGHI);

			Foo a = 0, b = 1, c = 2, d = 0, e = 1, f = 2, g = 3, h = 4, i = 5;

			fooVectorABC.PushBack(a);
			fooVectorABC.PushBack(b);
			fooVectorABC.PushBack(c);

			fooVectorDEF.PushBack(d);
			fooVectorDEF.PushBack(e);
			fooVectorDEF.PushBack(f);

			fooVectorGHI.PushBack(g);
			fooVectorGHI.PushBack(h);
			fooVectorGHI.PushBack(i);

			Assert::IsTrue(fooVectorABC == fooVectorDEF);
			Assert::IsTrue(fooVectorABC != fooVectorGHI);
			Assert::IsTrue(fooVectorDEF != fooVectorGHI);
		}
		
		TEST_METHOD(TestCopyConstructorAndAssignmentOperator)
		{
			Vector <Foo> fooVector1;
			Foo bar(0), car(1), dar(2);

			fooVector1.PushBack(bar);
			fooVector1.PushBack(car);
			fooVector1.PushBack(dar);

			Vector<Foo>fooVector2(fooVector1);

			Assert::IsTrue(fooVector1 == fooVector2);

			Assert::IsTrue(fooVector2.Size() == size_t(3));
			Assert::IsTrue(*fooVector2.PopBack() == car);
			Assert::IsTrue(fooVector1 != fooVector2);
			Assert::IsTrue(fooVector2.Size() == size_t(2));
			Assert::IsTrue(*fooVector2.PopBack() == bar);
			Assert::IsTrue(fooVector1 != fooVector2);
			Assert::IsTrue(fooVector2.Size() == size_t(1));
			Assert::IsTrue(fooVector2.PopBack() == fooVector2.begin());
			Assert::IsTrue(fooVector1 != fooVector2);
			Assert::IsTrue(fooVector2.Size() == size_t(0));

			fooVector2 = fooVector1;

			Assert::IsTrue(fooVector1 == fooVector2);

			Assert::IsTrue(fooVector1.Back() == fooVector2.Back());

			fooVector2.PopBack();
			Assert::IsTrue(fooVector1.Back() != fooVector2.Back());

			fooVector1.PopBack();
			Assert::IsTrue(fooVector1.Back() == fooVector2.Back());

			fooVector2.PopBack();
			Assert::IsTrue(fooVector1.Back() != fooVector2.Back());

			fooVector1.PopBack();
			Assert::IsTrue(fooVector1.Back() == fooVector2.Back());

			fooVector2.PopBack();
			Assert::IsTrue(fooVector1.Size() != fooVector2.Size());

			fooVector1.PopBack();
			Assert::IsTrue(fooVector1.Size() == fooVector2.Size());
		}
		
		TEST_METHOD(TestFind)
		{
			Foo bar(0), car(1), dar(2), ear(3), far(4), gar(5), har(6), iar(7);
			Vector <Foo> fooVector = { bar, car, dar, ear, far, gar, har };

			Assert::IsTrue(*fooVector.Find(far) == far);
			Assert::IsTrue(fooVector.Find(iar) == fooVector.end());
		}

		TEST_METHOD(TestRemove)
		{
			Foo bar(0), car(1), dar(2), ear(3), far(4), gar(5);
			Vector <Foo> fooVector = { bar,car,dar,ear,far};

			Assert::IsTrue(fooVector.Size() == 5);
			Assert::IsTrue(fooVector.Find(gar) == fooVector.end());
			fooVector.Remove(gar);
			Assert::IsTrue(fooVector.Find(gar) == fooVector.end());
			Assert::IsTrue(fooVector.Size() == 5);
			Assert::IsTrue(fooVector.Find(ear) != fooVector.end());
			fooVector.Remove(ear);
			Assert::IsTrue(fooVector.Find(ear) == fooVector.end());
			Assert::IsTrue(fooVector.Size() == 4);
			Assert::IsTrue(fooVector.Find(far) != fooVector.end());
			fooVector.Remove(far);
			Assert::IsTrue(fooVector.Find(far) == fooVector.end());
			Assert::IsTrue(fooVector.Size() == 3);
			Assert::IsTrue(fooVector.Find(bar) != fooVector.end());
			fooVector.Remove(bar);
			Assert::IsTrue(fooVector.Find(bar) == fooVector.end());
			Assert::IsTrue(fooVector.Size() == 2);
			Assert::IsTrue(fooVector.Find(car) != fooVector.end());
			fooVector.Remove(car);
			Assert::IsTrue(fooVector.Find(car) == fooVector.end());
			Assert::IsTrue(fooVector.Size() == 1);
			Assert::IsTrue(fooVector.Find(dar) != fooVector.end());
			fooVector.Remove(dar);
			Assert::IsTrue(fooVector.Find(dar) == fooVector.end());
			Assert::IsTrue(fooVector.Size() == 0);

			Vector <Foo> foo2Vector = { bar,car,dar,ear,far };
			Assert::IsTrue(foo2Vector.Size() == 5);
			foo2Vector.Remove(++(foo2Vector.begin()), --(--(foo2Vector.end())));
			Assert::IsTrue(foo2Vector.Size() == 2);
			Assert::IsTrue(foo2Vector.Front() == bar);
			Assert::IsTrue(foo2Vector.Back() == far);
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState VectorTest::sStartMemState;
}