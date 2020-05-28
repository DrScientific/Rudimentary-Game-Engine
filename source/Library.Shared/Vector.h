#pragma once

/// <summary>
/// The file containing all of the declarations of the Vector class.
/// </summary>

#include <string>
#include <exception>
#include <initializer_list>

namespace FIEAGameEngine
{
	/// <summary>
	/// Vector is a templated dynamicly sized array.
	/// It can store data of any type in contiguous memory.
	/// When the vector is at capacity and an attempt to store and element in it is made the vector will resize itself, moving all of it's data to a new location in memory.
	/// </summary>
	template <typename T>
	class Vector final
	{
	public:

		typedef T value_type;

		/// <summary>
		/// An iterator that contains an index into a Vector. Any data dereferenced through a Iterator is not const. See ConstIterator.
		/// </summary>
		class Iterator
		{
		public:

			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T;
			using pointer = T * ;
			using iterator_category = std::forward_iterator_tag;

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
			/// Predecrement operation. Decrements index pointed to by iterator by 1
			/// </summary>
			/// <returns></returns>
			Iterator& operator--();

			/// <summary>
			/// Postdecrement operation. Decrements index pointed to by iterator by 1
			/// </summary>
			Iterator operator--(int);

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
			T& operator*() const;


		private:
			/// <summary>
			/// Constructor for Iterator taking in a Vector owner and an index.
			/// </summary>
			/// <param name="owner">List owning the cIterator.</param>
			/// <param name="index">Index in array iterator will point to.</param>
			Iterator(Vector const& owner, size_t index = 0);

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			Vector const* mOwner = nullptr;

			/// <summary>
			/// Index relative to start of array where value is stored.
			/// </summary>
			size_t mDataIndex = 0;

			friend class ConstIterator;
			friend Vector;
		};

		/// <summary>
		/// A ConstIterator that contains an index into a Vector. Any data dereferenced through a ConstIterator is const.
		/// </summary>
		class ConstIterator
		{
		public:
			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using reference = T;
			using pointer = T * ;
			using iterator_category = std::forward_iterator_tag;

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
			ConstIterator(const Iterator & it);

			/// <summary>
			/// Assigns a iterator to a const iterator.
			/// </summary>
			ConstIterator& operator= (const Iterator & it);


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
			/// Predecrement operation. Decrements index pointed to by iterator by 1
			/// </summary>
			/// <returns></returns>
			ConstIterator& operator--();

			/// <summary>
			/// Postdecrement operation. Decrements index pointed to by iterator by 1
			/// </summary>
			ConstIterator operator--(int);

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
			T const& operator*() const;

		private:
			/// <summary>
			/// Constructor for ConstIterator taking in a Vector owner and an index.
			/// </summary>
			/// <param name="owner">List owning the ConstIterator.</param>
			/// <param name="data">Data pointed to by the ConstIterator.</param>
			ConstIterator(Vector const& owner, size_t index = 0);

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			Vector const* mOwner = nullptr;

			/// <summary>
			/// Index relative to start of array where value is stored.
			/// </summary>
			size_t mDataIndex = 0;

			friend Vector;
		};

		/// <summary>
		/// Default constructor.
		/// Initializes Vector with a capacity of 2 and a size of 0. 
		/// </summary>
		explicit Vector(size_t initialCapacity = 2);

		/// <summary>
		/// Copy constructor.
		/// Calls the assignment operator in order to deep copy the other list.
		/// </summary>
		/// <param name="other">The list we are creating a deep copy of.</param>
		Vector(Vector const& other);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The list we are creating a deep copy of.</param>
		Vector(Vector && other);


		/// <summary>
		/// Assignment Operator.
		/// Makes the left hand side of the assignment a deep copy of the right hand side of the assignment. 
		/// </summary>
		/// <param name="other">The list on the right hand side of the expression we are setting our list equal to.</param>
		/// <returns>A reference to the list on the left hand side of the operator.</returns>
		Vector& operator=(Vector const& other);

		/// <summary>
		/// Move Assignment operator
		/// </summary>
		/// <param name="other">The list on the right hand side of the expression we are setting our list equal to.</param>
		/// <returns>A reference to the list on the left hand side of the operator.</returns>
		Vector& operator=(Vector && other);

		/// <summary>
		/// Initializer list constructor.
		/// Takes each element in the initializer list and pushes it to the back of the Vector.
		/// This will result in an Vector where the left most element is the front of the list, and the right most element is the back of the list.
		/// </summary>
		/// <param name="iList">The initializer list we are creating a list from.</param>
		Vector(std::initializer_list<T> iList);

		/// <summary>
		/// Deletes any nodes remianing int the list.
		/// Calls the clear function to perform this.
		/// </summary>
		~Vector();

		/// <summary>
		/// Returns an iterator pointing to the first element of the list.
		/// </summary>
		/// <returns>Iterator pointing to the first element</returns>
		Iterator begin();

		/// <summary>
		/// Returns a const_iterator pointing to the first element of the list.
		/// </summary>
		/// <returns>const_iterator pointing to the first element of the list.</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns an iterator pointing to element past the last element of the list.
		/// </summary>
		/// <returns>An iterator pointing to element past the last element of the list</returns>
		Iterator end();

		/// <summary>
		/// Returns a const_iterator pointing to element past the last element of the list.
		/// </summary>
		/// <returns>A const_iterator pointing to element past the last element of the list.</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns a const_iterator pointing to the first element of the list.
		/// </summary>
		/// <returns>const_iterator pointing to the first element of the list.</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns a const_iterator pointing to element past the last element of the list.
		/// </summary>
		/// <returns>A const_iterator pointing to element past the last element of the list.</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Explicitly calls the destructor on each initialized element in the vector.
		/// </summary>
		void Clear();

		/// <summary>
		/// Reserves an amount of memory for the vector equal to the new capacity if the new capacity is larger than the old capacity.
		/// </summary>
		/// <param name="newCapacity"> The new capacity of the vector.</param>
		void Reserve(size_t newCapacity);

		/// <summary>
		/// Resize the vector. If it is sized to a size larger than it currently is, initialized the new elments to copies of the passed in T
		/// </summary>
		/// <param name="newSize">New size of the vector.</param>
		/// /// <param name="valueToFill">Values any newly created T's are initialized to.</param>
		void Resize(size_t newSize);

		/// <summary>
		/// Access the data stored at the given index. Works exactly like the [] operator in an array.
		/// </summary>
		/// <param name="index">Index where the data we want to access is located.</param>
		/// <returns>Data stored at the specified index.</returns>
		T& operator[](size_t const& index);

		/// <summary>
		/// Access the data stored at the given index. Works exactly like the [] operator in an array. Data accessed this way cannot be mutated
		/// </summary>
		/// <param name="index">Index where the data we want to access is located.</param>
		/// <returns>Data stored at the specified index.</returns>
		T const& operator[](size_t const& index) const;

		/// <summary>
		/// Returns a new vector that is this vector appeneded to the other vector.
		/// </summary>
		/// <param name="other">The vector to append to this vector.</param>
		/// <returns>A new vector that is this vector appeneded to the other vector..</returns>
		Vector<T> operator+(Vector<T> const& other);

		/// <summary>
		/// Returns a new vector that is this vector appeneded to the other vector.
		/// </summary>
		/// <param name="other">The vector to append to this vector.</param>
		/// <returns>A new vector that is this vector appeneded to the other vector..</returns>
		Vector<T> const operator+(Vector<T> const& other) const;

		/// <summary>
		/// Appends the elements of the other vector to this vector.vector that is this vector appeneded to the other vector.
		/// </summary>
		/// <param name="other">The vector to append to this vector.</param>
		/// <returns>This vector after having the other vector appended to it.</returns>
		Vector<T> operator+=(Vector<T> const& other);

		/// <summary>
		/// Returns a new vector that is this vector appeneded to the other vector.
		/// </summary>
		/// <param name="other">The vector to append to this vector.</param>
		/// <returns>A new vector that is this vector appeneded to the other vector..</returns>
		Vector<T> operator-(Vector<T> const& other);

		/// <summary>
		/// Returns a new vector that is this vector appeneded to the other vector.
		/// </summary>
		/// <param name="other">The vector to append to this vector.</param>
		/// <returns>A new vector that is this vector appeneded to the other vector..</returns>
		Vector<T> const operator-(Vector<T> const& other) const;

		/// <summary>
		/// Appends the elements of the other vector to this vector.vector that is this vector appeneded to the other vector.
		/// </summary>
		/// <param name="other">The vector to append to this vector.</param>
		/// <returns>This vector after having the other vector appended to it.</returns>
		Vector<T> operator-=(Vector<T> const& other);

		/// <summary>
		/// Access the data stored at the given index. Works exactly like the [] operator in an array.
		/// </summary>
		/// <param name="index">Index where the data we want to access is located.</param>
		/// <returns>Data stored at the specified index.</returns>
		T& At(size_t const& index);

		/// <summary>
		/// Access the data stored at the given index. Data accessed this way cannot be mutated
		/// </summary>
		/// <param name="index">Index where the data we want to access is located.</param>
		/// <returns>Data stored at the specified index.</returns>
		T const& At(size_t const& index) const;

		/// <summary>
		/// Returns the capacity of the vector.
		/// </summary>
		/// <returns>Capacity of the vector</returns>
		size_t Capacity() const;

		/// <summary>
		/// Returns the size of the vector.
		/// </summary>
		/// <returns>Size of the vector</returns>
		size_t Size() const;

		/// <summary>
		/// Returns true if the list is empty.
		/// </summary>
		/// <returns>Whether the list is empty.</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Checks that two vectors are equal.
		/// </summary>
		/// <param name="other">Vector to compare with.</param>
		/// <returns>Whether the vectors are equal.</returns>
		bool operator==(Vector<T> const& other) const;

		/// <summary>
		/// Checks that two vectors are equal.
		/// </summary>
		/// <param name="other">Vector to compare with.</param>
		/// <returns>Whether the vectors are equal.</returns>
		bool operator!=(Vector<T> const& other) const;

		/// <summary>
		/// Returns the value of the front element of the vector.
		/// </summary>
		/// <returns>The value of the front element of the vector.</returns>
		T& Front();

		/// <summary>
		/// Returns the value of the front element of the vector.
		/// </summary>
		/// <returns>The value of the front element of the vector.</returns>
		T const& Front() const;

		/// <summary>
		/// Returns the value of the last element of the vector.
		/// </summary>
		/// <returns>The value of the last element of the vector.</returns>
		T& Back();

		/// <summary>
		/// Returns the value of the last element of the vector.
		/// </summary>
		/// <returns>The value of the last element of the vector.</returns>
		T const& Back() const;

		/// <summary>
		/// Places the specified value at the back of the vector, resizing if necessary.
		/// </summary>
		/// <param name="value">Value to place at the back of the list.</param>
		void PushBack(T const& value);

		/// <summary>
		/// Places the specified value at the back of the vector, resizing if necessary.
		/// </summary>
		/// <param name="value">Value to place at the back of the list.</param>
		void PushBack(T const&& value);

		/// <summary>
		/// Places the specified value at the back of the vector, resizing if necessary. Wrapper of PushBack() so back inserter can be used.
		/// </summary>
		/// <param name="value">Value to place at the back of the list.</param>
		void push_back(T const& value);

		/// <summary>
		/// Removes the last element of the vector fromt the vector
		/// </summary>
		/// <returns>An iterator to the last element in the list after we have popped the last element off.</returns>
		Vector<T>::Iterator PopBack();

		/// <summary>
		/// Returns an iterator to the first element in the array with the passed in value.
		/// </summary>
		/// <param name="value">The value we are searching for.</param>
		/// <returns>An iterator to the first element in the array with the passed in value.</returns>
		Vector<T>::Iterator Find(T const& value);

		/// <summary>
		/// Returns a const_iterator to the first element in the array with the passed in value.
		/// </summary>
		/// <param name="value">The value we are searching for.</param>
		/// <returns>A const_iterator to the first element in the array with the passed in value.</returns>
		Vector<T>::ConstIterator Find(T const& value) const;

		/// <summary>
		/// Removes all elements equal to value in the list.
		/// </summary>
		/// <param name="value">Value to remove.</param>
		void Remove(T const& value);

		/// <summary>
		/// Removes the element at the passed in iterator.
		/// </summary>
		/// <param name="iteratorToRemove">Iterator pointing to the element to remove.</param>
		void Remove(Iterator const& iteratorToRemove);

		/// <summary>
		/// Removes all elements equal to value in the list.
		/// </summary>
		/// <param name="value">Value to remove.</param>
		void RemoveAt(size_t index);

		/// <summary>
		/// Removes all elements between two iterators exclusive of the finish iterator.
		/// </summary>
		/// <param name="start">Iterator pointing to the first element to remove.</param>
		/// <param name="finish">Iterator pointing to the element before the last element to remove.</param>
		void Remove(Iterator const& start, Iterator const& finish);

		/// <summary>
		/// Swaps the values pointed to by two iterators in the vector.
		/// </summary>
		/// <param name="element1">An iterator pointing to the first element to swap.</param>
		/// <param name="element2">An iterator pointing to the second element to swap.</param>
		void Swap(Iterator const& element1, Iterator const& element2);

		/// <summary>
		/// Randomizes the order of the Vector.
		/// </summary>
		void Shuffle();

		/// <summary>
		/// Reverses the Vector.
		/// </summary>
		void Reverse();

		/// <summary>
		/// Shrinks the capacity of the vector to the current size of the vector.
		/// </summary>
		void ShrinkToFit();

	private:
		/// <summary>
		/// Points to an array of size mCapacity. mArray will change whenever the array is resized.
		/// </summary>
		T * mArray = nullptr;

		/// <summary>
		/// The number of elements contained within vector.
		/// </summary>
		size_t mSize = 0;

		/// <summary>
		/// The number of elements the vector can contain before it must resize.
		/// </summary>
		size_t mCapacity = 0;

		/// <summary>
		/// Communicates the cause of an empty vector exception to the user. 
		/// </summary>
		inline static const std::string vectorEmptyExceptionText = "Attempted to return data from an empty vector.\n";

		/// <summary>
		/// Communicates the cause of an index out of bounds exception to the user.
		/// </summary>
		inline static const std::string indexOutOfBoundsExceptionText = "Attempted to access an out of bounds index.\n";

		/// <summary>
		/// Communicates the cause of an increment iterator past end exception to the user.
		/// </summary>
		inline static const std::string incrementIteratorPastEndExceptionText = "Attempted to increment an iterator past end of vector.\n";

		/// <summary>
		/// Communicates the cause of an data lost on resize exception to the user. 
		/// </summary>
		inline static const std::string newCapacityCannotBeSmallerThanCapacityExceptionText = "New capacity cannot be smaller than old vector capacity.\n";

		/// <summary>
		///  Communicates the cause of an iterator from other list exception to the user.
		/// </summary>
		inline static const std::string iteratorFromOtherListExceptionText = "Iterator provided is from another list.\n";

		/// <summary>
		///  Communicates the cause of a cannot swap end exception to the user.
		/// </summary>
		inline static const std::string cannotSwapEndExceptionText = "Cannot swap end Iterator.\n";
	};
}

#include "Vector.inl"