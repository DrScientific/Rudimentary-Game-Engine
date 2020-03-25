#include "pch.h"
#include "Bar.h"

using namespace FIEAGameEngine;

namespace UnitTests
{
	RTTI_DEFINITIONS(Bar)

	Bar::Bar(int data) : mData(new int(data))
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
	int const Bar::Data() const
	{
		return *mData;
	}
}