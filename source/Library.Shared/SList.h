#pragma once

/// <summary>
/// The file containing all of the declarations of the SList class.
/// </summary>

#include <string>
#include <exception>
#include <initializer_list>

namespace FIEAGameEngine
{
	/// <summary>
	/// SList is a templated singly linked forward pointing list.
	/// It can store data of any type in a series of nodes and each node points onward to the next node, but not back to the previous node.
	/// </summary>
	template <typename T>
	class SList final
	{
	private:
		/// <summary>
		/// Nodes contain data of an arbitray type as well as a pointer to the next node in the SList.
		/// </summary>
		struct Node final
		{
			/// <summary>
			/// Explicit node constructor.
			/// </summary>
			/// <param name="data"></param>
			/// <param name="next"></param>
			explicit Node(T const& data, Node* next = nullptr);

			/// <summary>
			/// No need for a copy constructor.
			/// </summary>
			/// <param name=""></param>
			Node(Node const&) = delete;

			/// <summary>
			/// No need for an assignment operator.
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			Node& operator=(Node const&) = delete;
			~Node() = default;

			/// <summary>
			/// Data stored by node.
			/// </summary>
			T mData;

			/// <summary>
			/// Pointer to the node after this one.
			/// </summary>
			Node * mNext = nullptr;
		};

	public:

		/// <summary>
		/// An iterator that points to member nodes of SList. Any data dereferenced through a Iterator is not const. See ConstIterator.
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
			/// Preincrement operation
			/// </summary>
			/// <returns></returns>
			Iterator& operator++();

			/// <summary>
			/// Postincrement operation
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
			T& operator*() const;

		private:
			/// <summary>
			/// Constructor for Iterator taking in a list owner and a node.
			/// </summary>
			/// <param name="owner">List owning the Iterator.</param>
			/// <param name="node">Node pointed to by the Iterator.</param>
			Iterator(const SList& owner, Node* node = nullptr);

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			const SList* mOwner = nullptr;

			/// <summary>
			/// A pointer to the node the Iterator is currently pointing at.
			/// </summary>
			Node * mNode = nullptr;

			friend class ConstIterator;
			friend class SList<T>;
		};

		/// <summary>
		/// A ConstIterator that points to member nodes of SList. Any data dereferenced through a ConstIterator is const.
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
			ConstIterator(const Iterator & it);

			/// <summary>
			/// Preincrement operation
			/// </summary>
			/// <returns></returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postincrement operation
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
			T const& operator*() const;

		private:
			/// <summary>
			/// Constructor for ConstIterator taking in a list owner and a node.
			/// </summary>
			/// <param name="owner">List owning the ConstIterator.</param>
			/// <param name="node">Node pointed to by the ConstIterator.</param>
			ConstIterator(const SList& owner, Node* node = nullptr);

			/// <summary>
			/// The list that owns the Iterator.
			/// </summary>
			const SList* mOwner = nullptr;

			/// <summary>
			/// Pointer to the next node in the list.
			/// </summary>
			Node * mNode = nullptr;

			friend class Iterator;
			friend class SList<T>;
		};

		/// <summary>
		/// Default constructor.
		/// Initializes SList to an empty list with mFront and mBack initialized to the nullptr. 
		/// </summary>
		SList();

		/// <summary>
		/// Initializer list constructor.
		/// Takes each element in the initializer list and pushes it to the back of the SList.
		/// This will result in an SList where the left most element is the front of the list, and the right most element is the back of the list.
		/// </summary>
		/// <param name="iList">The initializer list we are creating a list from.</param>
		SList(std::initializer_list<T> iList);

		/// <summary>
		/// Copy constructor.
		/// Calls the assignment operator in order to deep copy the other list.
		/// </summary>
		/// <param name="other">The list we are creating a deep copy of.</param>
		SList(SList const& other);

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The list we are creating a deep copy of.</param>
		SList(SList && other);

		/// <summary>
		/// Assignment Operator.
		/// Makes the left hand side of the assignment a deep copy of the right hand side of the assignment. 
		/// </summary>
		/// <param name="other">The list on the right hand side of the expression we are setting our list equal to.</param>
		/// <returns>A reference to the list on the left hand side of the operator.</returns>
		SList& operator=(SList const& other);

		/// <summary>
		/// Move Assignment Operator.
		/// </summary>
		/// <param name="other">The list on the right hand side of the expression we are setting our list equal to.</param>
		/// <returns>A reference to the list on the left hand side of the operator.</returns>
		SList& operator=(SList&& other);

		/// <summary>
		/// Deletes any nodes remianing int the list.
		/// Calls the clear function to perform this.
		/// </summary>
		~SList();

		/// <summary>
		/// First compares the sizes of the two lists.
		/// Then compares the data of each node in the left list to the data in each corresponding node in the right list.
		/// </summary>
		/// <param name="other"> The list on the right hand side of the expression we are comparing to.</param>
		/// <returns>
		/// /// If each node contains the same data as the corresponding node in the other list and the list are the same size true is returned.
		/// Otherwise returns false.
		/// </returns>
		bool operator==(SList const& other) const;

		/// <summary>
		/// /// First compares the sizes of the two lists.
		/// Then compares the data of each node in the left list to the data in each corresponding node in the right list.
		/// </summary>
		/// <param name="other"> The list on the right hand side of the expression we are comparing to.</param>
		/// <returns>
		/// If each node contains the same data as the corresponding node in the other list and the list are the same size false is returned.
		/// Otherwise returns true.
		/// </returns>
		bool operator!=(SList const& other) const;

		/// <summary>
		/// Gets Iterator pointing to first element in list.
		/// </summary>
		/// <returns>An Iterator to the first element in the list.</returns>
		Iterator begin() const;

		/// <summary>
		/// Gets ConstIterator pointing to first element in list.
		/// </summary>
		/// <returns>A ConstIterator to the first element in the list.</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Gets Iterator pointing to nullptr.
		/// </summary>
		/// <returns>An Iterator to the element past the last element</returns>
		Iterator end() const;

		/// <summary>
		/// Gets ConstIterator pointing to nullptr.
		/// </summary>
		/// <returns>A ConstIterator to the element past the last element</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Puts a new node containing the passed in value at the front of the list.
		/// </summary>
		/// <param name="value">The value we are pushing to the front of the list.</param>
		Iterator PushFront(T const& value);

		/// <summary>
		/// Removes the element at the front of the list from the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>A copy of the data that was being stored at the front of the list.</returns>
		Iterator PopFront();

		/// <summary>
		/// Puts a new node containing the passed in value at the back of the list.
		/// </summary>
		/// <param name="value">The value we are pushing to the back of the list.</param>
		Iterator PushBack(T const& value);

		/// <summary>
		/// Removes the element at the back of the list from the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>A copy of the data that was being stored at the back of the list.</returns>
		Iterator PopBack();

		/// <summary>
		/// Returns true if the list size is 0. Returns false otherwise.y.
		/// </summary>
		/// <returns>A bool as to whether the list is empty.</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Accesses the data at the front of the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns> The data stored at the front of the list by reference.</returns>
		T & Front();

		/// <summary>
		/// Accesses the data at the front of the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns> The data stored at the front of the list by reference.</returns>
		const T& Front() const;

		/// <summary>
		/// Accesses the data at the back of the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>The data stored at the back of the list by reference.</returns>
		T& Back();

		/// <summary>
		/// Accesses the data at the back of the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>The data stored at the back of the list by reference.</returns>
		const T& Back() const;

		/// <summary>
		/// Iterates through each node in the list, saving the next node, deleting the current node, then setting the current node to the next node.
		/// This will always result in an empty list.
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the number of elements in the list.
		/// </summary>
		/// <returns>The number of elements in the list.</returns>
		size_t Size() const;

		/// <summary>
		/// Inserts a node after the node pointed to by the passed in Iterator.
		/// </summary>
		/// <param name="it">The node to insert the passed in value after.</param>
		/// <param name="value">The value to insert in the list.</param>
		SList<T>::Iterator InsertAfter(Iterator const& it, T const& value);

		/// <summary>
		/// Finds an element with a given value in the list
		/// </summary>
		/// <param name="value">Value to search for</param>
		/// <returns>Iterator to first node storing the searched for value.</returns>
		SList<T>::Iterator Find(T const& value);

		/// <summary>
		/// Finds an element with a given value in the list
		/// </summary>
		/// <param name="value">Value to search for</param>
		/// <returns>Iterator to first node storing the searched for value.</returns>
		SList<T>::ConstIterator Find(T const& value) const;

		/// <summary>
		/// Removes the first node with the passed in value.
		/// </summary>
		/// <param name="value">Value of node to remove.</param>
		void Remove(T const& value);

		/// <summary>
		/// Removes the node at the passed in Iterator.
		/// </summary>
		/// <param name="it">The Iterator to be removed.</param>
		void Remove(Iterator const& it);

		/// <summary>
		/// Reverses the SList.
		/// </summary>
		void Reverse();

	private:
		/// <summary>
		/// A pointer to the first element of the list. Should only be null when the list is empty.
		/// </summary>
		Node* mFront = nullptr;

		/// <summary>
		/// A pointer to the last element of the list. Should only be null when the list is empty.
		/// </summary>
		Node* mBack = nullptr;

		/// <summary>
		/// The number of nodes contained within the list.
		/// </summary>
		size_t mSize = 0;

		/// <summary>
		/// Communicates the cause of an empty list exception to the user. 
		/// </summary>
		inline static const std::string listEmptyExceptionText = "Attempted to return data from an empty list.\n";

		/// <summary>
		/// Communicates the cause of an index out of bounds exception to the user. Not currently implemented, should be implemented once operator[] and iterators are in place.
		/// </summary>
		inline static const std::string indexOutOfBoundsExceptionText = "Attempted to access an out of bounds index.\n";

		/// <summary>
		///  Communicates the cause of an iterator from other list exception to the user.
		/// </summary>
		inline static const std::string iteratorFromOtherListExceptionText = "Iterator provided is from another list.\n";

		friend class Iterator;
		friend class ConstIterator;
	};
}

#include "SList.inl"