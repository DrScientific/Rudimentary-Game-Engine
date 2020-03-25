#include "pch.h"
#include "TypeManager.h"

using namespace glm;
using namespace std;
using namespace FIEAGameEngine;

TypeManager* TypeManager::mInstance = nullptr;

TypeManager& TypeManager::GetTypeManager()
{
	if (mInstance == nullptr)
	{
		mInstance = new TypeManager();
	}
	return *mInstance;
}

TypeManager::TypeManager() :
	SignatureMap()
{

}

TypeManager::~TypeManager()
{

}

void TypeManager::RegisterType(RTTI::IdType id, Vector<Attributed::Signature> signatures)
{
	SignatureMap.Insert(id, signatures);
}
Vector<Attributed::Signature> & TypeManager::GetTypeSignature(RTTI::IdType id)
{
	return SignatureMap.At(id);
}
void TypeManager::UnregisterType(RTTI::IdType id)
{
	SignatureMap.Remove(id);
}

void TypeManager::Clear()
{
	SignatureMap.Clear();
	delete mInstance;
	mInstance = nullptr;
}
