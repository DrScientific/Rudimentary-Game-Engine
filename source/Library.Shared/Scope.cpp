/// <summary>
/// The cpp file containing the definition of nontemplated Scope functions declared in Scope.h.
/// </summary>

#include "pch.h"
#include "Scope.h"

using namespace glm;
using namespace std;
using namespace FIEAGameEngine;

RTTI_DEFINITIONS(Scope);


Scope::Scope(Scope* const parent, size_t const & hashMapSize) :
	mHashMap(hashMapSize), mParent(parent)
{

}

FIEAGameEngine::Scope::Scope(Scope const & other)
{
	*this = other;
}

Scope::~Scope()
{
	Clear();
}

Scope & FIEAGameEngine::Scope::operator=(Scope const & rhs)
{
	if (*this != rhs)
	{
		Clear();
	}
	for (size_t i = 0; i < rhs.mVector.Size(); i++)
	{
		Datum & newDatum = Append(rhs.mVector[i]->first);
		if (rhs.mVector[i]->second.Type() != Datum::DatumType::Scope)
		{
			newDatum = rhs.mVector[i]->second;
		}
		else
		{
			for (size_t j = 0; j < rhs.mVector[i]->second.Size(); j++)
			{
				(newDatum.PushBack(*(new Scope(rhs.mVector[i]->second[j]))))->mParent = this;
			}
		}
	}
	return *this;
}

Datum * Scope::Find(string const & key) const
{
	if (key == "")
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
	if (key == "")
	{
		throw exception(scopeCannotHaveEmptyKeyExceptionText.c_str());
	}
	Datum * result = Find(key);
	if (result == nullptr)
	{
		if (mParent != nullptr)
		{
			result = mParent->Search(key, scopeAddress);
		}
	}
	else if(scopeAddress != nullptr)
	{
		*scopeAddress = this;
	}
	return result;
}

Datum & Scope::Append(string const & key)
{
	if (key == "")
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
	if (HasAncestor(childToAdopt))
	{
		throw exception(mayNotAdoptAncestorExceptionText.c_str());
	}

	childToAdopt.Orphan();
	childToAdopt.mParent = this;
	Append(newChildKey).PushBack(childToAdopt);
	
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
	//Should do less comparisons than simply comparing hashmaps although that is a valid, easier to read option.
	bool result = false;
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
	return result;
}

bool FIEAGameEngine::Scope::operator!=(Scope const & rhs) const
{
	return !(*this == rhs);
}

string const Scope::FindName(Scope * const searchedScope)
{
	string result = "";
	if (searchedScope->mParent == this)
	{
		for (size_t i = 0; i < this->mVector.Size(); i++)
		{
			PairType* storedPair = this->mVector[i];
			for (size_t j = 0; j < storedPair->second.Size(); j++)
			{
				if (storedPair->second.Type() == Datum::DatumType::Scope && &(storedPair->second[j]) == searchedScope)
				{
					result = storedPair->first;
					break;
				}
			}
			if (result != "")
			{
				break;
			}
		}
	}
	return result;
}

bool FIEAGameEngine::Scope::HasAncestor(Scope const & scope)
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
	pair<Datum *, size_t> result = pair<Datum *, size_t>(nullptr, 0);
	if (searchedScope.mParent == this)
	{
		for (size_t i = 0; i < this->mVector.Size(); i++)
		{
			PairType* storedPair = this->mVector[i];
			for (size_t j = 0; j < storedPair->second.Size(); j++)
			{
				if (storedPair->second.Type() == Datum::DatumType::Scope && &(storedPair->second[j]) == &searchedScope)
				{
					result = pair<Datum *, size_t>(&storedPair->second, j);
					break;
				}
			}
			if (result != pair<Datum *, size_t>(nullptr, 0))
			{
				break;
			}
		}
	}
	return result;
}

size_t FIEAGameEngine::Scope::Size()
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

void Scope::Clear()
{
	Orphan();
	for (size_t i = 0; i < mVector.Size(); i++)
	{
		if (mVector[i]->second.Type() == Datum::DatumType::Scope)
		{
			for (size_t j = 0; j < mVector[i]->second.Size(); j++)
			{
				mVector[i]->second.Get<Scope*>(j)->mParent = nullptr;
				delete(mVector[i]->second.Get<Scope*>(j));
			}
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
