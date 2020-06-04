#include "pch.h"
#include "Foo.h"
#include <string>

using namespace std;
using namespace std::string_literals;
using namespace FIEAGameEngine;

namespace UnitTests
{
	RTTI_DEFINITIONS(Foo);


	Foo::Foo(int data) :
		mData(new int(data))
	{
	}

	Foo::Foo(const Foo& rhs) :
		mData(new int(*rhs.mData))
	{
	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			*mData = *rhs.mData;
		}

		return *this;
	}

	Foo::~Foo()
	{
		delete mData;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		return *mData == *rhs.mData;
	}

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}

	bool Foo::operator<(const Foo& rhs) const
	{
		return *mData < *rhs.mData;
	}

	bool Foo::operator<=(const Foo& rhs) const
	{
		return *mData <= *rhs.mData;
	}

	bool Foo::operator>(const Foo& rhs) const
	{
		return !operator<=(rhs);
	}

	bool Foo::operator>=(const Foo& rhs) const
	{
		return !operator<(rhs);
	}

	bool Foo::operator==(const int& rhs) const
	{
		return *mData == rhs;
	}

	bool Foo::operator!=(const int& rhs) const
	{
		return !operator==(rhs);
	}

	bool Foo::operator<(const int& rhs) const
	{
		return *mData < rhs;
	}

	bool Foo::operator<=(const int& rhs) const
	{
		return *mData <= rhs;
	}

	bool Foo::operator>(const int& rhs) const
	{
		return !operator<=(rhs);
	}

	bool Foo::operator>=(const int& rhs) const
	{
		return !operator<(rhs);
	}

	bool Foo::operator==(size_t const& rhs) const
	{
		return *mData == static_cast<int>(rhs);
	}

	bool Foo::operator!=(size_t const& rhs) const
	{
		return !operator==(rhs);
	}

	bool Foo::operator<(size_t const& rhs) const
	{
		return *mData < static_cast<int>(rhs);
	}

	bool Foo::operator<=(size_t const& rhs) const
	{
		return *mData <= static_cast<int>(rhs);
	}

	bool Foo::operator>(size_t const& rhs) const
	{
		return !operator<=(rhs);
	}

	bool Foo::operator>=(size_t const& rhs) const
	{
		return !operator<(rhs);
	}

	Foo Foo::operator+(const int& rhs) const
	{
		return Foo(*mData+rhs);
	}

	Foo Foo::operator-(const int& rhs) const
	{
		return Foo(*mData - rhs);
	}

	Foo Foo::operator*(const int& rhs) const
	{
		return Foo(*mData * rhs);
	}

	Foo Foo::operator/(const int& rhs) const
	{
		return Foo(*mData / rhs);
	}

	Foo Foo::operator%(int const& rhs) const
	{
		return Foo(*mData % rhs);
	}

	Foo& Foo::operator++()
	{
		(*mData)++;
		return *this;
	}

	Foo Foo::operator++(int)
	{
		Foo temp = *this;
		operator++();
		return temp;
	}

	bool Foo::Equals(RTTI const* rhs) const
	{
		Foo* other = rhs->As<Foo>();
		return (other != nullptr ? *this == *other : false);
	}

	std::string Foo::ToString() const
	{;
		return (mData != nullptr ? to_string(*mData ) : "nullptr");
	}

	int Foo::Data() const
	{
		return *mData;
	}

	void Foo::SetData(int data)
	{
		*mData = data;
	}
	bool operator==(int const& lhs, Foo const& rhs)
	{
		return lhs== rhs.Data();
	}
	bool operator!=(int const& lhs, Foo const& rhs)
	{
		return !operator==(lhs,rhs);
	}
	bool operator<(int const& lhs, Foo const& rhs)
	{
		return lhs < rhs.Data();
	}
	bool operator<=(int const& lhs, Foo const& rhs)
	{
		return lhs <= rhs.Data();
	}
	bool operator>(int const& lhs, Foo const& rhs)
	{
		return !operator<=(lhs, rhs);
	}
	bool operator>=(int const& lhs, Foo const& rhs)
	{
		return !operator<(lhs,rhs);
	}
	bool operator==(size_t const& lhs, Foo const& rhs)
	{
		return static_cast<int>(lhs) == rhs.Data();
	}
	bool operator!=(size_t const& lhs, Foo const& rhs)
	{
		return !operator==(lhs, rhs);
	}
	bool operator<(size_t const& lhs, Foo const& rhs)
	{
		return static_cast<int>(lhs) < rhs.Data();
	}
	bool operator<=(size_t const& lhs, Foo const& rhs)
	{
		return static_cast<int>(lhs) <= rhs.Data();
	}
	bool operator>(size_t const& lhs, Foo const& rhs)
	{
		return !operator<=(lhs, rhs);
	}
	bool operator>=(size_t const& lhs, Foo const& rhs)
	{
		return !operator<(lhs, rhs);
	}
	int operator+(int const& lhs, Foo const& rhs)
	{
		return lhs + rhs.Data();
	}
	int operator-(int const& lhs, Foo const& rhs)
	{
		return lhs - rhs.Data();
	}
	int operator*(int const& lhs, Foo const& rhs)
	{
		return lhs * rhs.Data();
	}
	int operator/(int const& lhs, Foo const& rhs)
	{
		return lhs / rhs.Data();
	}
	int operator%(int const& lhs, Foo const& rhs)
	{
		return lhs % rhs.Data();
	}
}