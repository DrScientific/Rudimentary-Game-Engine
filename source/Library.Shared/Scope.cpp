/// <summary>
/// The cpp file containing the definition of nontemplated Scope functions declared in Scope.h.
/// </summary>

#include "pch.h"
#include "Scope.h"

using namespace glm;
using namespace std;


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Scope);


	Scope::Scope(Scope* const parent, size_t const & hashMapSize) :
		mHashMap(hashMapSize), mParent(parent)
	{

	}

	FIEAGameEngine::Scope::Scope(Scope const & other)
	{
		*this = other;
	}

	FIEAGameEngine::Scope::Scope(Scope && other) :
		mHashMap(std::move(other.mHashMap)), mVector(std::move(other.mVector)), mParent(other.mParent)
	{
		Reparent(other);
		other.mParent = nullptr;
	}

	Scope::~Scope()
	{
		Clear();
	}

	Scope & FIEAGameEngine::Scope::operator=(Scope const & rhs)
	{
		if (this != &rhs)
		{
			_Clear(false);
			mVector.Reserve(rhs.mVector.Size());
			for (size_t i = 0; i < rhs.mVector.Size(); ++i)
			{
				string existingName = rhs.mVector[i]->first;
				Datum& existingDatum = rhs.mVector[i]->second;

				Datum& newDatum = Append(existingName);
				newDatum.SetType(existingDatum.Type());

				if (newDatum.Type() == Datum::DatumType::Scope)
				{
					for (size_t j = 0; j < existingDatum.Size(); j++)
					{
						Scope& existingScope = *(existingDatum.Get<Scope*>(j));
						Scope* newScope = existingScope.Clone();
						newScope->mParent = this;
						newDatum.PushBack(*newScope);
					}
				}
				else
				{
					newDatum = existingDatum;;
				}
			}
		}
		return *this;
	}

	Scope & FIEAGameEngine::Scope::operator=(Scope && rhs)
	{
		if (this != &rhs)
		{
			_Clear(false);
			mHashMap = std::move(rhs.mHashMap);
			mVector = std::move(rhs.mVector);
			mParent = rhs.mParent;

			Reparent(rhs);
			rhs.mParent = nullptr;
		}
		return *this;
	}

	Datum * Scope::Find(string const & key)
	{
		if (!key.size())
		{
			throw exception(scopeCannotHaveEmptyKeyExceptionText.c_str());
		}
		Datum * result = nullptr;
		DatumMap::const_Iterator searchedPairIt = mHashMap.Find(key);
		if (searchedPairIt != mHashMap.end())
		{
			result = const_cast<Datum*>(&((*searchedPairIt).second));
		}
		return result;
	}

	Datum const * Scope::Find(string const & key) const
	{
		if (!key.size())
		{
			throw exception(scopeCannotHaveEmptyKeyExceptionText.c_str());
		}
		Datum * result = nullptr;
		DatumMap::const_Iterator searchedPairIt = mHashMap.Find(key);
		if (searchedPairIt != mHashMap.end())
		{
			result = const_cast<Datum*>(&((*searchedPairIt).second));
		}
		return result;
	}

	Datum * Scope::Search(string const & key, Scope ** scopeAddress)
	{
		if (!key.size())
		{
			throw exception(scopeCannotHaveEmptyKeyExceptionText.c_str());
		}
		if (scopeAddress != nullptr)
		{
			*scopeAddress = nullptr;
		}
		Datum * result = Find(key);
		if (result == nullptr)
		{
			if (mParent != nullptr)
			{
				result = mParent->Search(key, scopeAddress);
			}
		}
		else if (scopeAddress != nullptr)
		{
			*scopeAddress = this;
		}
		return result;
	}

	Datum const * Scope::Search(string const & key, Scope const ** scopeAddress) const
	{
		if (!key.size())
		{
			throw exception(scopeCannotHaveEmptyKeyExceptionText.c_str());
		}
		Datum const * result = Find(key);
		if (result == nullptr)
		{
			if (mParent != nullptr)
			{
				result = mParent->Search(key, scopeAddress);
			}
		}
		else if (scopeAddress != nullptr)
		{
			*scopeAddress = this;
		}
		return result;
	}

	Datum & Scope::Append(string const & key)
	{
		if (!key.size())
		{
			throw exception(scopeCannotHaveEmptyKeyExceptionText.c_str());
		}
		auto[wasKeyFound, keyIterator] = mHashMap.Insert(key, Datum());
		if (!wasKeyFound)
		{
			mVector.PushBack(&(*keyIterator));
		}
		return keyIterator->second;
	}

	Scope & Scope::AppendScope(string const & key)
	{
		Datum* appendedDatum = &Append(key);
		appendedDatum->SetType(Datum::DatumType::Scope);
		return *(appendedDatum->PushBack(*(new Scope(this))));
	}

	void FIEAGameEngine::Scope::Adopt(Scope & childToAdopt, string const & newChildKey)
	{
		if (this != &childToAdopt)
		{
			if (HasAncestor(childToAdopt))
			{
				throw exception(mayNotAdoptAncestorExceptionText.c_str());
			}

			Datum& datumToPlaceScopeIn = Append(newChildKey);
			datumToPlaceScopeIn.SetType(Datum::DatumType::Scope);

			childToAdopt.Orphan();
			childToAdopt.mParent = this;
			datumToPlaceScopeIn.PushBack(childToAdopt);
		}
	}

	Scope * Scope::GetParent() const
	{
		return mParent;
	}

	Datum & Scope::operator[](string const & key)
	{
		return Append(key);
	}

	Datum & Scope::operator[](size_t const index)
	{
		if (index >= mVector.Size())
		{
			throw exception(indexOutOfBoundsExceptionText.c_str());
		}
		return mVector[index]->second;
	}

	bool FIEAGameEngine::Scope::operator==(Scope const & rhs) const
	{
		bool result = true;
		if(this != &rhs)
		{
			//Should do less comparisons than simply comparing hashmaps although that is a valid, easier to read option.
			result = false;
			if (mVector.Size() == rhs.mVector.Size())
			{
				result = true;
				for (size_t i = 0; i < mVector.Size(); i++)
				{
					if (*mVector[i] != *rhs.mVector[i])
					{
						result = false;
						break;
					}
				}
			}
		}
		return result;
	}

	bool FIEAGameEngine::Scope::operator!=(Scope const & rhs) const
	{
		return !(*this == rhs);
	}

	string const Scope::FindName(Scope * const searchedScope)
	{
		if (searchedScope->mParent == this)
		{
			for (size_t i = 0; i < mVector.Size(); i++)
			{
				PairType* storedPair = mVector[i];
				for (size_t j = 0; j < storedPair->second.Size(); j++)
				{
					if (storedPair->second.Type() == Datum::DatumType::Scope && &(storedPair->second[j]) == searchedScope)
					{
						return storedPair->first;
					}
				}

			}
		}
		return "";
	}

	bool FIEAGameEngine::Scope::HasAncestor(Scope const & scope) const
	{
		bool result = false;
		if (mParent == &scope)
		{
			result = true;
		}
		else if (mParent != nullptr)
		{
			result = mParent->HasAncestor(scope);
		}
		return result;
	}

	pair<Datum*, size_t> FIEAGameEngine::Scope::FindNestedScope(Scope const & searchedScope)
	{
		if (searchedScope.mParent == this)
		{
			for (size_t i = 0; i < mVector.Size(); i++)
			{
				Datum& currentDatum = mVector[i]->second;
				if (currentDatum.Type() == Datum::DatumType::Scope)
				{
					for (size_t j = 0; j < currentDatum.Size(); j++)
					{
						if (&(currentDatum[j]) == &searchedScope)
						{
							return pair<Datum *, size_t>(&currentDatum, j);
						}
					}
				}
			}
		}
		return pair<Datum *, size_t>(nullptr, 0);
	}

	size_t FIEAGameEngine::Scope::Size() const
	{
		return mVector.Size();
	}

	std::string FIEAGameEngine::Scope::ToString() const
	{
		return "Scope";
	}

	bool FIEAGameEngine::Scope::Equals(const RTTI * rhs) const
	{
		bool result = false;
		if (TypeIdInstance() == rhs->TypeIdInstance())
		{
			Scope* rhsScope = const_cast<Scope*>(static_cast<const Scope*>(rhs));
			if (mVector.Size() == rhsScope->mVector.Size())
			{
				result = true;
				for (size_t i = 0; i < mVector.Size(); i++)
				{
					if (*mVector[i] != *(rhsScope->mVector[i]))
					{
						result = false;
						break;
					}
				}
			}
		}
		return result;
	}

	gsl::owner<Scope*> Scope::Clone() const
	{
		return new Scope(*this);
	}

	void Scope::Clear()
	{
		_Clear(true);
	}

	void Scope::_Clear(bool orphan)
	{
		if (orphan)
		{
			Orphan();
		}
		for (const auto& pair : mVector)
		{
			const Datum& datum = pair->second;
			if (datum.Type() == Datum::DatumType::Scope)
			{
				for (size_t i = 0; i < datum.Size(); i++)
				{
					Scope& scope = *(datum.Get<Scope*>(i));
					scope.mParent = nullptr;
					delete &scope;
				}
			}
		}
		mVector.Clear();
		mHashMap.Clear();
	}

	void FIEAGameEngine::Scope::Reparent(Scope & oldParent)
	{
		for (size_t i = 0; i < mVector.Size(); i++)
		{
			Datum& datum = mVector[i]->second;
			if (datum.Type() == Datum::DatumType::Scope)
			{
				for (size_t j = 0; j < datum.Size(); j++)
				{
					datum[j].mParent = this;
				}
			}
		}

		if (oldParent.mParent != nullptr)
		{
			auto[foundDatum, datumIndex] = oldParent.mParent->FindNestedScope(oldParent);
			if (foundDatum != nullptr)
			{
				foundDatum->Set(this, datumIndex);
			}
		}
	}

	void FIEAGameEngine::Scope::Orphan()
	{
		if (mParent != nullptr)
		{
			auto[datum, index] = mParent->FindNestedScope(*this);
			if (datum != nullptr)
			{
				datum->RemoveAt(index);
			}
			mParent = nullptr;
		}
	}
}