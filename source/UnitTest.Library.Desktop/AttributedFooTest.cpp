#pragma once

#include "pch.h"

#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "Bar.h"
#include "TypeManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;

namespace UnitTestLibraryDesktop
{
	
	TEST_CLASS(AttributedFooTest)
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

		TEST_METHOD(PaulRTTITest)
		{
			
			AttributedFoo a;
			RTTI* rtti = &a;

			Assert::IsFalse(rtti->Is("Bar"));
			Assert::IsTrue(rtti->Is("AttributedFoo"));
			Assert::IsFalse(rtti->Is(Bar::TypeIdClass()));
			Assert::IsTrue(rtti->Is(AttributedFoo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::IsTrue(AttributedFoo::TypeIdClass() == rtti->TypeIdInstance());

			Bar* b = rtti->As<Bar>();
			Assert::IsNull(b);

			AttributedFoo * f = rtti->As<AttributedFoo>();
			Assert::IsNotNull(f);
			Assert::IsTrue(&a == f);
			RTTI* r = rtti->QueryInterface(Bar::TypeIdClass());
			Assert::IsNull(r);

			r = rtti->QueryInterface(AttributedFoo::TypeIdClass());
			Assert::IsNotNull(r);

			AttributedFoo otherFoo;
			//Assert::IsTrue(rtti->Equals(&otherFoo));

			Bar otherBar(10);
			Assert::IsFalse(rtti->Equals(&otherBar));

			Assert::IsTrue("AttributedFoo"s == r->ToString());
		}

		TEST_METHOD(PaulAttributesTest)
		{
			AttributedFoo foo;
			Assert::IsTrue(foo.IsAttribute("this"));
			Assert::IsTrue(foo.IsAttribute("ExternalInteger"));
			Assert::IsTrue(foo.IsAttribute("ExternalFloat"));
			Assert::IsTrue(foo.IsAttribute("ExternalString"));
			Assert::IsTrue(foo.IsAttribute("ExternalVector"));
			Assert::IsTrue(foo.IsAttribute("ExternalMatrix"));

			Assert::IsTrue(foo.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo.IsAttribute("ExternalMatrixArray"));

			Assert::IsTrue(foo.IsAttribute("NestedScope"));
			Assert::IsTrue(foo.IsAttribute("NestedScopeArray"));

			Assert::IsTrue(foo.IsPrescribedAttribute("this"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalMatrix"));

			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(foo.IsPrescribedAttribute("ExternalMatrixArray"));

			Assert::IsTrue(foo.IsPrescribedAttribute("NestedScope"));
			Assert::IsTrue(foo.IsPrescribedAttribute("NestedScopeArray"));

			Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalInteger"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalFloat"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalString"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalVector"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalMatrix"));

			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalStringArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("ExternalMatrixArray"));

			Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScope"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("NestedScopeArray"));
		}
		TEST_METHOD(PaulAppendAuxiliaryAttributeTest)
		{
			AttributedFoo foo;

			foo.AppendAuxiliaryAttribute("AuxiliaryInteger");
			Assert::IsTrue(foo.IsAttribute("AuxiliaryInteger"));
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryInteger"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryInteger"));

			Datum d1;
			foo.AppendAuxiliaryAttribute("AuxiliaryIntegerWithDatum", d1);
			Assert::IsTrue(foo.IsAttribute("AuxiliaryIntegerWithDatum"));
			Assert::IsTrue(foo.IsAuxiliaryAttribute("AuxiliaryIntegerWithDatum"));
			Assert::IsFalse(foo.IsPrescribedAttribute("AuxiliaryIntegerWithDatum"));

			Assert::ExpectException<std::exception>([&foo] {foo.AppendAuxiliaryAttribute("ExternalInteger"); });
		}

		TEST_METHOD(PaulExternalAssignmentTest)
		{
			AttributedFoo foo;

			Datum* datum = foo.Find("ExternalInteger");
			Assert::IsTrue(1 == datum->Size());

			int a = 5;
			datum->Set(a);
			Assert::IsTrue(a == datum->Get<int>());
			Assert::IsTrue(a == foo.ExternalInteger);

			float b = 6.0f;
			foo["ExternalFloat"] = b;
			Assert::IsTrue(b == foo.ExternalFloat);
		}

		TEST_METHOD(PaulCopyConstructorTest)
		{
			AttributedFoo foo;
			AttributedFoo anotherAttributedFoo = foo;

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("this"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrix"));

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrixArray"));

			Assert::IsTrue(&anotherAttributedFoo == anotherAttributedFoo["this"].Get<RTTI*>()->As<AttributedFoo>());


		}

		TEST_METHOD(PaulCopyAssignmentTest)
		{
			AttributedFoo foo;
			AttributedFoo anotherAttributedFoo;
			anotherAttributedFoo = foo;

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("this"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrix"));

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrixArray"));

			Assert::IsTrue(&anotherAttributedFoo == anotherAttributedFoo["this"].Get<RTTI*>()->As<AttributedFoo>());

		}
		TEST_METHOD(PaulAttributedClearTest)
		{
			AttributedFoo foo;
			size_t originalSize = foo.Size();
			foo.AppendAuxiliaryAttribute("AuxiliaryInteger");
			Assert::AreEqual(originalSize + 1, foo.Size());
			foo.Clear();
			Assert::AreEqual(originalSize, foo.Size());
		}
		TEST_METHOD(TestConstructor)
		{
			AttributedFoo a;
		}

		TEST_METHOD(TestAttributedMoveConstructor)
		{
			AttributedFoo foo;
			AttributedFoo anotherAttributedFoo = std::move(foo);

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("this"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrix"));

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrixArray"));

			Assert::IsTrue(&anotherAttributedFoo == anotherAttributedFoo["this"].Get<RTTI*>()->As<AttributedFoo>());

			Assert::IsTrue(anotherAttributedFoo.ExternalInteger == anotherAttributedFoo["ExternalInteger"].Get<int>());
			Assert::IsTrue(anotherAttributedFoo.ExternalFloat == anotherAttributedFoo["ExternalFloat"].Get<float>());
			Assert::IsTrue(anotherAttributedFoo.ExternalMatrix == anotherAttributedFoo["ExternalMatrix"].Get<mat4x4>());
			Assert::IsTrue(anotherAttributedFoo.ExternalVector == anotherAttributedFoo["ExternalVector"].Get<vec4>());
			Assert::IsTrue(anotherAttributedFoo.ExternalString == anotherAttributedFoo["ExternalString"].Get<string>());
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			AttributedFoo foo;
			AttributedFoo anotherAttributedFoo;
			anotherAttributedFoo = foo;

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("this"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrix"));

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrixArray"));

			Assert::IsTrue(&anotherAttributedFoo == anotherAttributedFoo["this"].Get<RTTI*>()->As<AttributedFoo>());

			Assert::IsTrue(anotherAttributedFoo.ExternalInteger == anotherAttributedFoo["ExternalInteger"].Get<int>());
			Assert::IsTrue(anotherAttributedFoo.ExternalFloat == anotherAttributedFoo["ExternalFloat"].Get<float>());
			Assert::IsTrue(anotherAttributedFoo.ExternalMatrix == anotherAttributedFoo["ExternalMatrix"].Get<mat4x4>());
			Assert::IsTrue(anotherAttributedFoo.ExternalVector == anotherAttributedFoo["ExternalVector"].Get<vec4>());
			Assert::IsTrue(anotherAttributedFoo.ExternalString == anotherAttributedFoo["ExternalString"].Get<string>());
		}

		TEST_METHOD(TestAttributedMoveAssignment)
		{
			AttributedFoo foo;
			AttributedFoo anotherAttributedFoo;
			anotherAttributedFoo = std::move(foo);

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("this"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrix"));

			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(anotherAttributedFoo.IsPrescribedAttribute("ExternalMatrixArray"));

			Assert::IsTrue(&anotherAttributedFoo == anotherAttributedFoo["this"].Get<RTTI*>()->As<AttributedFoo>());

			Assert::IsTrue(anotherAttributedFoo.ExternalInteger == anotherAttributedFoo["ExternalInteger"].Get<int>());
			Assert::IsTrue(anotherAttributedFoo.ExternalFloat == anotherAttributedFoo["ExternalFloat"].Get<float>());
			Assert::IsTrue(anotherAttributedFoo.ExternalMatrix == anotherAttributedFoo["ExternalMatrix"].Get<mat4x4>());
			Assert::IsTrue(anotherAttributedFoo.ExternalVector == anotherAttributedFoo["ExternalVector"].Get<vec4>());
			Assert::IsTrue(anotherAttributedFoo.ExternalString == anotherAttributedFoo["ExternalString"].Get<string>());

		}

		TEST_METHOD(TestIsAttribute)
		{
			AttributedFoo a;

			a.AppendAuxiliaryAttribute("Auxiliary1");
			a.AppendAuxiliaryAttribute("Auxiliary2");
			a.AppendAuxiliaryAttribute("Auxiliary3");
			a.AppendAuxiliaryAttribute("Auxiliary4");
			a.AppendAuxiliaryAttribute("Auxiliary5");

			Vector<Scope::PairType*> attributes(a.Attributes());

			Vector<string> names{ "this", "ExternalInteger", "ExternalFloat", "ExternalString", "ExternalVector", "ExternalMatrix", "ExternalIntegerArray", "ExternalFloatArray", "ExternalStringArray", "ExternalVectorArray", "ExternalMatrixArray", "NestedScope", "NestedScopeArray", "Auxiliary1", "Auxiliary2", "Auxiliary3", "Auxiliary4", "Auxiliary5" };

			for (size_t i = 0; i < attributes.Size(); i++)
			{
				Assert::IsTrue(a.IsAttribute(names[i]));
			}
		}

		TEST_METHOD(TestIsPrescribedAttribute)
		{
			AttributedFoo a;

			a.AppendAuxiliaryAttribute("Auxiliary1");
			a.AppendAuxiliaryAttribute("Auxiliary2");
			a.AppendAuxiliaryAttribute("Auxiliary3");
			a.AppendAuxiliaryAttribute("Auxiliary4");
			a.AppendAuxiliaryAttribute("Auxiliary5");

			Vector<Scope::PairType*> attributes(a.Attributes());

			Vector<string> names{ "this", "ExternalInteger", "ExternalFloat", "ExternalString", "ExternalVector", "ExternalMatrix", "ExternalIntegerArray", "ExternalFloatArray", "ExternalStringArray", "ExternalVectorArray", "ExternalMatrixArray", "NestedScope", "NestedScopeArray", "Auxiliary1", "Auxiliary2", "Auxiliary3", "Auxiliary4", "Auxiliary5" };

			for (size_t i = 0; i < attributes.Size() - 5; i++)
			{
				Assert::IsTrue(a.IsPrescribedAttribute(names[i]));
			}
			for (size_t i = attributes.Size(); i < attributes.Size(); i++)
			{
				Assert::IsFalse(a.IsPrescribedAttribute(names[i]));
			}
		}

		TEST_METHOD(TestIsAuxiliaryAttribute)
		{
			AttributedFoo a;

			a.AppendAuxiliaryAttribute("Auxiliary1");
			a.AppendAuxiliaryAttribute("Auxiliary2");
			a.AppendAuxiliaryAttribute("Auxiliary3");
			a.AppendAuxiliaryAttribute("Auxiliary4");
			a.AppendAuxiliaryAttribute("Auxiliary5");

			Vector<Scope::PairType*> attributes(a.Attributes());

			Vector<string> names{ "this", "ExternalInteger", "ExternalFloat", "ExternalString", "ExternalVector", "ExternalMatrix", "ExternalIntegerArray", "ExternalFloatArray", "ExternalStringArray", "ExternalVectorArray", "ExternalMatrixArray", "NestedScope", "NestedScopeArray", "Auxiliary1", "Auxiliary2", "Auxiliary3", "Auxiliary4", "Auxiliary5" };

			for (size_t i = 0; i < attributes.Size() - 5; i++)
			{
				Assert::IsFalse(a.IsAuxiliaryAttribute(names[i]));
			}
			for (size_t i = attributes.Size() - 5; i < attributes.Size(); i++)
			{
				Assert::IsTrue(a.IsAuxiliaryAttribute(names[i]));
			}
		}

		TEST_METHOD(TestAttributes)
		{
			AttributedFoo a;

			a.AppendAuxiliaryAttribute("Auxiliary1");
			a.AppendAuxiliaryAttribute("Auxiliary2");
			a.AppendAuxiliaryAttribute("Auxiliary3");
			a.AppendAuxiliaryAttribute("Auxiliary4");
			a.AppendAuxiliaryAttribute("Auxiliary5");

			Vector<Scope::PairType*> attributes(a.Attributes());

			Vector<string> names{ "this", "ExternalInteger", "ExternalFloat", "ExternalString", "ExternalVector", "ExternalMatrix", "ExternalIntegerArray", "ExternalFloatArray", "ExternalStringArray", "ExternalVectorArray", "ExternalMatrixArray", "NestedScope", "NestedScopeArray", "Auxiliary1", "Auxiliary2", "Auxiliary3", "Auxiliary4", "Auxiliary5" };
			Vector<Datum::DatumType> types{ Datum::DatumType::RTTIPtr, Datum::DatumType::Integer, Datum::DatumType::Float, Datum::DatumType::String, Datum::DatumType::Vector4, Datum::DatumType::Matrix4x4, Datum::DatumType::Integer, Datum::DatumType::Float, Datum::DatumType::String, Datum::DatumType::Vector4, Datum::DatumType::Matrix4x4, Datum::DatumType::Scope,  Datum::DatumType::Scope, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown };



			for (size_t i = 0; i < attributes.Size(); i++)
			{
				Assert::IsTrue(attributes[i]->first == names[i]);
				Assert::IsTrue(attributes[i]->second.Type() == types[i]);
			}
		}

		TEST_METHOD(TestPrescribedAttributes)
		{
			AttributedFoo a;

			a.AppendAuxiliaryAttribute("Auxiliary1");
			a.AppendAuxiliaryAttribute("Auxiliary2");
			a.AppendAuxiliaryAttribute("Auxiliary3");
			a.AppendAuxiliaryAttribute("Auxiliary4");
			a.AppendAuxiliaryAttribute("Auxiliary5");

			Vector<Scope::PairType*> attributes(a.Attributes());

			Vector<string> names{ "this", "ExternalInteger", "ExternalFloat", "ExternalString", "ExternalVector", "ExternalMatrix", "ExternalIntegerArray", "ExternalFloatArray", "ExternalStringArray", "ExternalVectorArray", "ExternalMatrixArray", "NestedScope", "NestedScopeArray", "Auxiliary1", "Auxiliary2", "Auxiliary3", "Auxiliary4", "Auxiliary5" };
			Vector<Datum::DatumType> types{ Datum::DatumType::RTTIPtr, Datum::DatumType::Integer, Datum::DatumType::Float, Datum::DatumType::String, Datum::DatumType::Vector4, Datum::DatumType::Matrix4x4, Datum::DatumType::Integer, Datum::DatumType::Float, Datum::DatumType::String, Datum::DatumType::Vector4, Datum::DatumType::Matrix4x4, Datum::DatumType::Scope, Datum::DatumType::Scope, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown };

			Vector <Attributed::PairType*> prescribedAttributes = a.PrescribedAttributes();

			for (size_t i = 0; i < prescribedAttributes.Size(); i++)
			{
				Assert::IsTrue(a.IsPrescribedAttribute(prescribedAttributes[i]->first));
			}
			for (size_t i = prescribedAttributes.Size(); i < names.Size(); i++)
			{
				Assert::IsFalse(a.IsPrescribedAttribute(a.Attributes()[i]->first));
			}
		}

		TEST_METHOD(TestRepopulate)
		{
			AttributedFoo foo;
			size_t originalSize = foo.Size();
			foo.AppendAuxiliaryAttribute("AuxiliaryInteger");
			Assert::AreEqual(originalSize + 1, foo.Size());
			foo.Clear();

			Assert::AreEqual(originalSize, foo.Size());
		}

		TEST_METHOD(TestAppendAuxiliaryAttributesAndAuxiliaryAttributes)
		{
			AttributedFoo a;

			Assert::IsTrue(&(a.AppendAuxiliaryAttribute("Auxiliary1")) == &(a.AppendAuxiliaryAttribute("Auxiliary1")));
			Assert::IsTrue(&(a.AppendAuxiliaryAttribute("Auxiliary2")) == &(a.AppendAuxiliaryAttribute("Auxiliary2")));
			Assert::IsTrue(&(a.AppendAuxiliaryAttribute("Auxiliary3")) == &(a.AppendAuxiliaryAttribute("Auxiliary3")));
			Assert::IsTrue(&(a.AppendAuxiliaryAttribute("Auxiliary4")) == &(a.AppendAuxiliaryAttribute("Auxiliary4")));
			Assert::IsTrue(&(a.AppendAuxiliaryAttribute("Auxiliary5")) == &(a.AppendAuxiliaryAttribute("Auxiliary5")));

			Vector<Scope::PairType*> attributes(a.Attributes());

			Vector<string> names{ "this", "ExternalInteger", "ExternalFloat", "ExternalString", "ExternalVector", "ExternalMatrix", "ExternalIntegerArray", "ExternalFloatArray", "ExternalStringArray", "ExternalVectorArray", "ExternalMatrixArray", "NestedScope", "NestedScopeArray", "Auxiliary1", "Auxiliary2", "Auxiliary3", "Auxiliary4", "Auxiliary5" };
			Vector<Datum::DatumType> types{ Datum::DatumType::RTTIPtr, Datum::DatumType::Integer, Datum::DatumType::Float, Datum::DatumType::String, Datum::DatumType::Vector4, Datum::DatumType::Matrix4x4, Datum::DatumType::Integer, Datum::DatumType::Float, Datum::DatumType::String, Datum::DatumType::Vector4, Datum::DatumType::Matrix4x4, Datum::DatumType::Scope, Datum::DatumType::Scope, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown, Datum::DatumType::Unknown };

			Vector <Attributed::PairType*> auxiliaryAttributes = a.AuxiliaryAttributes();

			for (size_t i = 0; i < auxiliaryAttributes.Size(); i++)
			{
				Assert::IsTrue(a.IsAuxiliaryAttribute(auxiliaryAttributes[i]->first));
			}
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AttributedFooTest::sStartMemState;
}
