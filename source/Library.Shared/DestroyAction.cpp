#include "pch.h"
#include "DestroyAction.h"
#include "WorldState.h"
#include "World.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(DestroyAction);

	DestroyAction::DestroyAction(std::string const& name) : Action(DestroyAction::TypeIdClass(), name)
	{

	}

	void DestroyAction::Update(WorldState & worldState)
	{
		Action* actionToDelete = static_cast<Action*>(NameSearch(mTarget, "Actions"));
		if (actionToDelete != nullptr)
		{
			worldState.mWorld->AddActionToGraveYard(actionToDelete);
		}
	}

	gsl::owner<Scope*> DestroyAction::Clone() const
	{
		return new DestroyAction(*this);
	}

	std::string DestroyAction::ToString() const
	{
		return DestroyAction::TypeName();
	}

	const Vector<Attributed::Signature> DestroyAction::Signatures()
	{
		return Action::Signatures() + Vector<Attributed::Signature>
		{
			{mTargetKey, Datum::DatumType::String, 1, offsetof(DestroyAction, mTarget) }
		};
	}
}