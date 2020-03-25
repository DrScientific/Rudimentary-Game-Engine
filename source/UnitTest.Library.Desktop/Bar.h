#pragma once
#include "RTTI.h"

namespace FIEAGameEngine
{
	class Bar : public RTTI
	{
		RTTI_DECLARATIONS(Bar, RTTI)
	public:
		explicit Bar(int data = 0);
		Bar(const Bar& rhs);
		~Bar();

	private:
		int* mData;
	};

}