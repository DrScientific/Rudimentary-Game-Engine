#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Factory.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(World)

	World::World(GameTime time) : Attributed(TypeIdClass()), mState(time)
	{
	}

	void World::Adopt(Scope & child, std::string const & newChildKey)
	{
		if (newChildKey == "Sectors" && !child.Is(Sector::TypeIdClass()))
		{
			throw exception(nonSectorInSectorsText.c_str());
		}
		Scope::Adopt(child, newChildKey);
	}

	std::string World::Name()
	{
		return mName;
	}

	void World::SetName(std::string name)
	{
		mName = name;
	}

	Datum & World::Sectors()
	{
		return *Find("Sectors");
	}

	Sector & World::CreateSector(std::string name, std::string className)
	{
		Scope * newScope = Factory<Scope>::Create(className);
		assert(newScope->Is(Sector::TypeIdClass()));
		Sector * newSector = static_cast<Sector*>(newScope);
		newSector->SetName(name);
		Adopt(*newSector, "Sectors");
		return *newSector;

	}

	bool World::IsAwake() const
	{
		return mIsAwake ? true : false;
	}

	void World::SetIsAwake(bool const & awake)
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

	void World::Wake()
	{
		mIsAwake = 1;
	}

	void World::Sleep()
	{
		mIsAwake = 0;
	}

	void World::Update(WorldState & worldState)
	{
		Datum & sectors = *Find("Sectors");
		for (size_t i = 0; i < sectors.Size(); i++)
		{
			static_cast<Sector*>(&sectors[i])->Update(worldState);
		}
	}

	std::string World::ToString() const
	{
		return "World";
	}

	gsl::owner<Scope*> World::Clone() const
	{
		return new World(*this);
	}

	const FIEAGameEngine::Vector<Attributed::Signature> World::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{"Name", Datum::DatumType::String, 1, offsetof(World, mName) },
			{"IsAwake", Datum::DatumType::Integer, 1, offsetof(World, mIsAwake) },
			{"Sectors", Datum::DatumType::Scope, 0, 0 },
		};
	}
}