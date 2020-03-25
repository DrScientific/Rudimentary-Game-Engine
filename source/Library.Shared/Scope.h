#pragma once

//#include "Vector.h"
//#include "HashMap.h"
#include "Datum.h"
#include "RTTI.h"

using namespace std;
using namespace glm;

namespace FIEAGameEngine
{
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, FIEAGameEngine::RTTI);
	public:
		using PairType = pair<string, Datum>;

		Scope() = default;
		Scope(Scope const & other);

		~Scope();

		Scope& operator= (Scope const & rhs);

		Datum* Find(string const & key);

		Datum* Search(string const & key, Scope** scopeAddress = nullptr);

		Datum & Append(string const & key);

		Scope & AppendScope(string const & key);

		void Adopt(Scope const & child, string const & newChildKey);

		Scope * GetParent();

		Datum & operator[](string const & key);

		Datum & operator[](size_t index);

		bool operator==(Scope const & rhs) const;

		bool operator!=(Scope const & rhs) const;

		string const & FindName();

		virtual std::string ToString() const override
		{
			return "Scope";
		};

		virtual bool Equals(const RTTI* rhs) const override
		{
			return this == rhs;
		};

	private:
#pragma region MemberData

		//Vector<PairType*> mVector;

		//HashMap<string, Datum> mHashMap;

		Scope* mParent;
#pragma endregion
	};
}