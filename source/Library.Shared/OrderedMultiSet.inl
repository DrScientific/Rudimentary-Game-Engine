#include "OrderedMultiSet.h"

namespace FIEAGameEngine
{
	template <typename Key, typename LessThanFunctor>
	inline OrderedMultiSet<Key, LessThanFunctor>::OrderedMultiSet(std::initializer_list<KeyValueType> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}
	template <typename Key, typename LessThanFunctor>
	inline OrderedMultiSet<Key, LessThanFunctor>::OrderedMultiSet(OrderedMultiSet const& other) : RedBlackTree(other)
	{
	}

	template <typename Key, typename LessThanFunctor>
	inline OrderedMultiSet<Key, LessThanFunctor>::OrderedMultiSet(OrderedMultiSet&& other) : RedBlackTree(std::move(other))
	{
	}

	template <typename Key, typename LessThanFunctor>
	inline typename OrderedMultiSet<Key, LessThanFunctor>& OrderedMultiSet<Key, LessThanFunctor>::operator=(OrderedMultiSet const& other)
	{
		return RedBlackTree::operator=(other);
	}

	template <typename Key, typename LessThanFunctor>
	inline typename OrderedMultiSet<Key, LessThanFunctor>& OrderedMultiSet<Key, LessThanFunctor>::operator=(OrderedMultiSet&& other)
	{
		return RedBlackTree::operator=(other);
	}
}