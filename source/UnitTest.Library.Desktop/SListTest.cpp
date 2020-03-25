#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "SList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FIEAGameEngine;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
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
			SList <int> intList;
			SList <int*> intPtrList;
			SList <Foo> fooList;
		}
		TEST_METHOD(TestInitializerListConstructor)
		{
			int a = 0, b = 1, c = 2;
			SList <int> intList = { a,b,c };

			Assert::AreEqual(intList.Size(), size_t(3));
			Assert::IsTrue(*(intList.PopFront()) == b);
			Assert::IsTrue(*(intList.PopFront()) == c);
			Assert::IsTrue(intList.PopFront() == intList.end());
			Assert::IsTrue(intList.isEmpty());
			
			SList <int*> intPtrList = { &a,&b,&c };

			Assert::AreEqual(intPtrList.Size(), size_t(3));
			Assert::IsTrue(*(intPtrList.PopFront()) == &b);
			Assert::IsTrue(*(intPtrList.PopFront()) == &c);
			Assert::IsTrue(intPtrList.PopFront() == intPtrList.end());
			Assert::IsTrue(intPtrList.isEmpty());

			Foo bar, car(1), dar(2);
			SList <Foo> fooList = { bar, car, dar };

			Assert::AreEqual(fooList.Size(), size_t(3));
			Assert::IsTrue(*(fooList.PopFront()) == car);
			Assert::IsTrue(*(fooList.PopFront()) == dar);
			Assert::IsTrue(fooList.PopFront() == fooList.end());
			Assert::IsTrue(fooList.isEmpty());
		}
		TEST_METHOD(TestFrontExceptionThrowsAndBackExceptionThrows)
		{
			SList <int> intList;
			
			Assert::IsTrue(intList.isEmpty());

			auto frontIntListException = [&intList] { intList.Front(); };
			Assert::ExpectException<std::exception>(frontIntListException);

			auto backIntListException = [&intList] { intList.Back(); };
			Assert::ExpectException<std::exception>(backIntListException);


			SList <int*> intPtrList;

			Assert::IsTrue(intPtrList.isEmpty());

			auto frontIntPtrListException = [&intPtrList] { intPtrList.Front(); };
			Assert::ExpectException<std::exception>(frontIntPtrListException);

			auto backIntPtrListException = [&intPtrList] { intPtrList.Back(); };
			Assert::ExpectException<std::exception>(backIntPtrListException);

			SList <Foo> fooList;

			Assert::IsTrue(fooList.isEmpty());

			auto frontFooListException = [&fooList] { fooList.Front(); };
			Assert::ExpectException<std::exception>(frontFooListException);

			auto backFooListException = [&fooList] { fooList.Back(); };
			Assert::ExpectException<std::exception>(backFooListException);
		}

		TEST_METHOD(TestPushFront)
		{
			SList <int> intList;
			int a = 0, b = 1, c = 2;
			Assert::AreEqual(intList.Size(), size_t(0));
			intList.PushFront(a);
			Assert::AreEqual(intList.Front(), a);
			Assert::AreEqual(intList.Back(), a);
			Assert::AreEqual(intList.Size(), size_t(1));
			intList.PushFront(b);
			Assert::AreEqual(intList.Front(), b);
			Assert::AreEqual(intList.Back(), a);
			Assert::AreEqual(intList.Size(), size_t(2));
			intList.PushFront(c);
			Assert::AreEqual(intList.Front(), c);
			Assert::AreEqual(intList.Back(), a);
			Assert::AreEqual(intList.Size(), size_t(3));


			SList <int*> intPtrList;

			Assert::AreEqual(intPtrList.Size(), size_t(0));
			intPtrList.PushFront(&a);
			Assert::AreEqual(intPtrList.Front(), &a);
			Assert::AreEqual(intPtrList.Back(), &a);
			Assert::AreEqual(intPtrList.Size(), size_t(1));
			intPtrList.PushFront(&b);
			Assert::AreEqual(intPtrList.Front(), &b);
			Assert::AreEqual(intPtrList.Back(), &a);
			Assert::AreEqual(intPtrList.Size(), size_t(2));
			intPtrList.PushFront(&c);
			Assert::AreEqual(intPtrList.Front(), &c);
			Assert::AreEqual(intPtrList.Back(), &a);
			Assert::AreEqual(intPtrList.Size(), size_t(3));

			SList <Foo> fooList;
			Foo bar, car(1), dar(2);

			Assert::AreEqual(fooList.Size(), size_t(0));
			fooList.PushFront(bar);
			Assert::AreEqual(fooList.Front().Data(), bar.Data());
			Assert::AreEqual(fooList.Back().Data(), bar.Data());
			Assert::AreEqual(fooList.Size(), size_t(1));
			fooList.PushFront(car);
			Assert::AreEqual(fooList.Front().Data(), car.Data());
			Assert::AreEqual(fooList.Back().Data(), bar.Data());
			Assert::AreEqual(fooList.Size(), size_t(2));
			fooList.PushFront(dar);
			Assert::AreEqual(fooList.Front().Data(), dar.Data());
			Assert::AreEqual(fooList.Back().Data(), bar.Data());
			Assert::AreEqual(fooList.Size(), size_t(3));
		}
		TEST_METHOD(TestPushBack)
		{
			SList <int> intList;
			int a = 0, b = 1, c = 2;

			Assert::AreEqual(intList.Size(), size_t(0));
			intList.PushBack(a);
			Assert::AreEqual(intList.Front(), a);
			Assert::AreEqual(intList.Back(), a);
			Assert::AreEqual(intList.Size(), size_t(1));
			intList.PushBack(b);
			Assert::AreEqual(intList.Front(), a);
			Assert::AreEqual(intList.Back(), b);
			Assert::AreEqual(intList.Size(), size_t(2));
			intList.PushBack(c);
			Assert::AreEqual(intList.Front(), a);
			Assert::AreEqual(intList.Back(), c);
			Assert::AreEqual(intList.Size(), size_t(3));


			SList <int*> intPtrList;

			Assert::AreEqual(intPtrList.Size(), size_t(0));
			intPtrList.PushBack(&a);
			Assert::AreEqual(intPtrList.Front(), &a);
			Assert::AreEqual(intPtrList.Back(), &a);
			Assert::AreEqual(intPtrList.Size(), size_t(1));
			intPtrList.PushBack(&b);
			Assert::AreEqual(intPtrList.Front(), &a);
			Assert::AreEqual(intPtrList.Back(), &b);
			Assert::AreEqual(intPtrList.Size(), size_t(2));
			intPtrList.PushBack(&c);
			Assert::AreEqual(intPtrList.Front(), &a);
			Assert::AreEqual(intPtrList.Back(), &c);
			Assert::AreEqual(intPtrList.Size(), size_t(3));

			SList <Foo> fooList;
			Foo bar, car(1), dar(2);

			Assert::AreEqual(fooList.Size(), size_t(0));
			fooList.PushBack(bar);
			Assert::AreEqual(fooList.Front().Data(), bar.Data());
			Assert::AreEqual(fooList.Back().Data(), bar.Data());
			Assert::AreEqual(fooList.Size(), size_t(1));
			fooList.PushBack(car);
			Assert::AreEqual(fooList.Front().Data(), bar.Data());
			Assert::AreEqual(fooList.Back().Data(), car.Data());
			Assert::AreEqual(fooList.Size(), size_t(2));
			fooList.PushBack(dar);
			Assert::AreEqual(fooList.Front().Data(), bar.Data());
			Assert::AreEqual(fooList.Back().Data(), dar.Data());
			Assert::AreEqual(fooList.Size(), size_t(3));
		}
		TEST_METHOD(TestPopFront)
		{
			SList <int> intList;
			int a = 0, b = 1, c = 2;

			intList.PushFront(a);
			intList.PushFront(b);
			intList.PushBack(c);

			Assert::IsTrue(*(intList.PopFront()) == a);
			Assert::IsTrue(*(intList.PopFront()) == c);
			Assert::IsTrue(intList.PopFront() == intList.end());

			Assert::IsTrue(intList.isEmpty());

			auto popFrontIntListException = [&intList] { intList.PopFront(); };
			Assert::ExpectException<std::exception>(popFrontIntListException);

			SList <int*> intPtrList;
			intPtrList.PushFront(&a);
			intPtrList.PushFront(&b);
			intPtrList.PushBack(&c);

			Assert::IsTrue(*(intPtrList.PopFront()) == &a);
			Assert::IsTrue(*(intPtrList.PopFront()) == &c);
			Assert::IsTrue(intPtrList.PopFront() == intPtrList.end());

			Assert::IsTrue(intPtrList.isEmpty());

			auto popFrontIntPtrListException = [&intPtrList] { intPtrList.PopFront(); };
			Assert::ExpectException<std::exception>(popFrontIntPtrListException);

			SList <Foo> fooList;
			Foo bar, car(1), dar(2);
			fooList.PushFront(bar);
			fooList.PushFront(car);
			fooList.PushBack(dar);

			Assert::IsTrue((*fooList.PopFront()).Data() == bar.Data());
			Assert::IsTrue((*fooList.PopFront()).Data() == dar.Data());
			Assert::IsTrue(fooList.PopFront() == fooList.end());

			Assert::IsTrue(fooList.isEmpty());

			auto popFrontFooListException = [&fooList] { fooList.PopFront(); };
			Assert::ExpectException<std::exception>(popFrontFooListException);
		}

		TEST_METHOD(TestPopBack)
		{
			SList <int> intList;
			int a = 0, b = 1, c = 2;

			intList.PushFront(a);
			intList.PushFront(b);
			intList.PushBack(c);

			Assert::IsTrue(*intList.PopBack() == a);
			Assert::IsTrue(*intList.PopBack() == b);
			Assert::IsTrue(intList.PopBack() == intList.end());

			Assert::IsTrue(intList.isEmpty());

			auto popBackIntListException = [&intList] { intList.PopBack(); };
			Assert::ExpectException<std::exception>(popBackIntListException);

			SList <int*> intPtrList;
			intPtrList.PushFront(&a);
			intPtrList.PushFront(&b);
			intPtrList.PushBack(&c);

			Assert::IsTrue(*intPtrList.PopBack() == &a);
			Assert::IsTrue(*intPtrList.PopBack() == &b);
			Assert::IsTrue(intPtrList.PopBack() == intPtrList.end());

			Assert::IsTrue(intPtrList.isEmpty());

			auto popBackIntPtrListException = [&intPtrList] { intPtrList.PopBack(); };
			Assert::ExpectException<std::exception>(popBackIntPtrListException);

			SList <Foo> fooList;
			Foo bar, car(1), dar(2);
			fooList.PushFront(bar);
			fooList.PushFront(car);
			fooList.PushBack(dar);

			Assert::IsTrue((*fooList.PopBack()).Data() == bar.Data());
			Assert::IsTrue((*fooList.PopBack()).Data() == car.Data());
			Assert::IsTrue(fooList.PopBack() == fooList.end());

			Assert::IsTrue(fooList.isEmpty());

			auto popBackFooListException = [&fooList] { fooList.PopBack(); };
			Assert::ExpectException<std::exception>(popBackFooListException);
		}
		TEST_METHOD(TestClear)
		{
			SList <int> intList;
			int a = 0, b = 1, c = 2;

			intList.PushFront(a);
			intList.PushFront(b);
			intList.PushBack(c);
			
			intList.Clear();

			Assert::IsTrue(intList.isEmpty());

			SList <int*> intPtrList;
			intPtrList.PushFront(&a);
			intPtrList.PushFront(&b);
			intPtrList.PushBack(&c);

			intPtrList.Clear();

			Assert::IsTrue(intPtrList.isEmpty());

			SList <Foo> fooList;
			Foo bar, car(1), dar(2);
			fooList.PushFront(bar);
			fooList.PushFront(car);
			fooList.PushBack(dar);

			fooList.Clear();

			Assert::IsTrue(fooList.isEmpty());
		}
		TEST_METHOD(TestEquivalenceOperators)
		{
			SList <int> intListABC, intListDEF, intListGHI;

			Assert::IsTrue(intListABC == intListDEF);
			Assert::IsTrue(intListABC == intListGHI);
			Assert::IsTrue(intListDEF == intListGHI);

			int a = 0, b = 1, c = 2, d = 0, e = 1, f = 2, g = 3, h = 4, i = 5;

			intListABC.PushFront(a);
			intListABC.PushFront(b);
			intListABC.PushBack(c);

			intListDEF.PushFront(d);
			intListDEF.PushFront(e);
			intListDEF.PushBack(f);

			intListGHI.PushFront(g);
			intListGHI.PushFront(h);
			intListGHI.PushBack(i);

			Assert::IsTrue(intListABC == intListDEF);
			Assert::IsTrue(intListABC != intListGHI);
			Assert::IsTrue(intListDEF != intListGHI);
		}
		TEST_METHOD(TestCopyConstructorAndMoveAssignmentOperator)
		{
			SList <int> intList1;
			int a = 0, b = 1, c = 2;

			intList1.PushFront(a);
			intList1.PushFront(b);
			intList1.PushBack(c);

			SList<int>intList2(intList1);

			Assert::IsTrue(intList1 == intList2);

			Assert::AreEqual(intList2.Size(), size_t(3));
			Assert::IsTrue(*intList2.PopBack() == a);
			Assert::IsTrue(intList1 != intList2);
			Assert::AreEqual(intList2.Size(), size_t(2));
			Assert::IsTrue(*intList2.PopBack() == b);
			Assert::IsTrue(intList1 != intList2);
			Assert::AreEqual(intList2.Size(), size_t(1));
			Assert::IsTrue(intList2.PopBack() == intList2.end());
			Assert::IsTrue(intList1 != intList2);
			Assert::AreEqual(intList2.Size(), size_t(0));

			intList2 = intList1;

			Assert::IsTrue(intList1 == intList2);

			Assert::AreEqual(intList1.Front(), intList2.Front());

			intList2.PopFront();
			Assert::AreNotEqual(intList1.Front(), intList2.Front());

			intList1.PopFront();
			Assert::AreEqual(intList1.Front(), intList2.Front());

			intList2.PopFront();
			Assert::AreNotEqual(intList1.Front(), intList2.Front());

			intList1.PopFront();
			Assert::AreEqual(intList1.Front(), intList2.Front());

			intList2.PopFront();
			Assert::AreNotEqual(intList1.Size(), intList2.Size());

			intList1.PopFront();
			Assert::AreEqual(intList1.Size(), intList2.Size());

			SList <int*> intPtrList1;

			intPtrList1.PushFront(&a);
			intPtrList1.PushFront(&b);
			intPtrList1.PushBack(&c);

			SList<int*>intPtrList2(intPtrList1);

			Assert::IsTrue(intPtrList1 == intPtrList2);

			Assert::AreEqual(intPtrList2.Size(), size_t(3));
			Assert::IsTrue(*intPtrList2.PopBack() == &a);
			Assert::IsTrue(intPtrList1 != intPtrList2);
			Assert::AreEqual(intPtrList2.Size(), size_t(2));
			Assert::IsTrue(*intPtrList2.PopBack() == &b);
			Assert::IsTrue(intPtrList1 != intPtrList2);
			Assert::AreEqual(intPtrList2.Size(), size_t(1));
			Assert::IsTrue(intPtrList2.PopBack() == intPtrList2.end());
			Assert::IsTrue(intPtrList1 != intPtrList2);
			Assert::AreEqual(intPtrList2.Size(), size_t(0));

			intPtrList2 = intPtrList1;

			Assert::IsTrue(intPtrList1 == intPtrList2);

			Assert::AreEqual(intPtrList1.Front(), intPtrList2.Front());

			intPtrList2.PopFront();
			Assert::AreNotEqual(intPtrList1.Front(), intPtrList2.Front());

			intPtrList1.PopFront();
			Assert::AreEqual(intPtrList1.Front(), intPtrList2.Front());

			intPtrList2.PopFront();
			Assert::AreNotEqual(intPtrList1.Front(), intPtrList2.Front());

			intPtrList1.PopFront();
			Assert::AreEqual(intPtrList1.Front(), intPtrList2.Front());

			intPtrList2.PopFront();
			Assert::AreNotEqual(intPtrList1.Size(), intPtrList2.Size());

			intPtrList1.PopFront();
			Assert::AreEqual(intPtrList1.Size(), intPtrList2.Size());

			SList <Foo> fooList1;
			Foo bar, car(1), dar(2);

			fooList1.PushFront(bar);
			fooList1.PushFront(car);
			fooList1.PushBack(dar);

			SList<Foo>fooList2(fooList1);

			Assert::IsTrue(fooList1 == fooList2);

			Assert::IsTrue(fooList2.Size() == size_t(3));
			Assert::IsTrue(*fooList2.PopBack() == bar);
			Assert::IsTrue(fooList1 != fooList2);
			Assert::IsTrue(fooList2.Size() == size_t(2));
			Assert::IsTrue(*fooList2.PopBack() == car);
			Assert::IsTrue(fooList1 != fooList2);
			Assert::IsTrue(fooList2.Size() == size_t(1));
			Assert::IsTrue(fooList2.PopBack() == fooList2.end());
			Assert::IsTrue(fooList1 != fooList2);
			Assert::IsTrue(fooList2.Size() == size_t(0));

			fooList2 = fooList1;

			Assert::IsTrue(fooList1 == fooList2);

			Assert::IsTrue(fooList1.Front() == fooList2.Front());

			fooList2.PopFront();
			Assert::IsTrue(fooList1.Front() != fooList2.Front());

			fooList1.PopFront();
			Assert::IsTrue(fooList1.Front() == fooList2.Front());

			fooList2.PopFront();
			Assert::IsTrue(fooList1.Front() != fooList2.Front());

			fooList1.PopFront();
			Assert::IsTrue(fooList1.Front() == fooList2.Front());

			fooList2.PopFront();
			Assert::IsTrue(fooList1.Size() != fooList2.Size());

			fooList1.PopFront();
			Assert::IsTrue(fooList1.Size() == fooList2.Size());
		}

		TEST_METHOD(TestFind)
		{
			int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
			SList <int> intList = { a,b,c,d,e,f,g };

			Assert::IsTrue(*intList.Find(e) == e);
			Assert::IsTrue(intList.Find(7) == intList.end());

			SList <int*> intPtrList = { &a,&b,&c,&d,&e,&f,&g };

			Assert::IsTrue(*intPtrList.Find(&e) == &e);
			Assert::IsTrue(intPtrList.Find(&h) == intPtrList.end());

			Foo bar, car(1), dar(2), ear(3), far(4), gar(5), har(6), iar(7);
			SList <Foo> fooList = { bar, car, dar, ear, far, gar, har };

			Assert::IsTrue(*fooList.Find(far) == far);
			Assert::IsTrue(fooList.Find(iar) == fooList.end());
		}

		TEST_METHOD(TestRemove)
		{
			int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
			SList <int> intList = { a,b,c,d,e,f,g };

			Assert::IsTrue(intList.Size() == 7);
			intList.Remove(h);
			Assert::IsTrue(intList.Size() == 7);
			intList.Remove(g);
			Assert::IsTrue(intList.Size() == 6);
			intList.Remove(d);
			Assert::IsTrue(intList.Size() == 5);
			intList.Remove(a);
			Assert::IsTrue(intList.Size() == 4);
			Assert::IsTrue(intList.Front() == b);
			intList.Remove(++intList.begin());
			Assert::IsTrue(intList.Size() == 3);
			Assert::IsTrue(intList.Front() == b);

			SList <int*> intPtrList = { &a,&b,&c,&d,&e,&f,&g };
			Assert::IsTrue(intPtrList.Size() == 7);
			intPtrList.Remove(&h);
			Assert::IsTrue(intPtrList.Size() == 7);
			intPtrList.Remove(&g);
			Assert::IsTrue(intPtrList.Size() == 6);
			intPtrList.Remove(&d);
			Assert::IsTrue(intPtrList.Size() == 5);
			intPtrList.Remove(&a);
			Assert::IsTrue(intPtrList.Size() == 4);
			Assert::IsTrue(intPtrList.Front() == &b);
			intPtrList.Remove(++intPtrList.begin());
			Assert::IsTrue(intPtrList.Size() == 3);
			Assert::IsTrue(intPtrList.Front() == &b);

			Foo bar, car(1), dar(2), ear(3), far(4), gar(5), har(6), iar(7);
			SList <Foo> fooList = { bar, car, dar, ear, far, gar, har };

			Assert::IsTrue(fooList.Size() == 7);
			fooList.Remove(iar);
			Assert::IsTrue(fooList.Size() == 7);
			fooList.Remove(har);
			Assert::IsTrue(fooList.Size() == 6);
			fooList.Remove(ear);
			Assert::IsTrue(fooList.Size() == 5);
			fooList.Remove(bar);
			Assert::IsTrue(fooList.Size() == 4);
			Assert::IsTrue(fooList.Front() == car);
			fooList.Remove(++fooList.begin());
			Assert::IsTrue(fooList.Size() == 3);
			Assert::IsTrue(fooList.Front() == car);
		}

		TEST_METHOD(TestInsertAfter)
		{
			int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7;
			SList <int> intList = { a,b,c,d,e,f,g };

			Assert::IsTrue(intList.Size() == 7);
			intList.InsertAfter(intList.end(), h);
			Assert::IsTrue(intList.Size() == 8);
			intList.Remove(h);
			Assert::IsTrue(intList.Size() == 7);
			intList.InsertAfter(++(++(intList.begin())), h);
			Assert::IsTrue(intList.Size() == 8);
			Assert::IsTrue(intList.Find(h) == ++(++(++(intList.begin()))));


			SList <int*> intPtrList = { &a,&b,&c,&d,&e,&f,&g };
			
			Assert::IsTrue(intPtrList.Size() == 7);
			intPtrList.InsertAfter(intPtrList.end(), &h);
			Assert::IsTrue(intPtrList.Size() == 8);
			intPtrList.Remove(&h);
			Assert::IsTrue(intPtrList.Size() == 7);
			intPtrList.InsertAfter(++(++(intPtrList.begin())), &h);
			Assert::IsTrue(intPtrList.Size() == 8);
			Assert::IsTrue(intPtrList.Find(&h) == (++(++(++(intPtrList.begin())))));

			Foo bar, car(1), dar(2), ear(3), far(4), gar(5), har(6), iar(7);
			SList <Foo> fooList = { bar, car, dar, ear, far, gar, har };

			Assert::IsTrue(fooList.Size() == 7);
			fooList.InsertAfter(fooList.end(), iar);
			Assert::IsTrue(fooList.Size() == 8);
			fooList.Remove(iar);
			Assert::IsTrue(fooList.Size() == 7);
			fooList.InsertAfter(++(++(fooList.begin())), iar);
			Assert::IsTrue(fooList.Size() == 8);
			Assert::IsTrue(fooList.Find(iar) == (++(++(++(fooList.begin())))));
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState SListTest::sStartMemState;
}