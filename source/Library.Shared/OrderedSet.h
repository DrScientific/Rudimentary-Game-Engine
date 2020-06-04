#pragma once
#include "OrderedSetTraits.h"

namespace FIEAGameEngine
{
	template <typename Key, typename LessThanFunctor = std::less<Key>>
	class OrderedSet final : public RedBlackTree<OrderedSetTraits<Key, LessThanFunctor, false>>
	{
	public:
		using BaseClass = RedBlackTree<OrderedSetTraits<Key, LessThanFunctor, false>>;
		using KeyType = typename BaseClass::KeyType;
		using KeyValueType = typename BaseClass::KeyValueType;
		using KeyCompare = typename BaseClass::KeyCompare;
		using KeyValueCompare = typename BaseClass::KeyValueCompare;
		using Iterator = typename BaseClass::Iterator;
		using ConstIterator = typename BaseClass::ConstIterator;

		OrderedSet() = default;
		OrderedSet(std::initializer_list<KeyValueType> iList);
		OrderedSet(OrderedSet const& other);
		OrderedSet(OrderedSet&& other);
		OrderedSet& operator=(OrderedSet const& other);
		OrderedSet& operator=(OrderedSet&& other);
		virtual ~OrderedSet() = default;
	};
}
#include "OrderedSet.inl"