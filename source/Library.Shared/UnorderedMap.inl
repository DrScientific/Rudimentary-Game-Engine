/// <summary>
/// The inline file containing the definition of each unordered  map function declared in UnorderedMap.h.
/// </summary>

#include "UnorderedMap.h"


namespace FIEAGameEngine
{
	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::Iterator & UnorderedMap<TKey, TData, HashFunctor>::Iterator::operator++()
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
	inline typename UnorderedMap<TKey, TData, HashFunctor>::Iterator UnorderedMap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline bool UnorderedMap<TKey, TData, HashFunctor>::Iterator::operator==(Iterator const& other) const
	{
		return (mOwner == other.mOwner) && (mDataIndex == other.mDataIndex) && (mListIterator == other.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool UnorderedMap<TKey, TData, HashFunctor>::Iterator::operator!=(Iterator const& other) const
	{
		return !(*this == other);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::PairType & UnorderedMap<TKey, TData, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<UnorderedMap*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratePastLastElementException.c_str());
		}
		return *mListIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::PairType * UnorderedMap<TKey, TData, HashFunctor>::Iterator::operator->() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<UnorderedMap*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratePastLastElementException.c_str());
		}
		return &(*mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor>::Iterator::Iterator(UnorderedMap const& owner, size_t index, typename ChainType::Iterator listIt) :
		mOwner(&owner), mDataIndex(index), mListIterator(listIt)
	{

	}
	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::ConstIterator(Iterator const& it) :
		mOwner(it.mOwner), mDataIndex(it.mDataIndex), mListIterator(typename ChainType::ConstIterator(it.mListIterator))
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator & UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator=(const Iterator & it)
	{
		mOwner = it.mOwner;
		mDataIndex = it.mDataIndex;
		mListIterator = typename ChainType::ConstIterator(it.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator & UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator++()
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
				mListIterator = typename ChainType::ConstIterator();
				break;
			}
			mListIterator = mOwner->mBucketVector[mDataIndex].cbegin();
		}

		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator++(int)
	{
		ConstIterator iteratorBeforeIncrement = *this;
		operator++();
		return iteratorBeforeIncrement;
	}


	template<typename TKey, typename TData, typename HashFunctor>
	inline bool UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator==(ConstIterator const& other) const
	{
		return (mOwner == other.mOwner) && (mDataIndex == other.mDataIndex) && (mListIterator == other.mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator!=(ConstIterator const& other) const
	{
		return !(*this == other);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::PairType const& UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == mOwner->end())
		{
			throw std::exception(attemptToIteratePastLastElementException.c_str());
		}
		return *mListIterator;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::PairType const* UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::operator->() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == mOwner->end())
		{
			throw std::exception(attemptToIteratePastLastElementException.c_str());
		}
		return &(*mListIterator);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor>::ConstIterator::ConstIterator(UnorderedMap const& owner, size_t index, typename ChainType::ConstIterator listIt) :
		mOwner(&owner), mDataIndex(index), mListIterator(listIt)
	{

	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor>::UnorderedMap(size_t const& numBuckets) :
		mBucketVector(numBuckets)
	{
		if (numBuckets == 0)
		{
			throw std::exception(unorderedMapMustHaveSizeGreaterThanZeroException.c_str());
		}
		mBucketVector.Resize(numBuckets);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor>::UnorderedMap(std::initializer_list<PairType> iList) :
		mBucketVector(iList.size())
	{
		mBucketVector.Resize(iList.size());
		for (const auto& i : iList)
		{
			Insert(i);
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor>::UnorderedMap(UnorderedMap && other) :
		mBucketVector(std::move(other.mBucketVector)), mNumKeyValuePairs(other.mNumKeyValuePairs)
	{
		other.mNumKeyValuePairs = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline UnorderedMap<TKey, TData, HashFunctor> & UnorderedMap<TKey, TData, HashFunctor>::operator=(UnorderedMap && other)
	{
		if (this != &other)
		{
			mBucketVector = std::move(other.mBucketVector);
			mNumKeyValuePairs = std::move(other.mNumKeyValuePairs);
			mHash = std::move(other.mHash);

			other.mNumKeyValuePairs = 0;
		}
		return *this;

	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::Iterator UnorderedMap<TKey, TData, HashFunctor>::begin()
	{
		Iterator firstElementInUnorderedMap = end();
		for (size_t i = 0; i < mBucketVector.Size(); i++)
		{
			if (!mBucketVector[i].IsEmpty())
			{
				firstElementInUnorderedMap = Iterator(*this, i, mBucketVector[i].begin());
				break;
			}
		}
		return firstElementInUnorderedMap;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator UnorderedMap<TKey, TData, HashFunctor>::begin() const
	{
		Iterator it = const_cast<UnorderedMap*>(this)->begin();
		return ConstIterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::Iterator UnorderedMap<TKey, TData, HashFunctor>::end()
	{
		return Iterator(*this, mBucketVector.Size(), typename ChainType::Iterator());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator UnorderedMap<TKey, TData, HashFunctor>::end() const
	{
		Iterator it = const_cast<UnorderedMap*>(this)->end();
		return ConstIterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator UnorderedMap<TKey, TData, HashFunctor>::cbegin() const
	{
		Iterator it = const_cast<UnorderedMap*>(this)->begin();
		return ConstIterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator UnorderedMap<TKey, TData, HashFunctor>::cend() const
	{
		Iterator it = const_cast<UnorderedMap*>(this)->end();
		return ConstIterator(it);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline typename UnorderedMap<TKey, TData, HashFunctor>::Iterator UnorderedMap<TKey, TData, HashFunctor>::Find(TKey const& key)
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
	inline typename UnorderedMap<TKey, TData, HashFunctor>::ConstIterator UnorderedMap<TKey, TData, HashFunctor>::Find(TKey const& key) const
	{
		ConstIterator foundIt = end();
		size_t hashedBucket = HashKey(key);
		for (typename ChainType::ConstIterator listIt = mBucketVector[hashedBucket].cbegin(); listIt != mBucketVector[hashedBucket].cend(); listIt++)
		{
			if ((*listIt).first == key)
			{
				foundIt = ConstIterator(*this, hashedBucket, listIt);
				break;
			}
		}
		return foundIt;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<bool, typename UnorderedMap<TKey, TData, HashFunctor>::Iterator> UnorderedMap<TKey, TData, HashFunctor>::Insert(PairType const& keyDataPair)
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
	inline std::pair<bool, typename UnorderedMap<TKey, TData, HashFunctor>::Iterator> UnorderedMap<TKey, TData, HashFunctor>::Insert(TKey const& key, TData const& data)
	{
		PairType keyDataPair(key, data);
		return Insert(keyDataPair);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & UnorderedMap<TKey, TData, HashFunctor>::operator[](TKey const& key)
	{
		return Insert(key, TData()).second->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData & UnorderedMap<TKey, TData, HashFunctor>::At(TKey const& key)
	{

		Iterator foundIt = Find(key);
		return foundIt->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline TData const& UnorderedMap<TKey, TData, HashFunctor>::At(TKey const& key) const
	{

		ConstIterator foundIt = end();
		size_t hashedBucket = HashKey(key);
		for (typename ChainType::Iterator listIt = mBucketVector[hashedBucket].begin(); listIt != mBucketVector[hashedBucket].end(); listIt++)
		{
			if ((*listIt).first == key)
			{
				foundIt = ConstIterator(*this, hashedBucket, listIt);
				break;
			}
		}

		if (foundIt == end())
		{
			throw std::exception(keyNotInUnorderedMapException.c_str());
		}

		return foundIt->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline bool UnorderedMap<TKey, TData, HashFunctor>::operator==(UnorderedMap const& other) const
	{
		bool result = false;
		if (mNumKeyValuePairs == other.mNumKeyValuePairs)
		{
			result = true;
			for (ConstIterator i = cbegin(); i != cend(); i++)
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
	inline bool UnorderedMap<TKey, TData, HashFunctor>::operator!=(UnorderedMap const& other) const
	{
		return !(*this == other);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void UnorderedMap<TKey, TData, HashFunctor>::Remove(TKey const& key)
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
	inline void UnorderedMap<TKey, TData, HashFunctor>::Clear()
	{
		for (size_t i = 0; i != mBucketVector.Size(); i++)
		{
			mBucketVector[i].Clear();
		}
		mNumKeyValuePairs = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline size_t UnorderedMap<TKey, TData, HashFunctor>::Size() const
	{
		return mNumKeyValuePairs;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline double UnorderedMap<TKey, TData, HashFunctor>::LoadFactor() const
	{
		return (mNumKeyValuePairs / 1.0*mBucketVector.Size());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline void UnorderedMap<TKey, TData, HashFunctor>::Resize(size_t numBuckets)
	{
		UnorderedMap map(numBuckets);

		for (const auto& item : *this)
		{
			map.Insert(item);
		}

		*this = std::move(map);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline std::pair<bool, TData*> UnorderedMap<TKey, TData, HashFunctor>::ContainsKey(TKey const& key) const
	{
		std::pair<bool, TData*> result = std::pair<bool, TData*>(false, nullptr);

		ConstIterator foundIt = Find(key);
		if (foundIt != cend())
		{
			result.first = true;
			result.second = const_cast<TData*>(&(*foundIt).second);
		}
		return result;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	inline size_t UnorderedMap<TKey, TData, HashFunctor>::HashKey(TKey const& key) const
	{
		return mHash(key) % mBucketVector.Size();
	}
}