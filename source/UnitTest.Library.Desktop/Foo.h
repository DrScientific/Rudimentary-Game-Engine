#pragma once

/// <summary>
/// The file containing all of the declarations of the Foo class.
/// </summary>

/// <summary>
/// 
/// </summary>
namespace UnitTests
{
	/// <summary>
	/// A class used exclusivly for unit testing.
	/// </summary>
	class Foo
	{
	public:
		Foo();
		Foo(int const data);
		~Foo() = default;

		Foo& operator=(const Foo& rhs);

		bool operator ==(const Foo& rhs) const;
		bool operator !=(const Foo& rhs) const;

		int Data() const;
	private:
		/// <summary>
		/// Integer data stored by Foo.
		/// </summary>
		int mData = 0;
	};
}
