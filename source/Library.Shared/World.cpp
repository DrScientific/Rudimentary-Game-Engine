#include "pch.h"
#include "World.h"
#include "Sector.h"
#include "Factory.h"
#include "Action.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(World)

	World::World(GameTime * time, EventQueue * eventQueue) : Attributed(World::TypeIdClass()), mEventQueue(eventQueue), mState(*time)
	{
		assert(mVector[mSectorsIndex]->first == mSectorsKey);
		mState.mWorld = this;
	}

	World::World(string const & name, GameTime * time, EventQueue * eventQueue) : World(time, eventQueue)
	{
		mName = name;
	}

	void World::Adopt(Scope & child, string const & newChildKey)
	{
		if (newChildKey == mSectorsKey && !child.Is(Sector::TypeIdClass()))
		{
			throw exception(nonSectorInSectorsText.c_str());
		}
		Scope::Adopt(child, newChildKey);
	}

	string World::Name() const
	{
		return mName;
	}

	void World::SetName(string const & name)
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

	Sector & World::CreateSector(string const & name)
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
		mEventQueue->Update(mState);
	}

	string World::ToString() const
	{
		return  World::TypeName();
	}

	gsl::owner<Scope*> World::Clone() const
	{
		World * newWorld = new World(*this);
		newWorld->mState.mWorld = newWorld;
		newWorld->mState.mSector = nullptr;
		newWorld->mState.mEntity = nullptr;
		newWorld->mState.mAction = nullptr;
		return newWorld;
	}

	void World::AddActionToGraveYard(Action * actionToDelete)
	{
		if (mGraveyard.Find(actionToDelete) == mGraveyard.end())
		{
			mGraveyard.PushBack(actionToDelete);
		}
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