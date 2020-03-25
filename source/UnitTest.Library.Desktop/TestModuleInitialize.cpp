#pragma once

#include "pch.h"

#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "Action.h"
#include "ActionList.h"
#include "CreateAction.h"
#include "DestroyAction.h"
#include "ActionListWhile.h"
#include "ActionIncrement.h"
#include "TypeManager.h"
#include "ActionEvent.h"
#include "EventMessageAttributed.h"
#include "ReactionAttributed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace FIEAGameEngine;

namespace UnitTestLibraryDesktop
{

	TEST_MODULE_INITIALIZE(AddAttributedFooToTypeManager)
	{
		REGISTER_TYPE(AttributedFoo);
		REGISTER_TYPE(Entity);
		REGISTER_TYPE(Sector);
		REGISTER_TYPE(World);
		REGISTER_TYPE(ActionList);
		REGISTER_TYPE(ActionListWhile);
		REGISTER_TYPE(ActionIncrement);
		REGISTER_TYPE(CreateAction);
		REGISTER_TYPE(DestroyAction);
		REGISTER_TYPE(ActionEvent);
		REGISTER_TYPE(ReactionAttributed);
		REGISTER_TYPE(EventMessageAttributed);
	}

	TEST_MODULE_CLEANUP(ClearTypeManager)
	{
		TypeManager::Clear();
	}
}