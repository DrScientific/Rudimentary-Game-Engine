#include "pch.h"
#include "Bar.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Bar)

		Bar::Bar(int data) :
		mData(new int(data))
	{
	}

	Bar::Bar(const Bar& rhs) :
		mData(new int(*rhs.mData))
	{
	}

	Bar::~Bar()
	{
		delete mData;
	}
}