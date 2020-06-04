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
		Foo(Foo const& rhs);
		Foo& operator=(Foo const& rhs);
		~Foo();

		bool operator==(Foo const& rhs) const;
		bool operator!=(Foo const& rhs) const;
		bool operator<(Foo const& rhs) const;
		bool operator<=(Foo const& rhs) const;
		bool operator>(Foo const& rhs) const;
		bool operator>=(Foo const& rhs) const;

		bool operator==(int const& rhs) const;
		bool operator!=(int const& rhs) const;
		bool operator<(int const& rhs) const;
		bool operator<=(int const& rhs) const;
		bool operator>(int const& rhs) const;
		bool operator>=(int const& rhs) const;

		bool operator==(size_t const& rhs) const;
		bool operator!=(size_t const& rhs) const;
		bool operator<(size_t const& rhs) const;
		bool operator<=(size_t const& rhs) const;
		bool operator>(size_t const& rhs) const;
		bool operator>=(size_t const& rhs) const;

		Foo operator+(int const& rhs) const;
		Foo operator-(int const& rhs) const;
		Foo operator*(int const& rhs) const;
		Foo operator/(int const& rhs) const;
		Foo operator%(int const& rhs) const;

		Foo& operator++();

		Foo operator++(int);

		bool Equals(RTTI const* rhs) const override;
		std::string ToString() const override;

		int Data() const;
		void SetData(int data);

	private:
		int* mData;
	};

	bool operator==(int const& lhs, Foo const& rhs) ;
	bool operator!=(int const& lhs, Foo const& rhs);
	bool operator<(int const& lhs, Foo const& rhs);
	bool operator<=(int const& lhs, Foo const& rhs);
	bool operator>(int const& lhs, Foo const& rhs);
	bool operator>=(int const& lhs, Foo const& rhs);

	bool operator==(size_t const& lhs, Foo const& rhs);
	bool operator!=(size_t const& lhs, Foo const& rhs);
	bool operator<(size_t const& lhs, Foo const& rhs);
	bool operator<=(size_t const& lhs, Foo const& rhs);
	bool operator>(size_t const& lhs, Foo const& rhs);
	bool operator>=(size_t const& lhs, Foo const& rhs);

	int operator+(int const& lhs, Foo const& rhs);
	int operator-(int const& lhs, Foo const& rhs);
	int operator*(int const& lhs, Foo const& rhs);
	int operator/(int const& lhs, Foo const& rhs);
	int operator%(int const& lhs, Foo const& rhs);

	CONCRETE_FACTORY(Foo, FIEAGameEngine::RTTI);
}