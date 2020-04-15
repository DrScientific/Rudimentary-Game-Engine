#include "Set.h"

namespace FIEAGameEngine
{
	template<typename T, typename LessThanFunctor>
	inline Set<T, LessThanFunctor>::Set(std::initializer_list<T> iList) : RedBlackTree(iList)
	{
	}

	template<typename T, typename LessThanFunctor>
	inline Set<T, LessThanFunctor>::Set(Set const& other) : RedBlackTree(other)
	{
	}

	template<typename T, typename LessThanFunctor>
	inline Set<T, LessThanFunctor>::Set(Set&& other) : RedBlackTree(other)
	{
	}

	template<typename T, typename LessThanFunctor>
	inline typename Set<T, LessThanFunctor>& Set<T, LessThanFunctor>::operator=(Set const& other)
	{
		return RedBlackTree::operator=(other);
	}

	template<typename T, typename LessThanFunctor>
	inline typename Set<T, LessThanFunctor>& Set<T, LessThanFunctor>::operator=(Set&& other)
	{
		return RedBlackTree::operator=(other);
	}
}