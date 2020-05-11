#include "Set.h"

namespace FIEAGameEngine
{
	template<typename Key, typename LessThanFunctor>
	inline Set<Key, LessThanFunctor>::Set(std::initializer_list<ValueType> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}
	template<typename Key, typename LessThanFunctor>
	inline Set<Key, LessThanFunctor>::Set(Set const& other) : RedBlackTree(other)
	{
	}

	template<typename Key, typename LessThanFunctor>
	inline Set<Key, LessThanFunctor>::Set(Set&& other) : RedBlackTree(other)
	{
	}

	template<typename Key, typename LessThanFunctor>
	inline typename Set<Key, LessThanFunctor>& Set<Key, LessThanFunctor>::operator=(Set const& other)
	{
		return RedBlackTree::operator=(other);
	}

	template<typename Key, typename LessThanFunctor>
	inline typename Set<Key, LessThanFunctor>& Set<Key, LessThanFunctor>::operator=(Set&& other)
	{
		return RedBlackTree::operator=(other);
	}
}