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
		TypeManager::GetTypeManager().RegisterType(AttributedFoo::TypeIdClass(), AttributedFoo::Signatures());
		TypeManager::GetTypeManager().RegisterType(Entity::TypeIdClass(), Entity::Signatures());
		TypeManager::GetTypeManager().RegisterType(Sector::TypeIdClass(), Sector::Signatures());
		TypeManager::GetTypeManager().RegisterType(World::TypeIdClass(), World::Signatures());
		TypeManager::GetTypeManager().RegisterType(ActionList::TypeIdClass(), ActionList::Signatures());
		TypeManager::GetTypeManager().RegisterType(ActionListWhile::TypeIdClass(), ActionListWhile::Signatures());
		TypeManager::GetTypeManager().RegisterType(ActionIncrement::TypeIdClass(), ActionIncrement::Signatures());
		TypeManager::GetTypeManager().RegisterType(CreateAction::TypeIdClass(), CreateAction::Signatures());
		TypeManager::GetTypeManager().RegisterType(DestroyAction::TypeIdClass(), DestroyAction::Signatures());
		TypeManager::GetTypeManager().RegisterType(ActionEvent::TypeIdClass(), ActionEvent::Signatures());
		TypeManager::GetTypeManager().RegisterType(ReactionAttributed::TypeIdClass(), ReactionAttributed::Signatures());
		TypeManager::GetTypeManager().RegisterType(EventMessageAttributed::TypeIdClass(), EventMessageAttributed::Signatures());
	}

	TEST_MODULE_CLEANUP(ClearTypeManager)
	{
		TypeManager::GetTypeManager().Clear();
	}
}