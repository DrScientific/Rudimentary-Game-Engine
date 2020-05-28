#pragma once
#include "RedBlackTree.h"

namespace FIEAGameEngine
{
	//Traits required to make RedBlackTree behave like a set
	template <class _KeyType, class _ValueType, class LessThanFunctor, bool multipleEquivalentKeys>
	class OrderedMapTraits {
	public:
		using KeyType = _KeyType;
		using ValueType = std::pair<_KeyType const, _ValueType>;

		using KeyCompare = LessThanFunctor;

		static constexpr bool bIsMulti = multipleEquivalentKeys;

		class ValueCompare
		{
		protected:
			friend RedBlackTree<OrderedMapTraits>;

			ValueCompare(KeyCompare lessThanFunctor) : comp(lessThanFunctor) {}

			KeyCompare comp; // the comparator predicate for keys
		public:
			bool operator()(ValueType const& left, ValueType const& right) const
			{
				return comp(left.first, right.first);
			}
			
		};

		static const KeyType& ExtractKey(const ValueType& value) {
			return value.first;
		}
	};

	template <typename Key, typename Value, typename LessThanFunctor = std::less<Key>>
	class OrderedMap final : public RedBlackTree<OrderedMapTraits<Key, Value, LessThanFunctor, false>>
	{
	public:
		using BaseClass = RedBlackTree<OrderedMapTraits<Key, Value, LessThanFunctor, false>>;
		using KeyType = typename BaseClass::KeyType;
		using ValueType = typename BaseClass::ValueType;
		using KeyCompare = typename BaseClass::KeyCompare;
		using ValueCompare = typename BaseClass::ValueCompare;
		using Iterator = typename BaseClass::Iterator;
		using ConstIterator = typename BaseClass::ConstIterator;

		OrderedMap() = default;
		OrderedMap(std::initializer_list<ValueType> iList);
		OrderedMap(OrderedMap const& other);
		OrderedMap(OrderedMap&& other);
		OrderedMap& operator=(OrderedMap const& other);
		OrderedMap& operator=(OrderedMap&& other);
		virtual ~OrderedMap() = default;
	};
}
#include "OrderedMap.inl"