#pragma once

#include "SList.h"

namespace FIEAGameEngine
{
	template <typename T>
	class Stack final
	{
	public:
		
		void Push(T const & value);

		void Pop();

		T& Top();

		T const & Top() const;

		std::size_t Size() const;
		
		bool IsEmpty() const;
		
		void Clear();

	private:

		SList<T> mList;
	};

}

#include "Stack.inl"