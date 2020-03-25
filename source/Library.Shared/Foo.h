#pragma once
namespace FIEAGameEngine
{
	class Foo
	{
	public:
		explicit Foo(int data = 0);
		~Foo() = default;

		int Data() const;
	private:
		int mData;
	};
}
