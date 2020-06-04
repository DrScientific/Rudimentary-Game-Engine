#pragma once
#include "OrderedMapTraits.h"
#include "RedBlackTree.h"		


namespace FIEAGameEngine
{
	template <typename Key, typename Value, typename LessThanFunctor = std::less<Key>>
	class OrderedMultiMap final : public RedBlackTree<OrderedMapTraits<Key, Value, LessThanFunctor, true>>
	{
	public:
		using BaseClass = RedBlackTree<OrderedMapTraits<Key, Value, LessThanFunctor, true>>;
		using KeyType = typename BaseClass::KeyType;
		using ValueType = typename BaseClass::ValueType;
		using KeyValueType = typename BaseClass::KeyValueType;
		using KeyCompare = typename BaseClass::KeyCompare;
		using KeyValueCompare = typename BaseClass::KeyValueCompare;
		using Iterator = typename BaseClass::Iterator;
		using ConstIterator = typename BaseClass::ConstIterator;

		OrderedMultiMap() = default;
		OrderedMultiMap(std::initializer_list<KeyValueType> iList);
		OrderedMultiMap(OrderedMultiMap const& other);
		OrderedMultiMap(OrderedMultiMap&& other);
		OrderedMultiMap& operator=(OrderedMultiMap const& other);
		OrderedMultiMap& operator=(OrderedMultiMap&& other);
		virtual ~OrderedMultiMap() = default;

		using BaseClass::Insert;		//Disables function hiding by moving base Insert into derived scope.
		std::pair<Iterator, bool> Insert(KeyType const& key, ValueType const& value);
	};
}
#include "OrderedMultiMap.inl"