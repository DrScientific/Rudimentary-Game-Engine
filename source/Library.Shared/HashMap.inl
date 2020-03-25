/// <summary>
/// The inline file containing the definition of each hash map function declared in HashMap.h.
/// </summary>

#include "HashMap.h"

namespace FIEAGameEngine
{
	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator & HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (*this == const_cast<HashMap*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		else
		{
			mListIterator = mOwner->mBucketVector[mDataIndex].begin();
			while (mDataIndex < mOwner->mBucketVector.Size())
			{
				if (mOwner->mBucketVector[mDataIndex].IsEmpty())
				{
					mDataIndex++;
				}
				else
				{
					mListIterator++;
					if (mListIterator == mOwner->mBucketVector[mDataIndex].end())
					{
						mListIterator = mOwner->mBucketVector[++mDataIndex].begin();
					}
					break;
				}
			}
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
		inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::Iterator::operator==(Iterator const & rhs) const
	{
		if ((mOwner == rhs.mOwner) && (mDataIndex >= mOwner->mBucketVector.Size()) && (rhs.mDataIndex >= mOwner->mBucketVector.Size()))
		{
			return true;
		}
		else
		{
			return (mOwner == rhs.mOwner) && (mDataIndex == rhs.mDataIndex) && (mListIterator == rhs.mListIterator);
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType & HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
	{
		if (*this == const_cast<HashMap*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return *mListIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType * HashMap<TKey, TData, HashFunctor>::Iterator::operator->() const
	{
		if (*this == const_cast<HashMap*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return &(*mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(HashMap const & owner, size_t index, typename ChainType::Iterator listIt) :
		mOwner(&owner), mDataIndex(index), mListIterator(listIt)
	{

	}
	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::const_Iterator::const_Iterator(Iterator const & it)
	{
		mOwner = it.mOwner;
		mDataIndex = it.mDataIndex;
		mListIterator = typename ChainType::const_Iterator(it.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator & HashMap<TKey, TData, HashFunctor>::const_Iterator::operator=(const Iterator & it)
	{
		mOwner = it.mOwner;
		mDataIndex = it.mDataIndex;
		mListIterator = typename ChainType::const_Iterator(it.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator & HashMap<TKey, TData, HashFunctor>::const_Iterator::operator++()
	{
		if (*this == mOwner->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		else
		{
			mListIterator = mOwner->mBucketVector[mDataIndex].cbegin();
			while (mDataIndex < mOwner->mBucketVector.Size())
			{
				if (mOwner->mBucketVector[mDataIndex].IsEmpty())
				{
					mDataIndex++;
				}
				else
				{
					mListIterator++;
					if (mListIterator == mOwner->mBucketVector[mDataIndex].cend())
					{
						mListIterator = mOwner->mBucketVector[++mDataIndex].cbegin();
					}
					break;
				}
			}
		}
		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator HashMap<TKey, TData, HashFunctor>::const_Iterator::operator++(int)
	{
		const_Iterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::const_Iterator::operator==(const_Iterator const & rhs) const
	{
		if ((mOwner == rhs.mOwner) && (mDataIndex >= mOwner->mBucketVector.Size()) && (rhs.mDataIndex >= mOwner->mBucketVector.Size()))
		{
			return true;
		}
		else
		{
			return (mOwner == rhs.mOwner) && (mDataIndex == rhs.mDataIndex) && (mListIterator == rhs.mListIterator);
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::const_Iterator::operator!=(const_Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType const & HashMap<TKey, TData, HashFunctor>::const_Iterator::operator*() const
	{
		if (*this == mOwner->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return *mListIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType const * HashMap<TKey, TData, HashFunctor>::const_Iterator::operator->() const
	{
		if (*this == mOwner->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return &(*mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::const_Iterator::const_Iterator(HashMap const & owner, size_t index, typename ChainType::const_Iterator listIt) :
	mOwner(&owner), mDataIndex(index), mListIterator(listIt)
	{
		
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::HashMap(size_t const & numBuckets) :
		mBucketVector(numBuckets)
	{
		mBucketVector.Resize(numBuckets);
	}
	
	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::HashMap(std::initializer_list<PairType> iList)
	{
		mBucketVector.Resize(iList.size());
		for (auto i : iList)
		{
			Insert(i);
		}
	}
	
	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::begin()
	{
		Iterator firstElementInHashMap;
		if (mBucketVector[0].IsEmpty())
		{
			firstElementInHashMap = ++(Iterator(*this, 0, mBucketVector[0].begin()));
		}
		else
		{
			firstElementInHashMap =  (Iterator(*this, 0, mBucketVector[0].begin()));
		}
		return firstElementInHashMap;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator HashMap<TKey, TData, HashFunctor>::begin() const
	{
		Iterator it = const_cast<HashMap*>(this)->begin();
		return const_Iterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::end()
	{
		return Iterator(*this, mBucketVector.Size(), ChainType::Iterator());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator HashMap<TKey, TData, HashFunctor>::end() const
	{
		Iterator it = const_cast<HashMap*>(this)->end();
		return const_Iterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator HashMap<TKey, TData, HashFunctor>::cbegin() const
	{
		Iterator it = const_cast<HashMap*>(this)->begin();
		return const_Iterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator HashMap<TKey, TData, HashFunctor>::cend() const
	{
		Iterator it = const_cast<HashMap*>(this)->end();
		return const_Iterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(TKey const & key)
	{
		Iterator foundIt = end();
		size_t hashedBucket = mHash(key) % mBucketVector.Size();
		for (ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
		{
			if ((*listIt).first == key)
			{
				foundIt = Iterator(*this, hashedBucket, listIt);
				break;
			}
		}
		return foundIt;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::const_Iterator HashMap<TKey, TData, HashFunctor>::Find(TKey const & key) const
	{
		const_Iterator foundIt = end();
		size_t hashedBucket = mHash(key) % mBucketVector.Size();
		for (ChainType::const_Iterator listIt = mBucketVector[hashedBucket].cbegin(); listIt != mBucketVector[hashedBucket].cend(); listIt++)
		{
			if ((*listIt).first == key)
			{
				foundIt = const_Iterator(*this, hashedBucket, listIt);
				break;
			}
		}
		return foundIt;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(PairType const & keyDataPair)
	{
		Iterator foundIt = end();
		size_t hashedBucket = mHash(keyDataPair.first) % mBucketVector.Size();
		ChainType::Iterator listIt = mBucketVector[hashedBucket].begin();
		for (; listIt != mBucketVector[hashedBucket].end(); listIt++)
		{
			if ((*listIt).first == keyDataPair.first)
			{
				foundIt = Iterator(*this, hashedBucket, listIt);
				break;
			}
		}
		if (listIt == mBucketVector[hashedBucket].end())
		{
			mNumKeyValuePairs++;
			listIt = mBucketVector[hashedBucket].PushBack(keyDataPair);
			foundIt = Iterator(*this, hashedBucket, listIt);
		}

		return foundIt;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(TKey const & key, TData const & data)
	{
		PairType keyDataPair(key, data);
		return Insert(keyDataPair);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & HashMap<TKey, TData, HashFunctor>::operator[](TKey const & key)
	{
		return Insert(key, TData())->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & HashMap<TKey, TData, HashFunctor>::At(TKey const & key)
	{

		Iterator foundIt = end();
		size_t hashedBucket = mHash(key) % mBucketVector.Size();
		for (ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
		{
			if ((*listIt).first == key)
			{
				foundIt = Iterator(*this, hashedBucket, listIt);
				break;
			}
		}

		if (foundIt == end())
		{
			throw std::exception(keyNotInHashMapException.c_str());
		}

		return foundIt->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData const & HashMap<TKey, TData, HashFunctor>::At(TKey const & key) const
	{

		const_Iterator foundIt = end();
		size_t hashedBucket = mHash(key) % mBucketVector.Size();
		for (ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
		{
			if ((*listIt).first == key)
			{
				foundIt = const_Iterator(*this, hashedBucket, listIt);
				break;
			}
		}

		if (foundIt == end())
		{
			throw std::exception(keyNotInHashMapException.c_str());
		}

		return foundIt->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::operator==(HashMap const & rhs)
	{
		return ((mNumKeyValuePairs == rhs.mNumKeyValuePairs) && (mBucketVector == rhs.mBucketVector));
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::operator!=(HashMap const & rhs)
	{
		return !(*this == rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void HashMap<TKey, TData, HashFunctor>::Remove(TKey const & key)
	{
		Iterator foundIt = end();
		size_t hashedBucket = mHash(key) % mBucketVector.Size();
		for (ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
		{
			if ((*listIt).first == key)
			{
				mBucketVector[hashedBucket].Remove(listIt);
				--mNumKeyValuePairs;
				break;
			}
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void HashMap<TKey, TData, HashFunctor>::Clear()
	{
		for (size_t i = 0; i != mBucketVector.Size(); i++)
		{
			mBucketVector[i].Clear();
		}
		mNumKeyValuePairs = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline size_t HashMap<TKey, TData, HashFunctor>::Size() const
	{
		return mNumKeyValuePairs;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline double HashMap<TKey, TData, HashFunctor>::LoadFactor() const
	{
		return (mNumKeyValuePairs/ 1.0*mBucketVector.Size());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::ContainsKey(TKey key) const
	{
		bool result = true;
		if (Find(key) == end())
		{
			result = false;
		}
		return result;
	}
}