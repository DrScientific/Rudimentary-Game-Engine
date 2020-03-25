
#include "pch.h"
#include "Attributed.h"
#include "TypeManager.h"

namespace FIEAGameEngine
{
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

	Attributed::Attributed(Attributed && other) :
		Scope(std::move(other))
	{
		(*this)["this"] = this;
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

	Attributed & Attributed::operator=(Attributed && other)
	{
		Scope::operator=(std::move(other));
		(*this)["this"] = this;
		UpdateExternalStorage(other.TypeIdInstance());
		return *this;
	}

	Attributed::~Attributed()
	{
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
			for (size_t i = 0; i < TypeManager::GetTypeManager().GetTypeSignature(TypeIdInstance()).Size() + 1; i++)
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

	Vector<Scope::PairType*> Attributed::Attributes()
	{
		return mVector;
	}

	Vector<Scope::PairType*> Attributed::PrescribedAttributes()
	{
		Vector<PairType*> prescribedAttributes;
		for (size_t i = 0; i < TypeManager::GetTypeManager().GetTypeSignature(TypeIdInstance()).Size() + 1; i++)
		{
			prescribedAttributes.PushBack(mVector[i]);
		}
		return prescribedAttributes;
	}


	Vector<Scope::PairType*> Attributed::AuxiliaryAttributes()
	{
		Vector<PairType*> auxiliaryAttributes;
		for (size_t i = TypeManager::GetTypeManager().GetTypeSignature(TypeIdInstance()).Size() + 1; i < mVector.Size(); i++)
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

	gsl::owner<Scope*> Attributed::Clone()
	{
		return new Attributed(*this);
	}

	void Attributed::Populate(IdType id)
	{
		(*this)["this"] = this;
		Vector<Signature> attributes = TypeManager::GetTypeManager().GetTypeSignature(id);
		for (size_t i = 0; i < attributes.Size(); i++)
		{
			Datum & element = Append(attributes[i].mName);
			element.SetType(attributes[i].mType);
			if (attributes[i].mType != Datum::DatumType::Scope)
			{
				element.SetStorage(reinterpret_cast<uint8_t*>(this) + attributes[i].mOffset, attributes[i].mSize);
			}
			else
			{
				for (size_t j = 0; j < attributes[i].mSize; j++)
				{
					AppendScope(attributes[i].mName);
				}
			}
		}
	}
	void Attributed::UpdateExternalStorage(IdType id)
	{
		(*this)["this"] = this;
		Vector<Signature> attributes = TypeManager::GetTypeManager().GetTypeSignature(id);
		for (size_t i = 0; i < attributes.Size(); i++)
		{
			if (mVector[i + 1]->second.Type() != Datum::DatumType::Scope)
			{
				mVector[i + 1]->second.SetStorage(reinterpret_cast<uint8_t*>(this) + attributes[i].mOffset, attributes[i].mSize * mVector[i]->second.mTypeSizes[static_cast<size_t>(attributes[i].mType)]);
			}
		}
	}
}