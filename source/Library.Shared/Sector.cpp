#include "pch.h"
#include "Sector.h"
#include "Entity.h"
#include "World.h"
#include "Factory.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Sector)


	Sector::Sector(string const & name) : Attributed(Sector::TypeIdClass())
	{
		mName = name;
	}

	void Sector::Adopt(Scope & child, std::string const & newChildKey)
	{
		if (newChildKey == mEntitiesKey && !child.Is(Entity::TypeIdClass()))
		{
			throw exception(nonEntityInEntitiesText.c_str());
		}
		Scope::Adopt(child, newChildKey);
	}

	std::string Sector::Name() const
	{
		return mName;
	}

	void Sector::SetName(std::string const & name)
	{
		mName = name;
	}

	World const * Sector::GetWorld() const
	{
		World * worldPtr = nullptr;
		if (mParent != nullptr)
		{
			worldPtr = mParent->As<World>();
		}
		return worldPtr;
	}

	void Sector::SetWorld(World * const newWorld)
	{
		if (newWorld == nullptr)
		{
			Orphan();
		}
		else
		{
			newWorld->Adopt(*this, newWorld->mSectorsKey);
		}
	}

	bool Sector::IsAwake() const
	{
		return mIsAwake ? true : false;
	}

	void Sector::SetIsAwake(bool const & awake)
	{
		awake ? mIsAwake = 1 : mIsAwake = 0;
	}

	void Sector::Wake()
	{
		mIsAwake = 1;
	}

	void Sector::Sleep()
	{
		mIsAwake = 0;
	}

	Datum & Sector::Entities()
	{
		return operator[](mEntitiesIndex);
	}

	Datum const & Sector::Entities() const
	{
		return operator[](mEntitiesIndex);
	}

	Entity & Sector::CreateEntity(std::string name, std::string className)
	{
		Scope * newScope = Factory<Scope>::Create(className);
		assert(newScope->Is(Entity::TypeIdClass()));
		Entity * newEntity = static_cast<Entity*>(newScope);
		newEntity->SetSector(this);
		newEntity->SetName(name);
		Adopt(*newEntity, mEntitiesKey);
		return *newEntity;
	}

	void Sector::Update(WorldState & worldState)
	{
		if (mIsAwake)
		{
			Datum & entities = Entities();
			for (size_t i = 0; i < entities.Size(); i++)
			{
				worldState.mEntity = static_cast<Entity*>(&entities[i]);
				static_cast<Entity*>(&entities[i])->Update(worldState);
			}
			worldState.mEntity = nullptr;
		}
	}

	std::string Sector::ToString() const
	{
		return Sector::TypeName();
	}

	gsl::owner<Scope*> Sector::Clone() const
	{
		return new Sector(*this);
	}

	const FIEAGameEngine::Vector<Attributed::Signature> Sector::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{"Name", Datum::DatumType::String, 1, offsetof(Sector, mName) },
			{"IsAwake", Datum::DatumType::Integer, 1, offsetof(Sector, mIsAwake) },
			{ mEntitiesKey, Datum::DatumType::Scope, 0, 0 }
		};
	}

}