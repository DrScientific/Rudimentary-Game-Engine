#pragma once

#include "pch.h"

#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "TypeManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;


namespace UnitTestLibraryDesktop
{

	TEST_MODULE_INITIALIZE(AddAttributedFooToTypeManager)
	{
		TypeManager::GetTypeManager().RegisterType(AttributedFoo::TypeIdClass(), AttributedFoo::Signatures());
		TypeManager::GetTypeManager().RegisterType(Entity::TypeIdClass(), Entity::Signatures());
		TypeManager::GetTypeManager().RegisterType(Sector::TypeIdClass(), Sector::Signatures());
		TypeManager::GetTypeManager().RegisterType(World::TypeIdClass(), World::Signatures());
	}

	TEST_MODULE_CLEANUP(ClearTypeManager)
	{
		TypeManager::GetTypeManager().Clear();
	}
}