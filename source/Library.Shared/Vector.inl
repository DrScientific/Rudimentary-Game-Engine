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
	inline bool Vector<T>::Iterator::operator==(Iterator const& other) const
	{
		return (mOwner == other.mOwner) && (mDataIndex == other.mDataIndex);
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator!=(Iterator const& other) const
	{
		return !(*this == other);
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
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator & it) :
		mOwner(it.mOwner), mDataIndex(it.mDataIndex)
	{

	}

	template<typename T>
	inline typename Vector<T>::ConstIterator & Vector<T>::ConstIterator::operator=(const Iterator & it)
	{
		if (this != &it)
		{
			mDataIndex = it.mDataIndex;
			mOwner = it.mOwner;
		}
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator & Vector<T>::ConstIterator::operator++()
	{
		if (mDataIndex >= mOwner->mSize)
		{
			throw std::exception(incrementIteratorPastEndExceptionText.c_str());
		}
		mDataIndex += 1;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator & Vector<T>::ConstIterator::operator--()
	{
		if (mDataIndex <= 0)
		{
			throw std::exception(incrementIteratorPastEndExceptionText.c_str());
		}
		mDataIndex -= 1;
		return *this;
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator--();
		return iteratorBeforeIncrement;
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator==(ConstIterator const& other) const
	{
		return (mOwner == other.mOwner) && (mDataIndex == other.mDataIndex);
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator!=(ConstIterator const& other) const
	{
		return !(*this == other);
	}

	template<typename T>
	inline T const& Vector<T>::ConstIterator::operator*() const
	{
		if (mDataIndex >= mOwner->mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		return mOwner->mArray[mDataIndex];
	}

	template<typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector& owner, size_t index) :
		mOwner(&owner), mDataIndex(index)
	{

	}

	template<typename T>
	inline Vector<T>::Vector(size_t initialCapacity)
	{
		Reserve(initialCapacity);
	}

	template<typename T>
	inline Vector<T>::Vector(Vector const& other)
	{
		*this = other;
	}

	template<typename T>
	inline Vector<T>::Vector(Vector && other) :
		mSize(other.mSize), mCapacity(other.mCapacity), mArray(other.mArray)
	{
		other.mSize = 0;
		other.mCapacity = 0;
		other.mArray = nullptr;
	}

	template<typename T>
	inline Vector<T> & Vector<T>::operator=(Vector const& other)
	{
		if (this != &other)
		{
			Clear();
			if (mCapacity < other.mCapacity)
			{
				Reserve(static_cast<unsigned int>(other.mCapacity));
			}
			while (mSize < other.mSize)
			{
				PushBack(other.mArray[mSize]);
			}
		}
		return *this;
	}

	template<typename T>
	inline Vector<T> & Vector<T>::operator=(Vector && other)
	{
		if (this != &other)
		{
			Clear();
			ShrinkToFit();

			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mArray = other.mArray;

			other.mSize = 0;
			other.mCapacity = 0;
			other.mArray = nullptr;
		}

		return *this;
	}

	template<typename T>
	inline Vector<T>::Vector(std::initializer_list<T> iList)
	{
		Reserve(iList.size());
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
		inline Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return ConstIterator(*this, 0);
	}

	template<typename T> typename
		inline Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator(*this, mSize);
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator Vector<T>::end() const
	{
		return ConstIterator(*this, mSize);
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator Vector<T>::cbegin() const
	{
		return ConstIterator(*this, 0);
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator Vector<T>::cend() const
	{
		return ConstIterator(*this, mSize);
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
	inline void Vector<T>::Reserve(size_t newCapacity)
	{
		if (newCapacity > mCapacity)
		{
			mCapacity = newCapacity;
			T* newMemAddress = static_cast<T*>(realloc(mArray, mCapacity * sizeof(T)));
			if (newMemAddress)
			{
				mArray = newMemAddress;
			}
		}
	}

	template<typename T>
	inline void Vector<T>::Resize(size_t newSize)
	{
		if (newSize > mCapacity)
		{
			Reserve(newSize);
			for (mSize; mSize < newSize;)
			{
				PushBack(T());
			}
		}
		else if (newSize > mSize)
		{
			for (mSize; mSize < newSize;)
			{
				PushBack(T());
			}
		}
		else if (mSize < newSize)
		{
			Iterator FirstElementToRemove = Iterator(*this, newSize);
			Iterator LastElementInVector = --end();
			Remove(FirstElementToRemove, LastElementInVector);
		}
	}

	template<typename T>
	inline T& Vector<T>::operator[](size_t const& index)
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
	inline T const& Vector<T>::operator[](size_t const& index) const
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
	inline Vector<T> Vector<T>::operator+(Vector<T> const& other)
	{
		Vector<T> sum = *this;
		for (auto element : other)
		{
			sum.PushBack(element);
		}
		return sum;
	}

	template<typename T>
	inline Vector<T> const Vector<T>::operator+(Vector<T> const& other) const
	{
		Vector<T> sum = *this;
		for (auto element : other)
		{
			sum.PushBack(element);
		}
		return sum;
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator+=(Vector<T> const& other)
	{
		for (auto element : other)
		{
			this->PushBack(element);
		}
		return *this;
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator-(Vector<T> const& other)
	{
		Vector<T> difference = *this;
		for (auto element : other)
		{
			difference->Remove(element);
		}
		return difference;
	}

	template<typename T>
	inline Vector<T> const Vector<T>::operator-(Vector<T> const& other) const
	{
		Vector<T> difference = *this;
		for (auto element : other)
		{
			difference->Remove(element);
		}
		return difference;
	}

	template<typename T>
	inline Vector<T> Vector<T>::operator-=(Vector<T> const& other)
	{
		for (auto element : other)
		{
			this->Remove(element);
		}
		return *this;
	}

	template<typename T>
	inline T & Vector<T>::At(size_t const& index)
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
	inline T const& Vector<T>::At(size_t const& index) const
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
	inline bool Vector<T>::operator==(Vector<T> const& other) const
	{
		//return std::equal(begin(), end(), other.begin(), other.end());

		if (mSize == other.mSize)
		{
			for (size_t i = 0; i < mSize; i++)
			{
				if ((*this)[i] != other[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;

	}

	template<typename T>
	inline bool Vector<T>::operator!=(Vector<T> const& other) const
	{
		return !(*this == other);
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
	inline T const& Vector<T>::Front() const
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
	inline T const& Vector<T>::Back() const
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
	inline void Vector<T>::PushBack(T const& value)
	{
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				mCapacity = 1;
			}
			Reserve(mCapacity * 2);
		}

		new (mArray + (mSize++)) T(value);
	}

	template<typename T>
	inline void Vector<T>::PushBack(T const&& value)
	{
		if (mSize == mCapacity)
		{
			if (mCapacity == 0)
			{
				mCapacity = 1;
			}
			Reserve(mCapacity * 2);
		}

		new (mArray + (mSize++)) T(value);
	}

	template<typename T>
	inline void Vector<T>::push_back(T const& value)
	{
		PushBack(value);
	}

	template<typename T> typename
		inline Vector<T>::Iterator Vector<T>::PopBack()
	{
		if (mSize == 0)
		{
			throw std::exception(vectorEmptyExceptionText.c_str());
		}
		mArray[--mSize].~T();
		Iterator it = end();
		if (mSize > 0)
		{
			it.mDataIndex = mSize - 1;
		}
		return it;
	}

	template<typename T> typename
		inline Vector<T>::Iterator Vector<T>::Find(T const& value)
	{
		Iterator it = begin();

		for (; it != end(); ++it)
		{
			if (*it == value)
			{
				break;
			}
		}
		return it;
	}

	template<typename T> typename
		inline Vector<T>::ConstIterator Vector<T>::Find(T const& value) const
	{
		Iterator it = const_cast<Vector&>(*this).Find(value);
		return ConstIterator(it);
	}

	template<typename T>
	inline void Vector<T>::Remove(T const& value)
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
	inline void Vector<T>::Remove(Iterator const& iteratorToRemove)
	{
		if (iteratorToRemove.mOwner != this)
		{
			throw std::exception(iteratorFromOtherListExceptionText.c_str());
		}
		if (mSize > 0)
		{
			mArray[iteratorToRemove.mDataIndex].~T();
	
			memmove(&(mArray[iteratorToRemove.mDataIndex]), &(mArray[iteratorToRemove.mDataIndex + 1]), (mSize - iteratorToRemove.mDataIndex - 1) * sizeof(T));
			mSize -= 1;
		}
	}

	template<typename T>
	inline void Vector<T>::RemoveAt(size_t index)
	{
		if (index >= mSize)
		{
			throw std::exception(indexOutOfBoundsExceptionText.c_str());
		}
		mArray[index].~T();
		memmove(&(mArray[index]), &(mArray[index + 1]), (mSize - 1 - index) * sizeof(T));
		mSize--;
	}

	template<typename T>
	inline void Vector<T>::Remove(Iterator const& start, Iterator const& finish)
	{
		if (start.mOwner != this || finish.mOwner != this)
		{
			throw std::exception(iteratorFromOtherListExceptionText.c_str());
		}
		if (mSize > 0 && start.mDataIndex < finish.mDataIndex)
		{
			for (size_t i = start.mDataIndex; i != finish.mDataIndex; i++)
			{
				mArray[i].~T();
			}
			memmove(&(mArray[start.mDataIndex]), &(mArray[finish.mDataIndex]), (mSize - finish.mDataIndex) * sizeof(T));
			mSize -= (finish.mDataIndex - start.mDataIndex);
		}
	}

	template <typename T>
	void Vector<T>::Swap(Iterator const& element1, Iterator const& element2)
	{
		if (element1 == end() || element2 == end())
		{
			throw std::exception(cannotSwapEndExceptionText.c_str());
		}
		T buffer = std::move(*element1);
		*element1 = std::move(*element2);
		*element2 = std::move(buffer);
	}

	template <typename T>
	void Vector<T>::Shuffle()
	{
		for (size_t  i = 0; i < Size(); i++)
		{
			size_t randIndex = rand() % Size();
			T buffer = std::move(mArray[i]);
			mArray[i] = std::move(mArray[randIndex]);
			mArray[randIndex] = std::move(buffer);
		}
	}

	template <typename T>
	void Vector<T>::Reverse()
	{
		for (size_t i = 0; i < Size()/2; i++)
		{
			size_t mirroredIndex = Size() - 1 - i;
			T buffer = std::move(mArray[i]);
			mArray[i] = std::move(mArray[mirroredIndex]);
			mArray[mirroredIndex] = std::move(buffer);
		}
	}

	template<typename T>
	inline void Vector<T>::ShrinkToFit()
	{
		if (mSize != mCapacity)
		{
			if (mSize == 0)
			{
				free(mArray);
				mArray = nullptr;
				mCapacity = 0;
			}
			else
			{
				mCapacity = mSize;
				mArray= static_cast<T*>(realloc(mArray, mCapacity * sizeof(T)));
			}
		}
	}
}