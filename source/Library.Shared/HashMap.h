#pragma once

/// <summary>
/// The file containing all of the declarations of the hash map class.
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
	class HashMap final
	{
	public:
		using PairType = std::pair<TKey const, TData>;
		using ChainType = SList<PairType>;
		using BucketType = Vector<ChainType>;
		/// <summary>
		/// An iterator that contains an index into a hash map. Any data dereferenced through a Iterator is not const. See const_Iterator.
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
			Iterator(Iterator const &) = default;

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
			/// <param name="rhs">Iterator to compare with.</param>
			/// <returns>Whether the Iterators are equal.</returns>
			bool operator==(Iterator const & rhs) const;

			/// <summary>
			/// Checks that two Iterators are not equal.
			/// </summary>
			/// <param name="rhs">Iterator to compare with.</param>
			/// <returns>Whether the Iterators are not equal.</returns>
			bool operator!=(Iterator const & rhs) const;

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
			/// Constructor for Iterator taking in a HashMap owner and data.
			/// </summary>
			/// <param name="owner">List owning the cIterator.</param>
			/// <param name="index">Index in array iterator will point to.</param>
			Iterator(HashMap const & owner, size_t index = 0, typename ChainType::Iterator listIt = owner.mBucketVector[index].begin());

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			const HashMap* mOwner;

			/// <summary>
			/// Index relative to start of array where value is stored.
			/// </summary>
			size_t mDataIndex = 0;

			/// <summary>
			/// An SList iterator pointing to a specific element in a chain in a bucket.
			/// </summary>
			typename ChainType::Iterator mListIterator;

			friend class const_Iterator;
			friend class HashMap<TKey, TData, HashFunctor>;
		};

		/// <summary>
		/// An iterator that contains an index into a hash map. Any data dereferenced through a Iterator is not const. See const_Iterator.
		/// </summary>
		class const_Iterator
		{
		public:

			/// <summary>
			/// Default constructor for const_Iterator
			/// </summary>
			const_Iterator() = default;

			/// <summary>
			/// Default copy constructor for const_Iterator
			/// </summary>
			/// <param name="">const_Iterator to copy</param>
			const_Iterator(const const_Iterator&) = default;

			/// <summary>
			/// Default assignment operator for const_Iterator
			/// </summary>
			const_Iterator& operator= (const const_Iterator&) = default;

			/// <summary>
			/// Default destructor for const_Iterator
			/// </summary>
			~const_Iterator() = default;

			/// <summary>
			/// Constructs a const_Iterator from an Iterator.
			/// </summary>
			/// <param name="it">Iterator to create const_Iterator from</param>
			const_Iterator(Iterator const & it);

			/// <summary>
			/// Assigns an const_Iterator to an Iterator assignment operator for const_Iterator
			/// </summary>
			const_Iterator& operator= (const Iterator& it);

			/// <summary>
			/// Preincrement operation. Increments index pointed to by iterator by 1.
			/// </summary>
			/// <returns></returns>
			const_Iterator& operator++();

			/// <summary>
			/// Postincrement operation.  Increments index pointed to by iterator by 1.
			/// </summary>
			const_Iterator operator++(int);

			/// <summary>
			/// Checks that two const_Iterators are equal.
			/// </summary>
			/// <param name="rhs">const_Iterator to compare with.</param>
			/// <returns>Whether the const_Iterators are equal.</returns>
			bool operator==(const_Iterator const & rhs) const;

			/// <summary>
			/// Checks that two const_Iterators are not equal.
			/// </summary>
			/// <param name="rhs">const_Iterator to compare with.</param>
			/// <returns>Whether the const_Iterators are not equal.</returns>
			bool operator!=(const_Iterator const & rhs) const;

			/// <summary>
			/// Dereferences the const_Iterator.
			/// </summary>
			/// <returns>The const data pointed to by the const_Iterator.</returns>
			PairType const & operator*() const;

			/// <summary>
			/// Returns the address of the dereferenced const_Iterator.
			/// </summary>
			/// <returns>The address of the data pointed to by the const_Iterator.</returns>
			PairType const * operator->() const;

		private:
			/// <summary>
			/// Constructor for const_Iterator taking in a list owner and data.
			/// </summary>
			/// <param name="owner">List owning the const_Iterator.</param>
			/// <param name="data">Data pointed to by the const_Iterator.</param>
			const_Iterator(HashMap const & owner, size_t index = 0, typename ChainType::const_Iterator listIt = owner.mBucketVector[index].cbegin());
			
			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			const HashMap* mOwner;

			/// <summary>
			/// Index relative to start of array where value is stored.
			/// </summary>
			size_t mDataIndex = 0;  

			/// <summary>
			/// An SList const_Iterator pointing to a specific element in a chain in a bucket.
			/// </summary>
			typename ChainType::const_Iterator mListIterator;

			friend class HashMap<TKey, TData, HashFunctor>;
		};

		/// <summary>
		/// Default constructor.
		/// </summary>
		HashMap(size_t const & numBuckets = 2);

		/// <summary>
		/// Initializer list constructor.
		/// Takes each element in the initializer list and pushes it to the back of the Vector.
		/// This will result in an Vector where the left most element is the front of the list, and the right most element is the back of the list.
		/// </summary>
		/// <param name="iList">The initializer list we are creating a list from.</param>
		HashMap(std::initializer_list<PairType> iList);

		/// <summary>
		/// Copy constructor.
		/// Calls the assignment operator in order to deep copy the other list.
		/// </summary>
		/// <param name="other">The HashMap we are creating a deep copy of.</param>
		HashMap(HashMap const & other) = default;

		/// <summary>
		/// Assignment Operator.
		/// Makes the left hand side of the assignment a deep copy of the right hand side of the assignment. 
		/// </summary>
		/// <param name="rhs">The list on the right hand side of the expression we are setting our HashMap equal to.</param>
		/// <returns>A reference to the HashMap on the left hand side of the operator.</returns>
		HashMap& operator=(HashMap const & rhs) = default;

		/// <summary>
		/// Deletes the hash map.
		/// </summary>
		~HashMap() = default;

		/// <summary>
		/// Returns an iterator pointing to the first element of the HashMap THAT HAS BEEN INITIALIZED.
		/// Note the HashMap is unordered.
		/// </summary>
		/// <returns>Iterator pointing to the first element of the HashMap.</returns>
		Iterator begin();

		/// <summary>
		/// Returns a const_iterator pointing to the first element of the HashMap THAT HAS BEEN INITIALIZED.
		/// Note the HashMap is unordered.
		/// /// </summary>
		/// <returns>const_iterator pointing to the first element of the HashMap.</returns>
		const_Iterator begin() const;

		/// <summary>
		/// Returns an iterator pointing to element past the last element of the HashMap. This is out of bounds of the HashMap and will throw an exception if dereferenced.
		/// </summary>
		/// <returns>An iterator pointing to element past the last element of the HashMap</returns>
		Iterator end();

		/// <summary>
		/// Returns a const_iterator pointing to element past the last element of the HashMap. This is out of bounds of the HashMap and will throw an exception if dereferenced.
		/// </summary>
		/// <returns>A const_iterator pointing to element past the last element of the HashMap.</returns>
		const_Iterator end() const;

		/// <summary>
		/// Returns a const_iterator pointing to the first element of the HashMap THAT HAS BEEN INITIALIZED.
		/// Note the HashMap is unordered.
		/// /// </summary>
		/// <returns>const_iterator pointing to the first element of the HashMap.</returns>
		const_Iterator cbegin() const;

		/// <summary>
		/// Returns a const_iterator pointing to element past the last element of the HashMap. This is out of bounds of the HashMap and will throw an exception if dereferenced.
		/// </summary>
		/// <returns>A const_iterator pointing to element past the last element of the HashMap.</returns>
		const_Iterator cend() const;

		/// <summary>
		/// Returns an Iterator to the data at the corresponding key if it exists. Otherwise returns an Iterator with a null owner.
		/// </summary>
		/// <param name="key">The key to search the HashMap for.</param>
		/// <returns>An Iterator to the data at the corresponding key if it exists. Otherwise returns an Iterator with a null owner.</returns>
		Iterator Find(TKey const & key);

		/// <summary>
		/// Returns a const_Iterator to the data at the corresponding key if it exists. Otherwise returns a const_Iterator with a null owner.
		/// </summary>
		/// <param name="key">The key to search the HashMap for.</param>
		/// <returns>An const_terator to the data at the corresponding key if it exists. Otherwise returns an const_Iterator with a null owner.</returns>
		const_Iterator Find(TKey const & key) const;

		/// <summary>
		/// Inserts the pair at the index mapped to by the hashed key. If the pair already exists then an Iterator to the pair is returned.
		/// </summary>
		/// <param name="keyDataPair">A key-data pair which will hash key to find an empty index and store the key-data pair at that location. </param>
		/// <returns>An Iterator to the inserted key-data pair.</returns>
		Iterator Insert(PairType const & keyDataPair);

		/// <summary>
		/// Inserts the pair at the index mapped to by the hashed key. If the pair already exists then an Iterator to the pair is returned.
		/// </summary>
		/// <param name="key">A key which will be hashed to find an empty index and store the key-data pair at that location.</param>
		/// <param name="data">Data to store at the hashed key index.</param>
		/// <returns>An Iterator to the inserted key-data pair.</returns>
		Iterator Insert(TKey const & key, TData const & data);

		/// <summary>
		/// Returns the data stored in the key-data pair stored in the HashMap at the passed in key. If no key-data pair exists inserts a key-data pair into the HashMap where the key is th passed in key and the data is the default constructor of the data type.
		/// </summary>
		/// <param name="key">The key to search the HashMap for.</param>
		/// <returns>The data stored in the key-data pair stored in the HashMap at the passed in key. If no key-data pair exists inserts a key-data pair into the HashMap where the key is th passed in key and the data is the default constructor of the data type.</returns>
		TData & operator[] (TKey const & key);

		/// <summary>
		/// Returns the data stored in the key-data pair stored in the HashMap at the passed in key. If no key-data pair throw an exception
		/// </summary>
		/// <param name="key">The key to search the HashMap for.</param>
		/// <returns>The data stored in the key-data pair stored in the HashMap at the passed in key. If no key-data pair throw an exception</returns>
		TData & At (TKey const & key);

		/// <summary>
		/// Returns a const reference to data stored in the key-data pair stored in the HashMap at the passed in key. If no key-data pair throw an exception
		/// </summary>
		/// <param name="key">The key to search the HashMap for.</param>
		/// <returns>A const reference to data stored in the key-data pair stored in the HashMap at the passed in key. If no key-data pair throw an exception</returns>
		TData const & At(TKey const & key) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(HashMap const & rhs);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(HashMap const & rhs);

		/// <summary>
		/// Removes the key-data pair stored at the index mapped to by the hashed key. If the key-data pair is not in the HashMap do nothing.
		/// </summary>
		/// <param name="key">The key to search the HashMap for.</param>
		void Remove(TKey const & key);

		/// <summary>
		/// Removes any vlaues in any buckets
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the number of elements populating the HashMap.
		/// </summary>
		/// <returns>The number of elements populating the HashMap.</returns>
		size_t Size() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		double LoadFactor() const;

		/// <summary>
		/// Returns true if the key is in the HashMap and false otherwise.
		/// </summary>
		/// <param name="key">The key we are searching for within the HashMap.</param>
		/// <returns>True if the key is in the HashMap and false otherwise.</returns>
		bool ContainsKey(TKey key) const;

		
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
		HashFunctor const mHash;
		
		/// <summary>
		/// 
		/// </summary>
		inline static const std::string attemptToIteratarePastLastElementException = "Attempted to increment an iterator past end of the hash map.\n";

		/// <summary>
		/// 
		/// </summary>
		inline static const std::string keyNotInHashMapException = "Key searched for was not found in hash map.\n";
	};
	
	
};
#include "HashMap.inl"