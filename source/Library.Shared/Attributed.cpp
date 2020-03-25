
#include "pch.h"
#include "Attributed.h"
#include "TypeManager.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Attributed);

	Attributed::Signature::Signature(string name, Datum::DatumType type, size_t size, size_t offset) :
		mName(name), mType(type), mSize(size), mOffset(offset)
	{
	}


	Attributed::Attributed(RTTI::IdType id)
	{
		Populate(id);
	}

	Attributed::Attributed(Attributed const & other)
	{
		*this = other;
	}

	Attributed::Attributed(Attributed && other) noexcept :
		Scope(std::move(other))
	{
		UpdateExternalStorage(other.TypeIdInstance());
	}

	Attributed & Attributed::operator=(Attributed const & other)
	{
		if (this != &other)
		{
			Scope::operator=(other);
			UpdateExternalStorage(other.TypeIdInstance());
		}
		return *this;
	}

	Attributed & Attributed::operator=(Attributed && other) noexcept
	{
		Scope::operator=(std::move(other));
		UpdateExternalStorage(other.TypeIdInstance());
		return *this;
	}

	bool Attributed::IsAttribute(string const & name) const
	{
		return mHashMap.ContainsKey(name).first;
	}

	bool Attributed::IsPrescribedAttribute(string const & name) const
	{
		bool result = false;
		if (IsAttribute(name))
		{
			for (size_t i = 0; i < TypeManager::GetSignatures(TypeIdInstance()).Size() + 1; i++)
			{
				if (mVector[i]->first == name)
				{
					result = true;
					break;
				}
			}
		}
		return result;
	}

	bool Attributed::IsAuxiliaryAttribute(string const & name) const
	{
		bool result = false;
		if (mHashMap.ContainsKey(name).first && !IsPrescribedAttribute(name))
		{
			result = true;
		}
		return result;
	}

	Datum & Attributed::AppendAuxiliaryAttribute(string const & name)
	{
		Datum * appendedDatum = nullptr;
		if (IsPrescribedAttribute(name))
		{
			throw exception(cannotAppendAuxiliaryAttributeUnderPrescribedNameExceptionText.c_str());
		}
		appendedDatum = &(Append(name));
		
		return *appendedDatum;
	}

	Datum & Attributed::AppendAuxiliaryAttribute(string const & name, Datum const & value)
	{
		Datum * appendedDatum = nullptr;
		if (IsPrescribedAttribute(name))
		{
			appendedDatum = Find(name);
		}
		else
		{
			Datum & newDatum = Append(name);
			newDatum = value;
			appendedDatum = &newDatum;
		}

		return *appendedDatum;
	}

	Vector<Scope::PairType*> const & Attributed::Attributes()
	{
		return mVector;
	}

	Vector<Scope::PairType*> Attributed::PrescribedAttributes() const
	{
		Vector<PairType*> prescribedAttributes;
		for (size_t i = 0; i < TypeManager::GetSignatures(TypeIdInstance()).Size() + 1; i++)
		{
			prescribedAttributes.PushBack(mVector[i]);
		}
		return prescribedAttributes;
	}


	Vector<Scope::PairType*> Attributed::AuxiliaryAttributes() const
	{
		Vector<PairType*> auxiliaryAttributes;
		for (size_t i = TypeManager::GetSignatures(TypeIdInstance()).Size() + 1; i < mVector.Size(); i++)
		{
			auxiliaryAttributes.PushBack(mVector[i]);
		}
		return auxiliaryAttributes;
	}

	void Attributed::Clear()
	{
		Scope::Clear();
		Populate(TypeIdInstance());
	}

	gsl::owner<Scope*> Attributed::Clone() const
	{
		return new Attributed(*this);
	}

	std::string Attributed::ToString() const
	{
		return "Attributed";
	}

	void Attributed::Populate(IdType id)
	{
		(*this)["this"] = this;
		Vector<Signature> const & attributes = TypeManager::GetSignatures(id);
		for (size_t i = 0; i < attributes.Size(); i++)
		{
			Signature const & currentSignature = attributes[i];
			Datum & element = Append(currentSignature.mName);
			element.SetType(currentSignature.mType);
			if (currentSignature.mType != Datum::DatumType::Scope)
			{
				element.SetStorage(reinterpret_cast<uint8_t*>(this) + currentSignature.mOffset, currentSignature.mSize);
			}
			//Appending scopes is not necessary as our parser will append scopes as needed. 
			//TODO: Verify this.
			else
			{
				for (size_t j = 0; j < currentSignature.mSize; j++)
				{
					AppendScope(currentSignature.mName);
				}
			}
		}
	}
	void Attributed::UpdateExternalStorage(IdType id)
	{
		(*this)["this"] = this;
		Vector<Signature> const & attributes = TypeManager::GetSignatures(id);
		for (size_t i = 0; i < attributes.Size(); i++)
		{
			Signature currentSignature = attributes[i];
			if (currentSignature.mType != Datum::DatumType::Scope)
			{
				mVector[i+1]->second.SetStorage(reinterpret_cast<uint8_t*>(this) + currentSignature.mOffset, currentSignature.mSize);
			}
		}
	}
}