#include "pch.h"
#include "CreateAction.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(CreateAction);

	CreateAction::CreateAction(std::string const & name) : Action(CreateAction::TypeIdClass(), name)
	{

	}

	void CreateAction::Update(WorldState &)
	{
		Scope * newScope = Factory<Scope>::Create(mClassName);
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
		return Vector<Attributed::Signature>
		{
			{"Name", Datum::DatumType::String, 1, offsetof(CreateAction, mName) },
			{"ClassName", Datum::DatumType::String, 1, offsetof(CreateAction, mClassName)},
			{"InstanceName", Datum::DatumType::String, 1, offsetof(CreateAction, mInstanceName) }
		};
	}
}