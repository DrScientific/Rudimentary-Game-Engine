#include "OrderedSet.h"

namespace FIEAGameEngine
{
	template<typename Key, typename LessThanFunctor>
	inline OrderedSet<Key, LessThanFunctor>::OrderedSet(std::initializer_list<KeyValueType> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}
	template<typename Key, typename LessThanFunctor>
	inline OrderedSet<Key, LessThanFunctor>::OrderedSet(OrderedSet const& other) : RedBlackTree(other)
	{
	}

	template<typename Key, typename LessThanFunctor>
	inline OrderedSet<Key, LessThanFunctor>::OrderedSet(OrderedSet&& other) : RedBlackTree(std::move(other))
	{
	}

	template<typename Key, typename LessThanFunctor>
	inline typename OrderedSet<Key, LessThanFunctor>& OrderedSet<Key, LessThanFunctor>::operator=(OrderedSet const& other)
	{
		return RedBlackTree::operator=(other);
	}

	template<typename Key, typename LessThanFunctor>
	inline typename OrderedSet<Key, LessThanFunctor>& OrderedSet<Key, LessThanFunctor>::operator=(OrderedSet&& other)
	{
		return RedBlackTree::operator=(other);
	}
}