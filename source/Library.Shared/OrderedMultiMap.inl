#include "OrderedMultiMap.h"

namespace FIEAGameEngine
{
	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMultiMap<Key, Value, LessThanFunctor>::OrderedMultiMap(std::initializer_list<KeyValueType> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}
	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMultiMap<Key, Value, LessThanFunctor>::OrderedMultiMap(OrderedMultiMap const& other) : RedBlackTree(other)
	{
	}

	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMultiMap<Key, Value, LessThanFunctor>::OrderedMultiMap(OrderedMultiMap&& other) : RedBlackTree(std::move(other))
	{
	}

	template <typename Key, typename Value, typename LessThanFunctor>
	inline typename OrderedMultiMap<Key, Value, LessThanFunctor>& OrderedMultiMap<Key, Value, LessThanFunctor>::operator=(OrderedMultiMap const& other)
	{
		return RedBlackTree::operator=(other);
	}

	template <typename Key, typename Value, typename LessThanFunctor>
	inline typename OrderedMultiMap<Key, Value, LessThanFunctor>& OrderedMultiMap<Key, Value, LessThanFunctor>::operator=(OrderedMultiMap&& other)
	{
		return RedBlackTree::operator=(other);
	}

	template<typename Key, typename Value, typename LessThanFunctor>
	inline std::pair<typename OrderedMultiMap<Key, Value, LessThanFunctor>::Iterator, bool> OrderedMultiMap<Key, Value, LessThanFunctor>::Insert(KeyType const& key, ValueType const& value)
	{
		return Insert(std::make_pair(key, value));
	}
}