#pragma once

/// <summary>
/// The file containing all of the declarations of the unordered map class.
/// </summary>

#include <string>
#include <exception>
#include <initializer_list>
#include "SList.h"
#include "Vector.h"
#include "DefaultHashFunctor.h"

namespace FIEAGameEngine
{
	/// <summary>
	/// 
	/// </summary>
	template <typename TKey, typename TData, typename HashFunctor = DefaultHashFunctor<TKey>>
	class UnorderedMap final
	{
	public:
		using PairType = std::pair<TKey const, TData>;
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;
		/// <summary>
		/// An iterator that contains an index into a unordered map. Any data dereferenced through a Iterator is not const. See ConstIterator.
		/// </summary>
		class Iterator
		{
		public:

			/// <summary>
			/// Default constructor for Iterator.
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Default copy constructor for Iterator
			/// </summary>
			/// <param name="">Iterator to copy</param>
			Iterator(Iterator const&) = default;

			/// <summary>
			/// Default assignment operator for Iterator
			/// </summary>
			Iterator& operator= (const Iterator&) = default;

			/// <summary>
			/// Default destructor for Iterator
			/// </summary>
			~Iterator() = default;

			/// <summary>
			/// Preincrement operation. Increments index pointed to by iterator by 1.
			/// </summary>
			/// <returns></returns>
			Iterator& operator++();

			/// <summary>
			/// Postincrement operation. Increments index pointed to by iterator by 1.
			/// </summary>
			Iterator operator++(int);

			/// <summary>
			/// Checks that two Iterators are equal.
			/// </summary>
			/// <param name="other">Iterator to compare with.</param>
			/// <returns>Whether the Iterators are equal.</returns>
			bool operator==(Iterator const& other) const;

			/// <summary>
			/// Checks that two Iterators are not equal.
			/// </summary>
			/// <param name="other">Iterator to compare with.</param>
			/// <returns>Whether the Iterators are not equal.</returns>
			bool operator!=(Iterator const& other) const;

			/// <summary>
			/// Dereferences the Iterator.
			/// </summary>
			/// <returns>The data pointed to by the Iterator.</returns>
			PairType& operator*() const;

			/// <summary>
			/// Returns the address of the dereferenced Iterator.
			/// </summary>
			/// <returns>The address of the data pointed to by the Iterator.</returns>
			PairType * operator->() const;


		private:
			/// <summary>
			/// Constructor for Iterator taking in a UnorderedMap owner and data.
			/// </summary>
			/// <param name="owner">List owning the cIterator.</param>
			/// <param name="index">Index in array iterator will point to.</param>
			Iterator(UnorderedMap const& owner, size_t index = 0, typename ChainType::Iterator listIt = owner.mBucketVector[index].begin());

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			const UnorderedMap* mOwner = nullptr;

			/// <summary>
			/// Index relative to start of array where value is stored.
			/// </summary>
			size_t mDataIndex = 0;

			/// <summary>
			/// An SList iterator pointing to a specific element in a chain in a bucket.
			/// </summary>
			typename ChainType::Iterator mListIterator;

			friend class ConstIterator;
			friend UnorderedMap;
		};

		/// <summary>
		/// An iterator that contains an index into a unordered map. Any data dereferenced through a Iterator is not const. See ConstIterator.
		/// </summary>
		class ConstIterator
		{
		public:

			/// <summary>
			/// Default constructor for ConstIterator
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Default copy constructor for ConstIterator
			/// </summary>
			/// <param name="">ConstIterator to copy</param>
			ConstIterator(const ConstIterator&) = default;

			/// <summary>
			/// Default assignment operator for ConstIterator
			/// </summary>
			ConstIterator& operator= (const ConstIterator&) = default;

			/// <summary>
			/// Default destructor for ConstIterator
			/// </summary>
			~ConstIterator() = default;

			/// <summary>
			/// Constructs a ConstIterator from an Iterator.
			/// </summary>
			/// <param name="it">Iterator to create ConstIterator from</param>
			ConstIterator(Iterator const& it);

			/// <summary>
			/// Assigns an ConstIterator to an Iterator assignment operator for ConstIterator
			/// </summary>
			ConstIterator& operator= (const Iterator& it);

			/// <summary>
			/// Preincrement operation. Increments index pointed to by iterator by 1.
			/// </summary>
			/// <returns></returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postincrement operation.  Increments index pointed to by iterator by 1.
			/// </summary>
			ConstIterator operator++(int);

			/// <summary>
			/// Checks that two const_Iterators are equal.
			/// </summary>
			/// <param name="other">ConstIterator to compare with.</param>
			/// <returns>Whether the const_Iterators are equal.</returns>
			bool operator==(ConstIterator const& other) const;

			/// <summary>
			/// Checks that two const_Iterators are not equal.
			/// </summary>
			/// <param name="other">ConstIterator to compare with.</param>
			/// <returns>Whether the const_Iterators are not equal.</returns>
			bool operator!=(ConstIterator const& other) const;

			/// <summary>
			/// Dereferences the ConstIterator.
			/// </summary>
			/// <returns>The const data pointed to by the ConstIterator.</returns>
			PairType const& operator*() const;

			/// <summary>
			/// Returns the address of the dereferenced ConstIterator.
			/// </summary>
			/// <returns>The address of the data pointed to by the ConstIterator.</returns>
			PairType const* operator->() const;

		private:
			/// <summary>
			/// Constructor for ConstIterator taking in a list owner and data.
			/// </summary>
			/// <param name="owner">List owning the ConstIterator.</param>
			/// <param name="data">Data pointed to by the ConstIterator.</param>
			ConstIterator(UnorderedMap const& owner, size_t index = 0, typename ChainType::ConstIterator listIt = owner.mBucketVector[index].cbegin());

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			const UnorderedMap* mOwner = nullptr;

			/// <summary>
			/// Index relative to start of array where value is stored.
			/// </summary>
			size_t mDataIndex = 0;

			/// <summary>
			/// An SList ConstIterator pointing to a specific element in a chain in a bucket.
			/// </summary>
			typename ChainType::ConstIterator mListIterator;

			friend UnorderedMap;
		};

		/// <summary>
		/// Default constructor.
		/// </summary>
		explicit UnorderedMap(size_t const& numBuckets = 256);

		/// <summary>
		/// Initializer list constructor.
		/// Takes each element in the initializer list and pushes it to the back of the Vector.
		/// This will result in an Vector where the left most element is the front of the list, and the right most element is the back of the list.
		/// </summary>
		/// <param name="iList">The initializer list we are creating a list from.</param>
		UnorderedMap(std::initializer_list<PairType> iList);

		/// <summary>
		/// Copy constructor.
		/// Calls the assignment operator in order to deep copy the other list.
		/// </summary>
		/// <param name="other">The UnorderedMap we are creating a deep copy of.</param>
		UnorderedMap(UnorderedMap const& other) = default;

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The UnorderedMap we are moving.</param>
		UnorderedMap(UnorderedMap && other);

		/// <summary>
		/// Assignment Operator.
		/// Makes the left hand side of the assignment a deep copy of the right hand side of the assignment. 
		/// </summary>
		/// <param name="other">The list on the right hand side of the expression we are setting our UnorderedMap equal to.</param>
		/// <returns>A reference to the UnorderedMap on the left hand side of the operator.</returns>
		UnorderedMap& operator=(UnorderedMap const& other) = default;

		/// <summary>
		/// Move Assignment Operator.
		/// </summary>
		/// <param name="other">The list on the right hand side of the expression we are setting our UnorderedMap equal to.</param>
		/// <returns>A reference to the UnorderedMap on the left hand side of the operator.</returns>
		UnorderedMap& operator=(UnorderedMap && other);

		/// <summary>
		/// Deletes the unordered map.
		/// </summary>
		~UnorderedMap() = default;

		/// <summary>
		/// Returns an iterator pointing to the first element of the UnorderedMap THAT HAS BEEN INITIALIZED.
		/// Note the UnorderedMap is unordered.
		/// </summary>
		/// <returns>Iterator pointing to the first element of the UnorderedMap.</returns>
		Iterator begin();

		/// <summary>
		/// Returns a const_iterator pointing to the first element of the UnorderedMap THAT HAS BEEN INITIALIZED.
		/// Note the UnorderedMap is unordered.
		/// /// </summary>
		/// <returns>const_iterator pointing to the first element of the UnorderedMap.</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns an iterator pointing to element past the last element of the UnorderedMap. This is out of bounds of the UnorderedMap and will throw an exception if dereferenced.
		/// </summary>
		/// <returns>An iterator pointing to element past the last element of the UnorderedMap</returns>
		Iterator end();

		/// <summary>
		/// Returns a const_iterator pointing to element past the last element of the UnorderedMap. This is out of bounds of the UnorderedMap and will throw an exception if dereferenced.
		/// </summary>
		/// <returns>A const_iterator pointing to element past the last element of the UnorderedMap.</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns a const_iterator pointing to the first element of the UnorderedMap THAT HAS BEEN INITIALIZED.
		/// Note the UnorderedMap is unordered.
		/// /// </summary>
		/// <returns>const_iterator pointing to the first element of the UnorderedMap.</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns a const_iterator pointing to element past the last element of the UnorderedMap. This is out of bounds of the UnorderedMap and will throw an exception if dereferenced.
		/// </summary>
		/// <returns>A const_iterator pointing to element past the last element of the UnorderedMap.</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Returns an Iterator to the data at the corresponding key if it exists. Otherwise returns an Iterator with a null owner.
		/// </summary>
		/// <param name="key">The key to search the UnorderedMap for.</param>
		/// <returns>An Iterator to the data at the corresponding key if it exists. Otherwise returns an Iterator with a null owner.</returns>
		Iterator Find(TKey const& key);

		/// <summary>
		/// Returns a ConstIterator to the data at the corresponding key if it exists. Otherwise returns a ConstIterator with a null owner.
		/// </summary>
		/// <param name="key">The key to search the UnorderedMap for.</param>
		/// <returns>An const_terator to the data at the corresponding key if it exists. Otherwise returns an ConstIterator with a null owner.</returns>
		ConstIterator Find(TKey const& key) const;

		/// <summary>
		/// Inserts the pair at the index mapped to by the hashed key. If the pair already exists then an Iterator to the pair is returned.
		/// </summary>
		/// <param name="keyDataPair">A key-data pair which will hash key to find an empty index and store the key-data pair at that location. </param>
		/// <returns>An Iterator to the inserted key-data pair.</returns>
		std::pair <bool, Iterator> Insert(PairType const& keyDataPair);

		/// <summary>
		/// Inserts the pair at the index mapped to by the hashed key. If the pair already exists then an Iterator to the pair is returned.
		/// </summary>
		/// <param name="key">A key which will be hashed to find an empty index and store the key-data pair at that location.</param>
		/// <param name="data">Data to store at the hashed key index.</param>
		/// <returns>An Iterator to the inserted key-data pair.</returns>
		std::pair <bool, Iterator>  Insert(TKey const& key, TData const& data);

		/// <summary>
		/// Returns the data stored in the key-data pair stored in the UnorderedMap at the passed in key. If no key-data pair exists inserts a key-data pair into the UnorderedMap where the key is th passed in key and the data is the default constructor of the data type.
		/// </summary>
		/// <param name="key">The key to search the UnorderedMap for.</param>
		/// <returns>The data stored in the key-data pair stored in the UnorderedMap at the passed in key. If no key-data pair exists inserts a key-data pair into the UnorderedMap where the key is th passed in key and the data is the default constructor of the data type.</returns>
		TData & operator[] (TKey const& key);

		/// <summary>
		/// Returns the data stored in the key-data pair stored in the UnorderedMap at the passed in key. If no key-data pair throw an exception
		/// </summary>
		/// <param name="key">The key to search the UnorderedMap for.</param>
		/// <returns>The data stored in the key-data pair stored in the UnorderedMap at the passed in key. If no key-data pair throw an exception</returns>
		TData & At(TKey const& key);

		/// <summary>
		/// Returns a const reference to data stored in the key-data pair stored in the UnorderedMap at the passed in key. If no key-data pair throw an exception
		/// </summary>
		/// <param name="key">The key to search the UnorderedMap for.</param>
		/// <returns>A const reference to data stored in the key-data pair stored in the UnorderedMap at the passed in key. If no key-data pair throw an exception</returns>
		TData const& At(TKey const& key) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator==(UnorderedMap const& other) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator!=(UnorderedMap const& other) const;

		/// <summary>
		/// Removes the key-data pair stored at the index mapped to by the hashed key. If the key-data pair is not in the UnorderedMap do nothing.
		/// </summary>
		/// <param name="key">The key to search the UnorderedMap for.</param>
		void Remove(TKey const& key);

		/// <summary>
		/// Removes any vlaues in any buckets
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the number of elements populating the UnorderedMap.
		/// </summary>
		/// <returns>The number of elements populating the UnorderedMap.</returns>
		size_t Size() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		double LoadFactor() const;

		/// <summary>
		/// Resizes the unordered map to a new number of buckets. Remaps all values when called.
		/// </summary>
		/// <param name="numBuckets">New number of buckets</param>
		void Resize(size_t numBuckets);

		/// <summary>
		/// Returns true if the key is in the UnorderedMap and false otherwise Returns data at key as out parameter if it exists.
		/// </summary>
		/// <param name="key">The key we are searching for within the UnorderedMap.</param>
		/// <param name="data">Out param of value at key.</param>
		/// <returns>True if the key is in the UnorderedMap and false otherwise.</returns>
		std::pair<bool, TData*> ContainsKey(TKey const& key) const;


	private:

		/// <summary>
		/// Vector where each index stores an SList.
		/// </summary>
		BucketType mBucketVector;

		/// <summary>
		/// The number of of key-value pairs in the list.
		/// </summary>
		size_t mNumKeyValuePairs = 0;

		/// <summary>
		/// 
		/// </summary>
		HashFunctor mHash;

		/// <summary>
		/// 
		/// </summary>
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		size_t HashKey(TKey const& key) const;

		/// <summary>
		/// 
		/// </summary>
		inline static const std::string attemptToIteratePastLastElementException = "Attempted to increment an iterator past end of the unordered map.\n";

		/// <summary>
		/// 
		/// </summary>
		inline static const std::string keyNotInUnorderedMapException = "Key searched for was not found in unordered map.\n";

		/// <summary>
		/// 
		/// </summary>
		inline static const std::string unorderedMapMustHaveSizeGreaterThanZeroException = "Unordered map must have bucket size greater than 0.\n";

		/// <summary>
		/// 
		/// </summary>
		inline static const std::string ownerIsNullException = "Iterator owner is null and cannot be dereferenced.\n";

	};


};
#include "UnorderedMap.inl"