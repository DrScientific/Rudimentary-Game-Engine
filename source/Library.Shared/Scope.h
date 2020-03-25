#pragma once

#include "Vector.h"
#include "HashMap.h"
#include "Datum.h"
#include "RTTI.h"
#include "gsl/gsl"

using namespace std;
using namespace glm;

namespace FIEAGameEngine
{
	class Scope : public RTTI
	{

		RTTI_DECLARATIONS(Scope, FIEAGameEngine::RTTI);
	public:
		
		friend class Scope;
		friend class Attributed;
		

		using PairType = pair<string const, Datum>;
		using DatumMap = HashMap<string const, Datum>;
		using DatumVector = Vector<PairType*>;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="parent">Pointer to the parent of the newly constructed scope.</param>
		/// <param name="hashMapSize">Size of the HashMap our scope will contain.</param>
		explicit Scope(Scope* const parent = nullptr, size_t const & hashMapSize = 20);

		/// <summary>
		/// Copy constructor
		/// </summary>
		/// <param name="other">Scope to create a copy of</param>
		Scope(Scope const & other);

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">Scope to move construct from</param>
		Scope(Scope && other);

		/// <summary>
		/// Destructor
		/// </summary>
		~Scope();

		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <param name="rhs">Scope to copy data from.</param>
		/// <returns>This scope after copying the rhs.</returns>
		Scope& operator= (Scope const & rhs);

		/// <summary>
		/// Move Assignment operator
		/// </summary>
		/// <param name="rhs">Scope to move data from.</param>
		/// <returns>This scope after moving the rhs.</returns>
		Scope& operator= (Scope && rhs);

		/// <summary>
		/// Returns a pointer to the datum at the given key. If there is nothing at the provided key returns the nullptr.
		/// </summary>
		/// <param name="key">Key to search for.</param>
		/// <returns>A pointer to the datum at the given key. If there is nothing at the provided key returns the nullptr.</returns>
		Datum* Find(string const & key);

		/// <summary>
		/// Returns a pointer to the datum at the given key. If there is nothing at the provided key returns the nullptr.
		/// </summary>
		/// <param name="key">Key to search for.</param>
		/// <returns>A pointer to the datum at the given key. If there is nothing at the provided key returns the nullptr.</returns>
		Datum const * Find(string const & key) const;

		/// <summary>
		/// Returns a pointer to the datum at the given key in this scope or it's ancestors. If this scope or it's ancestors do not posses anything at the given key returns the nullptr.
		/// Scope address is a second optional parameter that will return a pointer to a pointer of the scope the key was found in.
		/// </summary>
		/// <param name="key">Key to search for.</param>
		/// <param name="scopeAddress">Scope address is a second optional parameter that will return a pointer to a pointer of the scope the key was found in.</param>
		/// <returns>A pointer to the datum at the given key in this scope or it's ancestors.</returns>
		Datum* Search(string const & key, Scope** scopeAddress = nullptr);

		/// <summary>
		/// Returns a pointer to the datum at the given key in this scope or it's ancestors. If this scope or it's ancestors do not posses anything at the given key returns the nullptr.
		/// Scope address is a second optional parameter that will return a pointer to a pointer of the scope the key was found in.
		/// </summary>
		/// <param name="key">Key to search for.</param>
		/// <param name="scopeAddress">Scope address is a second optional parameter that will return a pointer to a pointer of the scope the key was found in.</param>
		/// <returns>A pointer to the datum at the given key in this scope or it's ancestors.</returns>
		Datum const * Search(string const & key, Scope const ** scopeAddress = nullptr) const;

		/// <summary>
		/// Appends an empty datum at the given key. If a datum exists at that key already returns that datum instead.
		/// </summary>
		/// <param name="key">The key to append the datum at.</param>
		/// <returns>The newly constructed datum or if a datum exists at that key already returns that datum instead.</returns>
		Datum & Append(string const & key);

		/// <summary>
		/// Appends a datum containing an empty scope at the given key.
		/// If a datum of type scope exists at that key already pushes a new empty scope onto that datum.
		/// If a datum of a non scope type exists at that key will throw an exception.
		/// </summary>
		/// <param name="key">The key to append the datum at.</param>
		/// <returns>The newly constructed scope.</returns>
		Scope & AppendScope(string const & key);

		/// <summary>
		/// Adopts an existiing scope placing it at the provided key. Removes the scope from it's previous parent.
		/// </summary>
		/// <param name="child">Scope to adopt.</param>
		/// <param name="newChildKey">Key to place the newly adopted scope at.</param>
		void Adopt(Scope & child, string const & newChildKey);

		/// <summary>
		/// Returns the parent of this scope.
		/// </summary>
		/// <returns>The parent of this scope.</returns>
		Scope * GetParent() const;

		/// <summary>
		/// Returns the datum at the given key. If no datum exists at the given key creates and empty datum and returns it/
		/// </summary>
		/// <param name="key">The key of the datum we wish to access.</param>
		/// <returns>The datum at the given key.</returns>
		Datum & operator[](string const & key);

		/// <summary>
		/// Returns the datum at the given index.
		/// </summary>
		/// <param name="index">Index of the datum we wish to acces.</param>
		/// <returns>The datum at the given index.</returns>
		Datum & operator[](size_t const index);

		/// <summary>
		/// Compares two scopes, comparing each key-datum pair.
		/// </summary>
		/// <param name="rhs">Scope to compare with this scope.</param>
		/// <returns>Whether the scopes are equal</returns>
		bool operator==(Scope const & rhs) const;

		/// <summary>
		/// Compares two scopes, comparing each key-datum pair.
		/// </summary>
		/// <param name="rhs">Scope to compare with this scope.</param>
		/// <returns>Whether the scopes are not equal</returns>
		bool operator!=(Scope const & rhs) const;

		/// <summary>
		/// Finds the name of the passed in scope pointer. If the passed in scope is not found returns the empty string.
		/// </summary>
		/// <param name="scope">Pointer to the scope we wish to find the name of</param>
		/// <returns>Name of the passed in scope.</returns>
		string const FindName(Scope * const scope);

		/// <summary>
		/// Returns whether the passed in scope is an ancester of this scope.
		/// </summary>
		/// <param name="scope">The scope we wish to look for in this scope's ancestory</param>
		/// <returns>Whether the passed in scope is an ancester of this scope.</returns>
		bool HasAncestor(Scope const & scope) const;

		/// <summary>
		/// Given a scope returns the datum and datum index the scope is located at.
		/// </summary>
		/// <param name="searchedScope">The scope to search for.</param>
		/// <returns>The datum and datum index the scope is located at</returns>
		pair<Datum *, size_t> FindNestedScope(Scope const & searchedScope);

		/// <summary>
		/// Returns the number of key-datum pairs in this scope.
		/// </summary>
		/// <returns>The number of key-datum pairs in this scope.</returns>
		size_t Size() const;

		/// <summary>
		/// Override of RTTI to string.
		/// </summary>
		/// <returns></returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Override of RTTI equals.
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		virtual bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Removes scope from it's parent and set's the scope's parent pointer to null.
		/// </summary>
		void Orphan();

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<Scope*> Clone();

		/// <summary>
		/// Public clear that can be overloaded by derived objects.
		/// </summary>
		virtual void Clear();

	protected:
		
		/// <summary>
		/// Private clear call that clears the contents of the scope. Passed parameter determines whether we orphan the scope from it's parent.
		/// </summary>
		/// <param name="orphan">Whether to orphan the scope from it's parent.</param>
		void _Clear(bool orphan);

		/// <summary>
		/// Makes the parent of all nested scopes in this scope equal to the address of this scope. Removes any nested scopes from the provide parent parameter.
		/// </summary>
		/// <param name="oldParent">Old parent of the newly possesed scopes.</param>
		void Reparent(Scope & oldParent);

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
		/// <summary>
		/// Communicates the cause of a may not adopt ancestor exception to the user.
		/// </summary>
		inline static const string mayNotAdoptAncestorExceptionText = "Scope may not adopt a scope that is its ancestor.\n";
#pragma endregion
	};
}