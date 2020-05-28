#include "OrderedMap.h"

namespace FIEAGameEngine
{
	template <typename Key, typename Value, typename LessThanFunctor>
	inline OrderedMap<Key, Value, LessThanFunctor>::OrderedMap(std::initializer_list<ValueType> iList)
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
	inline OrderedMap<Key, Value, LessThanFunctor>::OrderedMap(OrderedMap&& other) : RedBlackTree(other)
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
}