#include "pch.h"
#include "Action.h"
#include "Entity.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Action)

	Action::Action(RTTI::IdType typeId, std::string const& name) : Attributed(typeId), mName(name)
	{

	}

	std::string const& Action::Name() const
	{
		return mName;
	}

	bool Action::IsContinuous() const
	{
		return mIsContinuous;
	}

	void Action::SetName(std::string const& name)
	{
		mName = name;
	}

	void Action::SetIsContinuous(bool isContinuous)
	{
		mIsContinuous = isContinuous;
	}

	const FIEAGameEngine::Vector<Attributed::Signature> Action::Signatures()
	{
		return Vector<Attributed::Signature>
		{
			{ mNameKey, Datum::DatumType::String, 1, offsetof(Action, mName) },
			{ mIsContinuousKey, Datum::DatumType::Integer, 1, offsetof(Action, mIsContinuous) }
		};
	}
}