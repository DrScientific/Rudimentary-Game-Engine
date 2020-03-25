/// <summary>
/// The inline file containing the definition of each Vector function declared in Vector.h.
/// </summary>

#include "Vector.h"

namespace FIEAGameEngine
{
	template<typename T> typename
	inline Vector<T>::Iterator & Vector<T>::Iterator::operator++()
	{
		if (mDataIndex >= mOwner->mSize)
		{
			throw std::exception(incrementIteratorPastEndExceptionText.c_str());
		}
		mDataIndex += 1;
		return *this;
	}

	template<typename T> typename
	inline Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}

	template<typename T> typename
	inline Vector<T>::Iterator & Vector<T>::Iterator::operator--()
	{
		if (mDataIndex <= 0)
		{
			throw std::exception(incrementIteratorPastEndExceptionText.c_str());
		}
		mDataIndex -= 1;
		return *this;
	}

	template<typename T> typename
	inline Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator--();
		return iteratorBeforeIncrement;
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator==(Iterator const & rhs) const
	{
		return (mOwner == rhs.mOwner) && (mDataIndex == rhs.mDataIndex);
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator!=(Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T& Vector<T>::Iterator::operator*() const
	{
		if (mDataIndex >= mOwner->mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		return mOwner->mArray[mDataIndex];
	}

	template<typename T>
	inline Vector<T>::Iterator::Iterator(const Vector& owner, size_t index) :
		mOwner(&owner), mDataIndex(index)
	{

	}

	template<typename T>
	inline Vector<T>::const_Iterator::const_Iterator(const Iterator & it)
	{
		mDataIndex = it.mDataIndex;
		mOwner = it.mOwner;
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator & Vector<T>::const_Iterator::operator++()
	{
		if (mDataIndex >= mOwner->mSize)
		{
			throw std::exception(incrementIteratorPastEndExceptionText.c_str());
		}
		mDataIndex += 1;
		return *this;
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator Vector<T>::const_Iterator::operator++(int)
	{
		const_Iterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}

	template<typename T> typename
		inline Vector<T>::const_Iterator & Vector<T>::const_Iterator::operator--()
	{
		if (mDataIndex <= 0)
		{
			throw std::exception(incrementIteratorPastEndExceptionText.c_str());
		}
		mDataIndex -= 1;
		return *this;
	}

	template<typename T> typename
		inline Vector<T>::const_Iterator Vector<T>::const_Iterator::operator--(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator--();
		return iteratorBeforeIncrement;
	}

	template<typename T>
	inline bool Vector<T>::const_Iterator::operator==(const_Iterator const & rhs) const
	{
		return (mOwner == rhs.mOwner) && (mDataIndex == rhs.mDataIndex);
	}

	template<typename T>
	inline bool Vector<T>::const_Iterator::operator!=(const_Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T const & Vector<T>::const_Iterator::operator*() const
	{
		if (mDataIndex >= mOwner->mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		return mOwner->mArray[mDataIndex];
	}

	template<typename T>
	inline Vector<T>::const_Iterator::const_Iterator(const Vector& owner, size_t index) :
		mOwner(&owner), mDataIndex(index)
	{

	}

	template<typename T>
	inline Vector<T>::Vector()
	{
		
		mArray = reinterpret_cast<T*>(malloc(sizeof(T) * mCapacity));
	}

	template<typename T>
	inline Vector<T>::Vector(Vector const & other)
	{
		mArray = reinterpret_cast<T*>(malloc(sizeof(T) * other.mCapacity));
		*this = other;
	}

	template<typename T>
	inline Vector<T> & Vector<T>::operator=(Vector const & rhs)
	{
		Clear();
		if (mCapacity < rhs.mCapacity)
		{
			Reserve(static_cast<unsigned int>(rhs.mCapacity));
		}
		while (mSize < rhs.mSize)
		{
			PushBack(rhs.mArray[mSize]);
		}
		return *this;
	}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> iList)
	{
		mArray = reinterpret_cast<T*>(malloc(sizeof(T) * mCapacity));
		if (mCapacity < iList.size())
		{
			Reserve(static_cast<unsigned int>(iList.size()));
		}

		for (auto& i : iList)
		{
			PushBack(i);
		}
	}

	template<typename T>
	inline Vector<T>::~Vector()
	{
		Clear();
		free(mArray);
	}

	template<typename T> typename
	inline Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator(*this, 0);
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator Vector<T>::begin() const
	{
		return const_Iterator(*this, 0);
	}

	template<typename T> typename
	inline Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator(*this, mSize);
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator Vector<T>::end() const
	{
		return const_Iterator(*this, mSize);
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator Vector<T>::cbegin() const
	{
		return const_Iterator(*this, 0);
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator Vector<T>::cend() const
	{
		return const_Iterator(*this, mSize);
	}

	template<typename T>
	inline void Vector<T>::Clear()
	{
		for (size_t i = 0; i < mSize; i++)
		{
			mArray[i].~T();
		}
		mSize = 0;
	}

	template<typename T>
	inline void Vector<T>::Reserve(unsigned int newCapacity)
	{
		if (newCapacity < mCapacity)
		{
			throw std::exception(newCapacityCannotBeSmallerThanCapacityExceptionText.c_str());
		}
		mCapacity = newCapacity;
		mArray = static_cast<T*>(realloc(mArray, mCapacity * sizeof(T)));
		
	}

	template<typename T>
	inline T& Vector<T>::operator[](size_t const & index)
	{
		if (index >= mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		else
		{
			return mArray[index];
		}
	}

	template<typename T>
	inline T const & Vector<T>::operator[](size_t const & index) const
	{
		if (index >= mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		else
		{
			return mArray[index];
		}
	}

	template<typename T>
	inline T & Vector<T>::At(size_t const & index)
	{
		if (index >= mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		else
		{
			return mArray[index];
		}
	}

	template<typename T>
	inline T const & Vector<T>::At(size_t const & index) const
	{
		if (index >= mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		else
		{
			return mArray[index];
		}
	}

	template<typename T>
	inline size_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template<typename T>
	inline size_t Vector<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	template<typename T>
	inline bool Vector<T>::operator==(Vector<T> const & rhs) const
	{
		if (mSize == rhs.mSize)
		{
			for (size_t i = 0; i < mSize; i++)
			{
				if ((*this)[i] != rhs[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	template<typename T>
	inline bool Vector<T>::operator!=(Vector<T> const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename T>
	inline T & Vector<T>::Front()
	{
		if (mSize == 0)
		{
			throw std::exception(vectorEmptyExceptionText.c_str());
		}
		else
		{
			return *mArray;
		}
	}

	template<typename T>
	inline T const & Vector<T>::Front() const
	{
		if (mSize == 0)
		{
			throw std::exception(vectorEmptyExceptionText.c_str());
		}
		else
		{
			return *mArray;
		}
	}

	template<typename T>
	inline T & Vector<T>::Back()
	{
		if (mSize == 0)
		{
			throw std::exception(vectorEmptyExceptionText.c_str());
		}
		else
		{
			return mArray[mSize - 1];
		}
	}

	template<typename T>
	inline T const & Vector<T>::Back() const
	{
		if (mSize == 0)
		{
			throw std::exception(vectorEmptyExceptionText.c_str());
		}
		else
		{
			return mArray[mSize - 1];
		}
	}

	template<typename T>
	inline void Vector<T>::PushBack(T const & value)
	{
		if (mSize == mCapacity)
		{
			Reserve(static_cast<unsigned int>(mCapacity * 2));
		}

		new (mArray+(mSize++)) T (value);
	}

	template<typename T> typename
	inline Vector<T>::Iterator Vector<T>::PopBack()
	{
		if (mSize > 1)
		{
			mArray[--mSize].~T();
			return Vector<T>::Iterator(*this, mSize - 1);
		}
		if (mSize == 1)
		{
			mArray[--mSize].~T();
			return begin();
		}
		throw std::exception(vectorEmptyExceptionText.c_str());
	}

	template<typename T> typename
	inline Vector<T>::Iterator Vector<T>::Find(T const & value)
	{

		for (size_t i = 0; i < mSize; i++)
		{
			if (mArray[i] == value)
			{
				return Iterator(*this, i);
			}
		}
		return end();
	}

	template<typename T> typename
	inline Vector<T>::const_Iterator Vector<T>::Find(T const & value) const
	{
		Iterator it = const_cast<Vector&>(*this).Find(value);
		return const_Iterator(it);
	}

	template<typename T>
	inline void Vector<T>::Remove(T const & value)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (mArray[i] == value)
			{
				mArray[i].~T();
				memmove(&(mArray[i]), &(mArray[i + 1]), (mSize - 1 - i) * sizeof(T));
				mSize--;
				break;
			}
		}
	}

	template<typename T>
	inline void Vector<T>::Remove(Iterator const & start, Iterator const & finish)
	{
		if (start.mOwner != this || finish.mOwner != this)
		{
			throw std::exception(iteratorFromOtherListExceptionText.c_str());
		}
		if (mSize > 0 && start.mDataIndex < finish.mDataIndex)
		{
			for (size_t i = start.mDataIndex; i <= finish.mDataIndex; i++)
			{
				mArray[i].~T();
			}
			memmove(&(mArray[start.mDataIndex]), &(mArray[finish.mDataIndex + 1]), (mSize -finish.mDataIndex - 1) * sizeof(T));
			mSize -= (finish.mDataIndex - start.mDataIndex + 1);
		}
	}
}