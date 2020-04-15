#pragma once
#include "RedBlackTree.h"

namespace  FIEAGameEngine
{
	template <typename T, typename LessThanFunctor = std::less<T>>
	class Set final : public RedBlackTree<T, LessThanFunctor>
	{
	public:
		Set() = default;
		Set(std::initializer_list<T> iList);
		Set(Set const& other);
		Set(Set&& other);
		Set& operator=(Set const& other);
		Set& operator=(Set&& other);
		virtual ~Set() = default;
	};
}
#include "Set.inl"