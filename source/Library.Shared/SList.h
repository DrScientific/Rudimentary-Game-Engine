#pragma once

namespace FIEAGameEngine
{
	class SList
	{
	public:
		SList();
		~SList();

		size_t Size() const;
		bool Find(const int value) const;

	private:
		struct Node
		{
			int Data;
			Node * Next;
		};
		
		Node* mFront = nullptr;
		Node* mBack = nullptr;
		size_t mSize = 0;
	};
}
