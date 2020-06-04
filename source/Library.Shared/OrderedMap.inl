#include "OrderedMap.h"

namespace FIEAGameEngine
{
	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMap<Key, Value, LessThanFunctor>::OrderedMap(std::initializer_list<KeyValueType> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}
	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMap<Key, Value, LessThanFunctor>::OrderedMap(OrderedMap const& other) : RedBlackTree(other)
	{
	}

	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMap<Key, Value, LessThanFunctor>::OrderedMap(OrderedMap&& other) : RedBlackTree(std::move(other))
	{
	}

	template <typename Key, typename Value, typename LessThanFunctor>
	inline typename OrderedMap<Key, Value, LessThanFunctor>& OrderedMap<Key, Value, LessThanFunctor>::operator=(OrderedMap const& other)
	{
		return RedBlackTree::operator=(other);
	}

	template <typename Key, typename Value, typename LessThanFunctor>
	inline typename OrderedMap<Key, Value, LessThanFunctor>& OrderedMap<Key, Value, LessThanFunctor>::operator=(OrderedMap&& other)
	{
		return RedBlackTree::operator=(other);
	}

	template<typename Key, typename Value, typename LessThanFunctor>
	inline std::pair<typename OrderedMap<Key, Value, LessThanFunctor>::Iterator, bool> OrderedMap<Key, Value, LessThanFunctor>::Insert(KeyType const& key, ValueType const& value)
	{
		return Insert(std::make_pair(key, value));
	}
}