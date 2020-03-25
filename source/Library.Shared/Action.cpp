#include "pch.h"
#include "Action.h"
#include "Entity.h"

using namespace std;

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Action)

	Action::Action(RTTI::IdType typeId, std::string const & name) : Attributed(typeId), mName(name)
	{

	}

	std::string Action::Name() const
	{
		return mName;
	}

	void Action::SetName(std::string const & name)
	{
		mName = name;
	}
}