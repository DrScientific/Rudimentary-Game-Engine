#pragma once
#include "RTTI.h"

namespace UnitTests
{
	class Bar : public FIEAGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Bar, FIEAGameEngine::RTTI)
	public:
		explicit Bar(int data = 0);
		Bar(const Bar& rhs);
		~Bar();

		int const Data() const;

	private:
		int* mData;
	};

}