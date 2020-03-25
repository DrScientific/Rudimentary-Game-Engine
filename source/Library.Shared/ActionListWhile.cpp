#include "pch.h"
#include "ActionListWhile.h"
#include "WorldState.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionListWhile);

	ActionListWhile::ActionListWhile(std::string const & name) : ActionList(ActionListWhile::TypeIdClass(), name)
	{
	}

	void ActionListWhile::Update(WorldState & worldState)
	{
		Datum& actions = operator[](mActionsIndex);
		Datum & preambleActions = operator[](mPreambleIndex);
		Datum & incrementActions = operator[](mIncrementIndex);

		
		for (size_t i = 0; i < preambleActions.Size(); i++)
		{
			worldState.mAction = static_cast<Action*>(&preambleActions[i]);
			static_cast<Action*>(&preambleActions[i])->Update(worldState);
		}
		worldState.mAction = nullptr;

		while (mCondition)
		{

			for (size_t i = 0; i < actions.Size(); i++)
			{
				worldState.mAction = static_cast<Action*>(&actions[i]);
				static_cast<Action*>(&actions[i])->Update(worldState);
			}
			worldState.mAction = nullptr;

			for (size_t i = 0; i < incrementActions.Size(); i++)
			{
				worldState.mAction = static_cast<Action*>(&incrementActions[i]);
				static_cast<Action*>(&incrementActions[i])->Update(worldState);
			}
			worldState.mAction = nullptr;
		}
		worldState.mAction = nullptr;
		
	}

	gsl::owner<Scope*> ActionListWhile::Clone() const
	{
		return new ActionListWhile(*this);
	}

	std::string ActionListWhile::ToString() const
	{
		return ActionListWhile::TypeName();
	}

	const Vector<Attributed::Signature> ActionListWhile::Signatures()
	{

		return Vector<Attributed::Signature>
		{
			{ mConditionKey, Datum::DatumType::Integer, 1, offsetof(ActionListWhile, mCondition) },
			{ mPreambleKey, Datum::DatumType::Scope, 0, 0 },
			{ mIncrementKey, Datum::DatumType::Scope, 0, 0 }
		};
	}
}