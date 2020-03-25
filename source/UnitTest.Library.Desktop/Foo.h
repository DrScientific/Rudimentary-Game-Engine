#pragma once

namespace UnitTests
{
	class Foo
	{
	public:
		Foo(int data = 0);
		Foo(const Foo& rhs);
		Foo& operator=(const Foo& rhs);
		~Foo();

		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

		int Data() const;
		void SetData(int data);

	private:
		int* mData;
	};
}