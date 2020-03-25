#pragma once

/// <summary>
/// The inline file containing the definition of each SList function declared in SList.h.
/// </summary>

#include "SList.h"

namespace FIEAGameEngine
{
	template<typename T>
	inline SList<T>::SList()
	{

	}

	template<typename T>
	inline SList<T>::SList(SList const & other)
	{
		*this = other;
	}

	template<typename T>
	inline SList<T>::SList(std::initializer_list<T> iList)
	{
		for (auto& i: iList)
		{
			PushBack(i);
		}
	}

	template<typename T>
	inline SList<T>::~SList()
	{
		Clear();
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::begin() const
	{
		return SList<T>::Iterator(*this, mFront);
	}

	template<typename T> typename
	inline SList<T>::const_Iterator SList<T>::cbegin() const
	{
		return SList<T>::const_Iterator(*this, mFront);
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::end() const
	{
		return SList<T>::Iterator(*this, nullptr);
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::PushFront(T const value)
	{
		Node * newFront = new Node(value);
		newFront->mNext = mFront;
		mFront = newFront;

		if (mSize == 0)
		{
			mBack = mFront;
		}
		mSize++;

		return Iterator(*this, newFront);
	}

	template <typename T> typename
	inline SList<T>::Iterator SList<T>::PopFront()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}

		Node* newFront = mFront->mNext;

		delete mFront;

		if (mSize == 1)
		{
			mFront = mBack = nullptr;
		}
		else
		{
			mFront = newFront;
		}
		mSize--;

		return Iterator(*this, mFront);		
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::PushBack(T const value)
	{
		Node* newBack = new Node(value);

		if (!mSize == 0)
		{
			mBack->mNext = newBack;
		}

		mBack = newBack;
		
		if (mSize == 0)
		{
			mFront = mBack;
		}
		
		mSize++;

		return Iterator(*this, newBack);
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::PopBack()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}

		Node* newBack = mFront;

		if (mSize == 1)
		{
			delete mBack;
			
			newBack = mFront = mBack = nullptr;
		}
		else
		{
			while (newBack->mNext != mBack)
			{
				newBack = newBack->mNext;
			}
			
			newBack->mNext = nullptr;
			delete mBack;
			mBack = newBack;			
		}
		mSize--;

		return Iterator(*this, newBack);
	}

	template<typename T>
	inline bool SList<T>::isEmpty() const
	{
		return mSize <= 0;
	}

	template<typename T>
	inline T & SList<T>::Front()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}
		return mFront->mData;
	}

	template<typename T>
	inline const T& SList<T>::Front() const
	{
		return const_cast<SList*>(this)->Front();
	}

	template<typename T>
	inline T& SList<T>::Back()
	{
		if (mSize == 0)
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}
		return mBack->mData;
	}

	template<typename T>
	inline const T& SList<T>::Back() const
	{
		return const_cast<SList*>(this)->Back();
	}

	
	template<typename T>
	inline void SList<T>::Clear()
	{
		Node *currentNode = mFront, *nextNode = nullptr;

		while (currentNode != nullptr)
		{
			nextNode = currentNode->mNext;
			delete currentNode;
			currentNode = nextNode;
		}

		mFront = mBack = nullptr;
		mSize = 0;
	}

	template<typename T>
	inline size_t SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	inline void SList<T>::InsertAfter(Iterator const & it, T const & value)
	{
		if (it == end())
		{
			PushBack(value);
		}
		else
		{
			Node *nodeBeforeInsert = it.mNode, *nodeToBeInserted = new Node(value), *nodeAfterInsert = it.mNode->mNext;
			nodeBeforeInsert->mNext = nodeToBeInserted;
			nodeToBeInserted->mNext = nodeAfterInsert;
			mSize++;
		}
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::Find(T const & value) const
	{
		SList<T>::Iterator it = begin();
		for (auto& i : *this)
		{
			if (value == i)
			{
				return it;
			}
			it++;
		}
		return end();
	}

	template<typename T>
	inline void SList<T>::Remove(T const & value)
	{
		Iterator foundIt = Find(value);
		Remove(foundIt);
	}

	template<typename T>
	inline void SList<T>::Remove(Iterator & it)
	{
		Node* nodeToRemove = it.mNode;
		if (nodeToRemove != nullptr)
		{
			if (nodeToRemove == mFront)
			{
				PopFront();
			}
			else if (nodeToRemove != mBack)
			{
				Node *nodeAfterNodeToRemove = nodeToRemove->mNext;
				nodeToRemove->mData = nodeAfterNodeToRemove->mData;
				nodeToRemove->mNext = nodeAfterNodeToRemove->mNext;
				delete nodeAfterNodeToRemove;
				mSize--;
			}
			else
			{
				PopBack();
			}
		}
	}

	template<typename T>
	inline SList<T> & SList<T>::operator=(const SList & rhs)
	{
		if (*this != rhs)
		{
			Clear();
			for (auto& i : rhs)
			{
				PushBack(i);
			}
		}
		return *this;
	}

	template<typename T>
	inline bool SList<T>::operator==(SList const & rhs) const
	{
		if (mSize == rhs.mSize)
		{
			Node *lhsElement = mFront, *rhsElement = rhs.mFront;
			while ((lhsElement != nullptr && rhsElement != nullptr) && (lhsElement->mData == rhsElement->mData))
			{
				lhsElement = lhsElement->mNext;
				rhsElement = rhsElement->mNext;
			}
			if (lhsElement == nullptr && rhsElement == nullptr)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline bool SList<T>::operator!=(SList const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline SList<T>::Node::Node(T const & data, Node * next)
		: mData(data), mNext(next)
	{
	}

	template<typename T> typename
	inline SList<T>::Iterator & SList<T>::Iterator::operator++()
	{
		if (this->mNode != nullptr)
		{
			mNode = mNode->mNext;
		}
		return *this;
	}

	template<typename T> typename
	inline SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		if (this->mNode != nullptr)
		{
			mNode = mNode->mNext;
		}
		return iteratorBeforeIncrement;
	}

	template<typename T>
	inline bool SList<T>::Iterator::operator==(Iterator const & rhs) const
	{
		return (mOwner == rhs.mOwner) && (mNode == rhs.mNode);
	}

	template<typename T>
	inline bool SList<T>::Iterator::operator!=(Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T& SList<T>::Iterator::operator*()
	{
		return mNode->mData;
	}

	template<typename T>
	inline SList<T>::Iterator::Iterator(const SList& owner, Node * node) :
		mOwner(&owner), mNode(node)
	{

	}

	template<typename T>
	inline SList<T>::const_Iterator::const_Iterator(const Iterator & it)
	{
		mNode = it.mNode;
		mOwner = it.mOwner;
	}

	template<typename T> typename
	inline SList<T>::const_Iterator & SList<T>::const_Iterator::operator++()
	{
		mNode = mNode->mNext;
		return *this;
	}

	template<typename T> typename
	inline SList<T>::const_Iterator SList<T>::const_Iterator::operator++(int)
	{
		const_Iterator iteratorBeforeIncrement = *this;
		mNode = mNode->mNext;
		return iteratorBeforeIncrement;
	}

	template<typename T>
	inline bool SList<T>::const_Iterator::operator==(const_Iterator const & rhs) const
	{
		return (mOwner == rhs.mOwner) && (mNode == rhs.mNode);
	}

	template<typename T>
	inline bool SList<T>::const_Iterator::operator!=(const_Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T const & SList<T>::const_Iterator::operator*() const
	{
		return mNode->mData;
	}

	template<typename T>
	inline SList<T>::const_Iterator::const_Iterator(const SList& owner, Node * node) :
		mOwner(&owner), mNode(node)
	{

	}
}