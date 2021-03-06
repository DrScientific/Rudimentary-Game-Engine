#include "pch.h"
#include "ActionIncrement.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement(std::string const& name) : Action(ActionIncrement::TypeIdClass(), name)
	{

	}

	void ActionIncrement::Update(WorldState &)
	{
		if (!mTargetName.empty())
		{
			Scope * targetScope = NameSearch(mTargetName, mTargetGameContainer);
			Datum * datumToIncrement = nullptr;

			while (datumToIncrement == nullptr && targetScope != nullptr)
			{
				datumToIncrement = targetScope->Find(mTargetAttribute);
				if (datumToIncrement == nullptr)
				{
					targetScope = targetScope->NameSearch(mTargetName, mTargetGameContainer);
				}
			}

			if (datumToIncrement != nullptr)
			{
				if (datumToIncrement->Type() == Datum::DatumType::Integer)
				{
					for (size_t i = 0; i < datumToIncrement->Size(); i++)
					{
						datumToIncrement->Set(static_cast<int>(datumToIncrement->Get<int>(i) + mStep), i);
					}
				}
			}
		}
	}

	gsl::owner<Scope*> ActionIncrement::Clone() const
	{
		return new ActionIncrement(*this);
	}

	std::string ActionIncrement::ToString() const
	{
		return ActionIncrement::TypeName();
	}

	const FIEAGameEngine::Vector<Attributed::Signature> ActionIncrement::Signatures()
	{
		
		return Action::Signatures() + Vector<Attributed::Signature>
		{
			{mTargetGameContainerKey, Datum::DatumType::String, 1, offsetof(ActionIncrement, mTargetGameContainer) },
			{mTargetNameKey, Datum::DatumType::String, 1, offsetof(ActionIncrement, mTargetName) },
			{mTargetAttributeKey, Datum::DatumType::String, 1, offsetof(ActionIncrement, mTargetAttribute) },
			{mStepKey, Datum::DatumType::Integer, 1, offsetof(ActionIncrement, mStep ) }
		};
	}
}