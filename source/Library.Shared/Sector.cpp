#include "pch.h"
#include "Sector.h"
#include "Entity.h"
#include "World.h"
#include "Factory.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Sector)

	Sector::Sector(World * const world) : Attributed(TypeIdClass())
	{
		mParent = world;
	}

	Sector::~Sector()
	{
	}

	void Sector::Adopt(Scope & child, std::string const & newChildKey)
	{
		if (newChildKey == "Entities" && !child.Is(Entity::TypeIdClass()))
		{
			throw exception(nonEntityInEntitiesText.c_str());
		}
		Scope::Adopt(child, newChildKey);
	}

	std::string Sector::Name()
	{
		return mName;
	}

	void Sector::SetName(std::string name)
	{
		mName = name;
	}

	World const * Sector::GetWorld()
	{
		World * worldPtr = nullptr;
		if (mParent != nullptr)
		{
			assert(mParent->Is(World::TypeIdClass()));
			worldPtr = static_cast<World*>(mParent);
		}
		return worldPtr;
	}

	void Sector::SetWorld(World * const newWorld)
	{
		newWorld->Adopt(*this, "Sectors");
	}

	bool Sector::IsAwake() const
	{
		return mIsAwake ? true : false;
	}

	void Sector::SetIsAwake(bool const & awake)
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
		return *Find("Entities");
	}

	Entity & Sector::CreateEntity(std::string name, std::string className)
	{
		Scope * newScope = Factory<Scope>::Create(className);
		assert(newScope->Is(Entity::TypeIdClass()));
		Entity * newEntity = static_cast<Entity*>(newScope);
		newEntity->SetName(name);
		Adopt(*newEntity, "Entities");
		return *newEntity;
	}

	void Sector::Update(WorldState & worldState)
	{
		if (mIsAwake)
		{
			Datum entities = *Find("Entities");
			for (size_t i = 0; i < entities.Size(); i++)
			{
				static_cast<Entity*>(&entities[i])->Update(worldState);
			}
		}
	}

	std::string Sector::ToString() const
	{
		return "Sector";
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
			{"Entities", Datum::DatumType::Scope, 0, 0 },
		};
	}

}