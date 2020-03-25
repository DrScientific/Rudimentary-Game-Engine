#pragma once

#include "Vector.h"
#include "HashMap.h"
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
		
		//friend Scope* & Datum::PushBack(Scope const & value);
		//friend Datum& Datum::operator= (Scope const & rhs);
		

		using PairType = pair<string const, Datum>;
		using DatumMap = HashMap<string const, Datum, DefaultHashFunctor<string>>;
		using DatumVector = Vector<PairType*>;

		explicit Scope(Scope* const parent = nullptr, size_t const & hashMapSize = 20);
		Scope(Scope const & other);

		~Scope();

		Scope& operator= (Scope const & rhs);

		Datum* Find(string const & key) const;

		Datum* Search(string const & key, Scope** scopeAddress = nullptr);

		Datum & Append(string const & key);

		Scope & AppendScope(string const & key);

		void Adopt(Scope & child, string const & newChildKey);

		Scope * GetParent() const;

		Datum & operator[](string const & key);

		Datum & operator[](size_t const index);

		bool operator==(Scope const & rhs) const;

		bool operator!=(Scope const & rhs) const;

		string const FindName(Scope * const );

		bool HasAncestor(Scope const & scope);

		pair<Datum *, size_t> FindNestedScope(Scope const & searchedScope);

		size_t Size();

		virtual std::string ToString() const override;


		virtual bool Equals(const RTTI* rhs) const override;

		void Orphan();

	private:

		void Clear();

#pragma region MemberData

		DatumVector mVector;

		DatumMap mHashMap;

		Scope* mParent = nullptr;
#pragma endregion

#pragma region ExceptionStrings
		/// <summary>
		/// Communicates the cause of an index out of bounds exception to the user.
		/// </summary>
		inline static const string indexOutOfBoundsExceptionText = "Attempted to access an out of bounds index.\n";

		/// <summary>
		/// Communicates the cause of an index out of bounds exception to the user.
		/// </summary>
		inline static const string scopeCannotHaveEmptyKeyExceptionText = "Scope cannot have an empty key.\n";

		inline static const string mayNotAdoptAncestorExceptionText = "Scope may not adopt a scope that is its ancestor.\n";
#pragma endregion
	};
}