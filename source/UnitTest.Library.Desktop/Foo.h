#pragma once
#include "RTTI.h"
#include "Factory.h"

namespace UnitTests
{
	class Foo : public FIEAGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Foo, FIEAGameEngine::RTTI);

	public:
		Foo(int data = 0);
		Foo(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		~Foo();

		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

		bool Equals(RTTI const* rhs) const override;
		std::string ToString() const override;

		int Data() const;
		void SetData(int data);

	private:
		int* mData;
	};

	CONCRETE_FACTORY(Foo, FIEAGameEngine::RTTI);
	
}