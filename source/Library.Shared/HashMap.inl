/// <summary>
/// The inline file containing the definition of each hash map function declared in HashMap.h.
/// </summary>

#include "HashMap.h"


namespace FIEAGameEngine
{
	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator & HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}

		++mListIterator;
		while (mListIterator == mOwner->mBucketVector[mDataIndex].end())
		{
			++mDataIndex;
			if (mDataIndex >= mOwner->mBucketVector.Size())
			{
				mDataIndex = mOwner->mBucketVector.Size();
				mListIterator = typename ChainType::Iterator();
				break;
			}
			mListIterator = mOwner->mBucketVector[mDataIndex].begin();
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
		return (mOwner == rhs.mOwner) && (mDataIndex == rhs.mDataIndex) && (mListIterator == rhs.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType & HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<HashMap*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return *mListIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType * HashMap<TKey, TData, HashFunctor>::Iterator::operator->() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
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
	inline HashMap<TKey, TData, HashFunctor>::const_Iterator::const_Iterator(Iterator const & it) :
		mOwner(it.mOwner), mDataIndex(it.mDataIndex), mListIterator(typename ChainType::const_Iterator(it.mListIterator))
	{
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
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}

		++mListIterator;
		while (mListIterator == mOwner->mBucketVector[mDataIndex].cend())
		{
			++mDataIndex;
			if (mDataIndex >= mOwner->mBucketVector.Size())
			{
				mDataIndex = mOwner->mBucketVector.Size();
				mListIterator = typename ChainType::const_Iterator();
				break;
			}
			mListIterator = mOwner->mBucketVector[mDataIndex].cbegin();
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
		return (mOwner == rhs.mOwner) && (mDataIndex == rhs.mDataIndex) && (mListIterator == rhs.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::const_Iterator::operator!=(const_Iterator const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType const & HashMap<TKey, TData, HashFunctor>::const_Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == mOwner->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return *mListIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::PairType const * HashMap<TKey, TData, HashFunctor>::const_Iterator::operator->() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
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
		if (numBuckets == 0)
		{
			throw std::exception(hashMapMustHaveSizeGreaterThanZeroException.c_str());
		}
		mBucketVector.Resize(numBuckets);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::HashMap(std::initializer_list<PairType> iList) :
		mBucketVector(iList.size())
	{
		mBucketVector.Resize(iList.size());
		for (const auto& i : iList)
		{
			Insert(i);
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor>::HashMap(HashMap && other) :
		mBucketVector(std::move(other.mBucketVector)), mNumKeyValuePairs(other.mNumKeyValuePairs)
	{
		other.mNumKeyValuePairs = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline HashMap<TKey, TData, HashFunctor> & HashMap<TKey, TData, HashFunctor>::operator=(HashMap && rhs)
	{
		if (this != &rhs)
		{
			mBucketVector = std::move(rhs.mBucketVector);
			mNumKeyValuePairs = std::move(rhs.mNumKeyValuePairs);
			mHash = std::move(rhs.mHash);

			rhs.mNumKeyValuePairs = 0;
		}
		return *this;

	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::begin()
	{
		Iterator firstElementInHashMap = end();
		for (size_t i = 0; i < mBucketVector.Size(); i++)
		{
			if (!mBucketVector[i].IsEmpty())
			{
				firstElementInHashMap = Iterator(*this, i, mBucketVector[i].begin());
				break;
			}
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
		return Iterator(*this, mBucketVector.Size(), typename ChainType::Iterator());
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
		size_t hashedBucket = HashKey(key);
		for (typename ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
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
		size_t hashedBucket = HashKey(key);
		for (typename ChainType::const_Iterator listIt = mBucketVector[hashedBucket].cbegin(); listIt != mBucketVector[hashedBucket].cend(); listIt++)
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
	inline std::pair<bool, typename HashMap<TKey, TData, HashFunctor>::Iterator> HashMap<TKey, TData, HashFunctor>::Insert(PairType const & keyDataPair)
	{
		Iterator foundIt = end();
		bool alreadyInMap = true;
		size_t hashedBucket = HashKey(keyDataPair.first);
		typename ChainType::Iterator listIt = mBucketVector[hashedBucket].begin();
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
			alreadyInMap = false;
			mNumKeyValuePairs++;
			listIt = mBucketVector[hashedBucket].PushBack(keyDataPair);
			foundIt = Iterator(*this, hashedBucket, listIt);
		}

		return std::pair<bool, Iterator>(alreadyInMap, foundIt);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<bool, typename HashMap<TKey, TData, HashFunctor>::Iterator> HashMap<TKey, TData, HashFunctor>::Insert(TKey const & key, TData const & data)
	{
		PairType keyDataPair(key, data);
		return Insert(keyDataPair);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & HashMap<TKey, TData, HashFunctor>::operator[](TKey const & key)
	{
		return Insert(key, TData()).second->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & HashMap<TKey, TData, HashFunctor>::At(TKey const & key)
	{

		Iterator foundIt = Find(key);
		return foundIt->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData const & HashMap<TKey, TData, HashFunctor>::At(TKey const & key) const
	{

		const_Iterator foundIt = end();
		size_t hashedBucket = HashKey(key);
		for (typename ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
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
	inline bool HashMap<TKey, TData, HashFunctor>::operator==(HashMap const & rhs) const
	{
		bool result = false;
		if (mNumKeyValuePairs == rhs.mNumKeyValuePairs)
		{
			result = true;
			for (const_Iterator i = cbegin(); i != cend(); i++)
			{
				if ((*i) != *(Find((*i).first)))
				{
					result = false;
					break;
				}
			}
		}
		return result;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool HashMap<TKey, TData, HashFunctor>::operator!=(HashMap const & rhs) const
	{
		return !(*this == rhs);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void HashMap<TKey, TData, HashFunctor>::Remove(TKey const & key)
	{
		Iterator foundIt = end();
		size_t hashedBucket = HashKey(key);
		for (typename ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
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
		return (mNumKeyValuePairs / 1.0*mBucketVector.Size());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void HashMap<TKey, TData, HashFunctor>::Resize(size_t numBuckets)
	{
		HashMap map(numBuckets);

		for (const auto& item : *this)
		{
			map.Insert(item);
		}

		*this = std::move(map);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<bool, TData*> HashMap<TKey, TData, HashFunctor>::ContainsKey(TKey const & key) const
	{
		std::pair<bool, TData*> result = std::pair<bool, TData*>(false, nullptr);

		const_Iterator foundIt = Find(key);
		if (foundIt != cend())
		{
			result.first = true;
			result.second = const_cast<TData*>(&(*foundIt).second);
		}
		return result;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline size_t HashMap<TKey, TData, HashFunctor>::HashKey(TKey const & key) const
	{
		return mHash(key) % mBucketVector.Size();
	}
}