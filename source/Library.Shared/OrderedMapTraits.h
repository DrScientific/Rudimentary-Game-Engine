#pragma once
#include "RedBlackTree.h"

namespace FIEAGameEngine
{
	//Traits required to make RedBlackTree behave like a set
	template <class _KeyType, class _ValueType, class LessThanFunctor, bool multipleEquivalentKeys>
	class OrderedMapTraits
	{
	public:
		using KeyType = _KeyType;
		using ValueType = _ValueType;
		using KeyValueType = std::pair<_KeyType const, _ValueType>;

		using KeyCompare = LessThanFunctor;
		class KeyValueCompare
		{
		public:
			bool operator()(KeyValueType const& left, KeyValueType const& right) const
			{
				return comp(left.first, right.first);
			}
		protected:
			friend RedBlackTree<OrderedMapTraits>;

			KeyValueCompare(KeyCompare lessThanFunctor) : comp(lessThanFunctor) {}

			KeyCompare comp; // the comparator predicate for keys
		};

		static constexpr bool bIsMulti = multipleEquivalentKeys;

		static const KeyType& ExtractKey(const KeyValueType& value) {
			return value.first;
		}
		static const KeyType& ExtractValue(const KeyValueType& value) {
			return value.second;
		}
	};
}