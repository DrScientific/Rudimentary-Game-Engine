#include "pch.h"
#include "CreateAction.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(CreateAction);

	CreateAction::CreateAction(std::string const& name) : Action(CreateAction::TypeIdClass(), name)
	{

	}

	void CreateAction::Update(WorldState &)
	{
		Scope * newScope = Factory<Scope>::Create(mClassName);
		assert(newScope->Is(Action::TypeIdClass()));
		Action * newAction = static_cast<Action*>(newScope);
		newAction->SetName(mInstanceName);
		mParent->Adopt(*newAction, "Actions");
	}

	gsl::owner<Scope*> CreateAction::Clone() const
	{
		return new CreateAction(*this);
	}

	std::string CreateAction::ToString() const
	{
		return CreateAction::TypeName();
	}

	const Vector<Attributed::Signature> CreateAction::Signatures()
	{
		return Action::Signatures() + Vector<Attributed::Signature>
		{
			{mClassNameKey, Datum::DatumType::String, 1, offsetof(CreateAction, mClassName)},
			{mInstanceNameKey, Datum::DatumType::String, 1, offsetof(CreateAction, mInstanceName) }
		};
	}
}