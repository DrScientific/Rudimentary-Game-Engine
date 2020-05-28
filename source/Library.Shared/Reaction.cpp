#include "pch.h"
#include "Reaction.h"

namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(Reaction)

	Reaction::Reaction(RTTI::IdType typeId, std::string const& name) : ActionList(typeId, name)
	{
	}
}