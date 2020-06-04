#pragma once
#include "OrderedSetTraits.h"
#include "RedBlackTree.h"		


namespace FIEAGameEngine
{
	template <typename Key, typename LessThanFunctor = std::less<Key>>
	class OrderedMultiSet final : public RedBlackTree<OrderedSetTraits<Key, LessThanFunctor, true>>
	{
	public:
		using BaseClass = RedBlackTree<OrderedSetTraits<Key, LessThanFunctor, true>>;
		using KeyType = typename BaseClass::KeyType;
		using KeyValueType = typename BaseClass::KeyValueType;
		using KeyCompare = typename BaseClass::KeyCompare;
		using KeyValueCompare = typename BaseClass::KeyValueCompare;
		using Iterator = typename BaseClass::Iterator;
		using ConstIterator = typename BaseClass::ConstIterator;

		OrderedMultiSet() = default;
		OrderedMultiSet(std::initializer_list<KeyValueType> iList);
		OrderedMultiSet(OrderedMultiSet const& other);
		OrderedMultiSet(OrderedMultiSet&& other);
		OrderedMultiSet& operator=(OrderedMultiSet const& other);
		OrderedMultiSet& operator=(OrderedMultiSet&& other);
		virtual ~OrderedMultiSet() = default;
	};
}
#include "OrderedMultiSet.inl"