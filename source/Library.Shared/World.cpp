#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Factory.h"
#include "Action.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(World)

	World::World(GameTime time) : Attributed(TypeIdClass()), mState(time)
	{
		assert(mVector[mSectorsIndex]->first == mSectorsKey);
		mState.mWorld = this;
	}

	World::World(GameTime time, std::string const & name) : World(time)
	{
		mName = name;
	}

	void World::Adopt(Scope & child, std::string const & newChildKey)
	{
		if (newChildKey == mSectorsKey && !child.Is(Sector::TypeIdClass()))
		{
			throw exception(nonSectorInSectorsText.c_str());
		}
		Scope::Adopt(child, newChildKey);
	}

	std::string World::Name() const
	{
		return mName;
	}

	void World::SetName(std::string const & name)
	{
		mName = name;
	}

	Datum & World::Sectors()
	{
		return operator[](mSectorsIndex);
	}

	Datum const & World::Sectors() const
	{
		return operator[](mSectorsIndex);
	}

	Sector & World::CreateSector(std::string const & name)
	{
		Sector* newSector = new Sector();
		newSector->SetWorld(this);
		newSector->SetName(name);
		Adopt(*newSector, mSectorsKey);
		return *newSector;
	}

	void World::Update()
	{
		Datum & sectors = Sectors();
		for (size_t i = 0; i < sectors.Size(); i++)
		{
			mState.mSector = static_cast<Sector*>(&sectors[i]);
			static_cast<Sector*>(&sectors[i])->Update(mState);
		}
		mState.mSector = nullptr;
		ClearGraveYard();
	}

	std::string World::ToString() const
	{
		return  World::TypeName();
	}

	gsl::owner<Scope*> World::Clone() const
	{
		return new World(*this);
	}

	void World::AddActionToGraveYard(Action * actionToDelete)
	{
		mGraveyard.PushBack(actionToDelete);
	}

	const FIEAGameEngine::Vector<Attributed::Signature> World::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{"Name", Datum::DatumType::String, 1, offsetof(World, mName) },
			{mSectorsKey, Datum::DatumType::Scope, 0, 0 }
		};
	}

	void World::ClearGraveYard()
	{
		for (size_t i = 0; i < mGraveyard.Size(); i++)
		{
			mGraveyard[i]->Orphan();
		}
		for (size_t i = 0; i < mGraveyard.Size(); i++)
		{
			delete mGraveyard[i];
		}
		mGraveyard.Clear();
	}
}