#pragma once

namespace FIEAGameEngine
{

#pragma region FundamentalConstant
	template<class InstanceType, InstanceType instance>
	struct FundamentalConstant
	{
		static constexpr InstanceType value = instance;
		using ValueType = InstanceType;
		using Type = FundamentalConstant;

		/// <summary>
		/// Allows for FundamentalConstant to be both implicitly and explicitly converted to ValueType/InstanceType.
		/// </summary>
		/// <returns>The contained ValueType/InstanceType object contained by the fundamental constant.</returns>
		constexpr operator ValueType() const noexcept
		{
			return value;
		}
		
		/// <summary>
		/// Function Object operator for FundamentalConstant. Takes no parameters.
		/// </summary>
		/// <returns>The contained ValueType/InstanceType object contained by the fundamental constant.</returns>
		/*_NODISCARD*/ constexpr ValueType operator()() const noexcept
		{
			return value;
		}
	};

#pragma region BoolConstant
	
	//Used in the logical evaluations in templates. 

	template <bool instance>
	using FundamentalBoolConstant = FundamentalConstant<bool, instance>;

	using TrueType = FundamentalBoolConstant<true>;

	using FalseType = FundamentalBoolConstant<false>;

#pragma endregion

#pragma endregion

#pragma region Conditionals
	
	
	template <bool ConditionalTest, class EnabledType = void>
	struct EnableIfTest {}; // no member "type" when !ConditionalTest

	template <class EnabledType>
	struct EnableIfTest<true, EnabledType> { // type is EnabledType when ConditionalTest is true
		using type = EnabledType;
	};

	template <bool ConditionalTest, class EnabledType = void>
	using EnableIf = typename EnableIfTest<ConditionalTest, EnabledType>::type;

	// Templated conditional test which returns false when two different classes are passed to it.
	template <class /*Class1*/, class /*Class2*/>
	inline constexpr bool AreSameClass = false;

	// Templated conditional test which returns true when two of the same class is passed to it.
	template <class Class>
	inline constexpr bool AreSameClass<Class, Class> = true;

	//If the conditional test passes use Class1
	template <bool ConditionalTest, class Class1, class Class2>
	struct ConditionalEvaluation
	{
		using type = Class1;
	};

	//If the conditional test fails use Class1
	template <class Class1, class Class2>
	struct ConditionalEvaluation<false, Class1, Class2>
	{
		using type = Class2;
	};

	template <bool ConditionalTest, class Class1, class Class2>
	using ConditionalType = typename ConditionalEvaluation<ConditionalTest, Class1, Class2>::type;

#pragma endregion
	
	//More cool stuff in xtr1Common in std

}