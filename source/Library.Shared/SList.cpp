#include "pch.h"
#include "SList.h"

using namespace FIEAGameEngine;

SList::SList()
{
	
}


SList::~SList()
{
}

size_t SList::Size() const
{
	return mSize;
}

bool SList::Find(const int value) const
{
	Node* current = mFront;
	while (current != nullptr)
	{
		if (current->Data == value)
		{
			return true;
		}

		current = current->Next;
	}
	return false;
}