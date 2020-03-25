#include "pch.h"
#include "Entity.h"
#include "Sector.h"
#include "Action.h"
#include "WorldState.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity(std::string const & name) : Entity(Entity::TypeIdClass(), name)
	{

	}

	Entity::Entity(RTTI::IdType typeId) : Entity(typeId, string())
	{

	}

	Entity::Entity(RTTI::IdType typeId, string const & name) : Attributed(typeId), mName(name)
	{
		assert(mVector[mActionsIndex]->first == mActionsKey);
		mName = name;
	}

	void Entity::Adopt(Scope & child, std::string const & newChildKey)
	{
		if (newChildKey == mActionsKey && !child.Is(Action::TypeIdClass()))
		{
			throw exception(nonActionInActionsText.c_str());
		}
		Scope::Adopt(child, newChildKey);
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
			sectorPtr = mParent->As<Sector>();
		}
		return sectorPtr;
	}

	void Entity::SetSector(Sector * const newSector)
	{
		if (newSector == nullptr)
		{
			Orphan();
		}
		else
		{
			newSector->Adopt(*this, newSector->mEntitiesKey);
		}
	}

	bool Entity::IsAwake() const
	{
		return mIsAwake ? true : false;
	}

	void Entity::SetIsAwake(bool const & awake)
	{
		awake ? mIsAwake = 1 : mIsAwake = 0;
	}

	void Entity::Wake()
	{
		mIsAwake = 1;
	}

	void Entity::Sleep()
	{
		mIsAwake = 0;
	}

	Datum & Entity::Actions()
	{
		return operator[](mActionsIndex);
	}

	Datum const & Entity::Actions() const
	{
		return operator[](mActionsIndex);
	}

	Action & Entity::CreateAction(std::string name, std::string className)
	{
		Scope * newScope = Factory<Scope>::Create(className);
		assert(newScope->Is(Action::TypeIdClass()));
		Action * newAction = static_cast<Action*>(newScope);
		newAction->SetName(name);
		Adopt(*newAction, mActionsKey);
		return *newAction;
	}

	void Entity::Update(WorldState & worldState)
	{
		if (mIsAwake)
		{
			Datum & actions = Actions();
			for (size_t i = 0; i < actions.Size(); i++)
			{
				worldState.mAction = static_cast<Action*>(&actions[i]);
				static_cast<Action*>(&actions[i])->Update(worldState);
			}
			worldState.mAction = nullptr;
		}
	}

	std::string Entity::ToString() const
	{
		return Entity::TypeName();
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
			{"IsAwake", Datum::DatumType::Integer, 1, offsetof(Entity, mIsAwake) },
			{ mActionsKey, Datum::DatumType::Scope, 0, 0 }
		};
	}

	
}