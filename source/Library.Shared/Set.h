#pragma once
#include "RedBlackTree.h"

namespace  FIEAGameEngine
{
	//Traits required to make RedBlackTree behave like a set
	template <class KeyValType,	class LessThanFunctor = std::less<KeyValType>>
	class SetTraits {
	public:
		using KeyType = KeyValType;
		using ValueType = KeyValType;
		
		using KeyCompare = LessThanFunctor;
		using ValueCompare = KeyCompare;

		static const KeyType& ExtractKey(const ValueType& value) {
			return value;
		}
	};

	template <typename Key, typename LessThanFunctor = std::less<Key>>
	class Set final : public RedBlackTree<SetTraits<Key, LessThanFunctor>>
	{
	public:
		using BaseClass = RedBlackTree<SetTraits<Key, LessThanFunctor>>;
		using KeyType = typename BaseClass::KeyType;
		using KeyCompare = typename BaseClass::KeyCompare;
		using ValueCompare = typename BaseClass::ValueCompare;
		using ValueType = typename BaseClass::ValueType;
		using Iterator = typename BaseClass::Iterator;
		using ConstIterator = typename BaseClass::ConstIterator;

		Set() = default;
		Set(std::initializer_list<ValueType> iList);
		Set(Set const& other);
		Set(Set&& other);
		Set& operator=(Set const& other);
		Set& operator=(Set&& other);
		virtual ~Set() = default;
	};

}
#include "Set.inl"