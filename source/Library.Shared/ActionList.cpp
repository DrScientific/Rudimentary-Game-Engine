#include "pch.h"
#include "ActionList.h"
#include "WorldState.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList(std::string const & name) : Action(ActionList::TypeIdClass(), name)
	{

	}

	ActionList::ActionList(RTTI::IdType typeId, string const & name) : Action(typeId, name)
	{

	}

	void ActionList::Adopt(Scope & child, std::string const & newChildKey)
	{
		if (newChildKey == mActionsKey && !child.Is(Action::TypeIdClass()))
		{
			throw exception(nonActionInActionsText.c_str());
		}
		Scope::Adopt(child, newChildKey);
	}

	Datum & ActionList::Actions()
	{
		return operator[](mActionsIndex);
	}

	Datum const & ActionList::Actions() const
	{
		return operator[](mActionsIndex);
	}

	Action & ActionList::CreateAction(std::string name, std::string className)
	{
		Scope * newScope = Factory<Scope>::Create(className);
		assert(newScope->Is(Action::TypeIdClass()));
		Action * newAction = static_cast<Action*>(newScope);
		newAction->SetName(name);
		Adopt(*newAction, mActionsKey);
		return *newAction;
	}

	void ActionList::Update(WorldState & worldState)
	{
		Datum & actions = Actions();
		for (size_t i = 0; i < actions.Size(); i++)
		{
			worldState.mAction = static_cast<Action*>(&actions[i]);
			static_cast<Action*>(&actions[i])->Update(worldState);
		}
		worldState.mAction = nullptr;
	}

	gsl::owner<Scope*> ActionList::Clone() const
	{
		return new ActionList(*this);
	}

	std::string ActionList::ToString() const
	{
		return ActionList::TypeName();
	}

	const Vector<Attributed::Signature> ActionList::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{mNameKey, Datum::DatumType::String, 1, offsetof(ActionList, mName) },
			{ mActionsKey, Datum::DatumType::Scope, 0, 0 }
		};
	}
}