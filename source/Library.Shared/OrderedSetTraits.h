#pragma once
#include "RedBlackTree.h"

namespace FIEAGameEngine
{
	//Traits required to make RedBlackTree behave like a set
	template <class _KeyValueType, class LessThanFunctor, bool multipleEquivalentKeys>
	class OrderedSetTraits
	{
	public:
		using KeyType = _KeyValueType;
		using ValueType = _KeyValueType;
		using KeyValueType = _KeyValueType;

		using KeyCompare = LessThanFunctor;
		using KeyValueCompare = KeyCompare;

		static constexpr bool bIsMulti = multipleEquivalentKeys;

		static const KeyType& ExtractKey(const KeyValueType& value) {
			return value;
		}
		static const ValueType& ExtractValue(const KeyValueType& value) {
			return value;
		}
	};
}