#pragma once

/// <summary>
/// The file containing all of the declarations of the SList class.
/// </summary>

#include "pch.h"

namespace FIEAGameEngine
{
	/// <summary>
	/// SList is a templated singly linked forward pointing list.
	/// It can store data of any type in a series of nodes and each node points onward to the next node, but not back to the previous node.
	/// </summary>
	template <typename T>
	class SList
	{
	public:

		/// <summary>
		/// Default constructor.
		/// Initializes SList to an empty list with mFront and mBack initialized to the nullptr. 
		/// </summary>
		SList();

		/// <summary>
		/// Copy constructor.
		/// Calls the assignment operator in order to deep copy the other list.
		/// </summary>
		/// <param name="other">The list we are creating a deep copy of.</param>
		SList(SList const & other);

		/// <summary>
		/// Initializer list constructor.
		/// Takes each element in the initializer list and pushes it to the back of the SList.
		/// This will result in an SList where the left most element is the front of the list, and the right most element is the back of the list.
		/// </summary>
		/// <param name="iList">The initializer list we are creating a list from.</param>
		SList(std::initializer_list<T> iList);

		/// <summary>
		/// Deletes any nodes remianing int the list.
		/// Calls the clear function to perform this.
		/// </summary>
		~SList();

		/// <summary>
		/// Puts a new node containing the passed in value at the front of the list.
		/// </summary>
		/// <param name="value">The value we are pushing to the front of the list.</param>
		void PushFront(T const value);

		/// <summary>
		/// Removes the element at the front of the list from the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>A copy of the data that was being stored at the front of the list.</returns>
		T PopFront();

		/// <summary>
		/// Puts a new node containing the passed in value at the back of the list.
		/// </summary>
		/// <param name="value">The value we are pushing to the back of the list.</param>
		void PushBack(T const value);

		/// <summary>
		/// Removes the element at the back of the list from the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>A copy of the data that was being stored at the back of the list.</returns>
		T PopBack();


		bool isEmpty() const;

		/// <summary>
		/// Accesses the data at the front of the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns> The data stored at the front of the list by reference.</returns>
		T& Front();

		/// <summary>
		/// Accesses the data at the back of the list.
		/// Will throw an exception if called on an empty list.
		/// </summary>
		/// <returns>The data stored at the back of the list by reference.</returns>
		T& Back();

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
		/// Assignment Operator.
		/// Makes the left hand side of the assignment a deep copy of the right hand side of the assignment. 
		/// </summary>
		/// <param name="rhs">The list on the right hand side of the expression we are setting our list equal to.</param>
		/// <returns>A reference to the list on the left hand side of the operator.</returns>
		SList& operator=(SList const & rhs);

		/// <summary>
		/// First compares the sizes of the two lists.
		/// Then compares the data of each node in the left list to the data in each corresponding node in the right list.
		/// </summary>
		/// <param name="rhs"> The list on the right hand side of the expression we are comparing to.</param>
		/// <returns>
		/// /// If each node contains the same data as the corresponding node in the other list and the list are the same size true is returned.
		/// Otherwise returns false.
		/// </returns>
		bool operator==(SList const & rhs) const;
		
		/// <summary>
		/// /// First compares the sizes of the two lists.
		/// Then compares the data of each node in the left list to the data in each corresponding node in the right list.
		/// </summary>
		/// <param name="rhs"> The list on the right hand side of the expression we are comparing to.</param>
		/// <returns>
		/// If each node contains the same data as the corresponding node in the other list and the list are the same size false is returned.
		/// Otherwise returns true.
		/// </returns>
		bool operator!=(SList const & rhs) const;

		/*
		//Specifics of most of the behaviors of these functions can be found here
		//http://www.cplusplus.com/reference/forward_list/forward_list/
		TODO int Count(const T value) const;
		
		TODO T& operator[](const int index) const;
		TODO unsigned int Find(const T value) const; //Requires iterators
		TODO unsigned int* FindAll(const T value) const; //Requires iterators
		
		TODO void InsertAfter(unsigned int index, const T value);
		TODO void EraseAfter(unsigned int index, const T value);
		
		TODO void Swap (SList & other) // swaps the contents of one list with another
		TODO void Resize (size_t const newSize);
		TODO void Resize (size_t const newSize, const const T value);
		TODO void Assign (); //Requires iterators
		TODO void EmplaceFront(); // Do not know how to reference constructor of templated type
		TODO void EmplaceBack(); // Do not know how to reference constructor of templated type
		
		
		TODO void SpliceAfter (); //Requires iterators
		TODO void Remove(const T value); 
		TODO void RemoveIf(const T value); //Requires predicate class? May not do this one.
		TODO void Unique(const T value); // will remove duplicate values
		TODO void Merge(SList & other); //Requires iterators
		TODO void Sort();
		TODO void Reverse(); //Requires iterators
		*/

	private:
		/// <summary>
		/// Nodes contain data of an arbitray type as well as a pointer to the next node in the SList.
		/// </summary>
		struct Node
		{
			T data;
			Node * next = nullptr;
		};

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
		const std::string listEmptyExceptionText = "Attempted to return data from an empty list.\n";

		/// <summary>
		/// Communicates the cause of an index out of bounds exception to the user. Not currently implemented, should be implemented once operator[] and iterators are in place.
		/// </summary>
		const std::string indexOutOfBoundsExceptionText = "Attempted to access an out of bounds index.\n";
	};
}

#include "SList.inl"