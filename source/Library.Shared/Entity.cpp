#include "pch.h"
#include "Entity.h"
#include "Sector.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity(Sector * const sector) : Attributed(TypeIdClass())
	{
		mParent = sector;
	}

	Entity::~Entity()
	{
	}

	string Entity::Name() const
	{
		return mName;
	}

	void Entity::SetName(string const & name)
	{
		mName = name;
	}

	Sector const * Entity::GetSector() const
	{
		Sector * sectorPtr = nullptr;
		if (mParent != nullptr)
		{
			assert(mParent->Is(Sector::TypeIdClass()));
			sectorPtr = static_cast<Sector*>(mParent);
		}
		return sectorPtr;
	}

	void Entity::SetSector(Sector * const newSector)
	{
		newSector->Adopt(*this, "Entities");
	}

	bool Entity::IsAwake() const
	{
		return mIsAwake ? true : false;
	}

	void Entity::SetIsAwake(bool const & awake)
	{
		if (awake)
		{
			mIsAwake = 1;
		}
		else
		{
			mIsAwake = 0;
		}
	}

	void Entity::Wake()
	{
		mIsAwake = 1;
	}

	void Entity::Sleep()
	{
		mIsAwake = 0;
	}

	void Entity::Update(WorldState & worldState)
	{
		if (mIsAwake)
		{
			//TODO Iterate through actions
			worldState;
		}
	}

	std::string Entity::ToString() const
	{
		return "Entity";
	}

	gsl::owner<Scope*> Entity::Clone() const
	{
		return new Entity(*this);
	}

	const Vector<Attributed::Signature> Entity::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{"Name", Datum::DatumType::String, 1, offsetof(Entity, mName) },
			{"IsAwake", Datum::DatumType::Integer, 1, offsetof(Entity, mIsAwake) }
		};
	}
}