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
		for (auto & i: iList)
		{
			PushBack(i);
		}
	}

	template<typename T>
	inline SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	inline void SList<T>::PushFront(T const value)
	{
		Node *newFront = new Node;
		newFront->data = value;
		newFront->next = mFront;
		mFront = newFront;

		if (isEmpty())
		{
			mBack = mFront;
		}
		mSize++;
	}

	template <typename T>
	inline T SList<T>::PopFront()
	{
		if (isEmpty())
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}

		T oldFrontData = mFront->data;

		//List is one element
		if (mFront == mBack)
		{
			delete mFront;
			mSize--;
			mFront = mBack = nullptr;
		}
		//List is more than one element
		else
		{
			Node *newFront = mFront->next;
			delete mFront;
			mSize--;
			mFront = newFront;
		}

		return oldFrontData;

		
	}

	template<typename T>
	inline void SList<T>::PushBack(T const value)
	{
		Node *newBack = new Node;
		newBack->data = value;
		if (!isEmpty())
		{
			mBack->next = newBack;
		}
		mBack = newBack;
		
		if (isEmpty())
		{
			mFront = mBack;
		}
		
		mSize++;
	}

	template<typename T>
	inline T SList<T>::PopBack()
	{
		if (isEmpty())
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}

		T oldBackData = mBack->data;

		//List is one element
		if (mBack == mFront)
		{
			delete mBack;
			mSize--;
			mFront = mBack = nullptr;
		}
		//List is more than one element
		else
		{
			Node *newBack = mFront;
			while (newBack != mBack && newBack->next != mBack)
			{
				newBack = newBack->next;
			}

			delete mBack;
			mSize--;
			mBack = newBack;
		}


		return oldBackData;
	}

	template<typename T>
	inline bool SList<T>::isEmpty() const
	{
		return Size() <= 0;
	}

	template<typename T>
	inline T & SList<T>::Front()
	{
		if (isEmpty())
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}
		return mFront->data;
	}

	template<typename T>
	inline T & SList<T>::Back()
	{
		if (isEmpty())
		{
			throw std::exception(listEmptyExceptionText.c_str());
		}
		return mBack->data;
	}

	
	template<typename T>
	inline void SList<T>::Clear()
	{
		Node *currentNode =mFront, *nextNode = nullptr;

		while (currentNode != nullptr)
		{
			nextNode = currentNode->next;
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

	/*template<typename T>
	inline bool SList<T>::Find(const T value) const
	{
		Node* currentNode = mFront;

		while (currentNode != nullptr)
		{
			if (value == currentNode.data)
			{
				return true;
			}
			currentNode = currentNode->next;
		}

		return false;
	}*/

	template<typename T>
	inline SList<T> & SList<T>::operator=(const SList & rhs)
	{
		if (*this != rhs)
		{
			Clear();
			Node *rhsCurrentNode = rhs.mFront;
			while (rhsCurrentNode != nullptr)
			{
				PushBack(rhsCurrentNode->data);
				rhsCurrentNode = rhsCurrentNode->next;
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
			while ((lhsElement != nullptr && rhsElement != nullptr) && (lhsElement->data == rhsElement->data))
			{
				lhsElement = lhsElement->next;
				rhsElement = rhsElement->next;
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
}