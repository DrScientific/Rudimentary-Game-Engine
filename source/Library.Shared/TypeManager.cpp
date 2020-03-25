#include "pch.h"
#include "TypeManager.h"

using namespace glm;
using namespace std;
using namespace FIEAGameEngine;

TypeManager::TypeRegistryType TypeManager::TypeRegistryMap;
//HashMap<RTTI::IdType const, Vector<Attributed::Signature>> TypeManager::SignaturesMap;


void FIEAGameEngine::TypeManager::RegisterType(RTTI::IdType id, Vector<Attributed::Signature> const& signatures, RTTI::IdType parentId)
{
	TypeRegistryMap.Insert(id, TypeRegistryEntry(signatures, parentId));
}

void FIEAGameEngine::TypeManager::RegisterType(RTTI::IdType id, Vector<Attributed::Signature>&& signatures, RTTI::IdType parentId)
{
	TypeRegistryMap.Insert(id, TypeRegistryEntry(std::move(signatures), parentId));
}

void FIEAGameEngine::TypeManager::UnregisterType(RTTI::IdType id)
{
	TypeRegistryMap.Remove(id);
	//SignaturesMap.Remove(id);
}

//Vector<Attributed::Signature> const& FIEAGameEngine::TypeManager::GetSignatures(RTTI::IdType id)
Vector<Attributed::Signature> FIEAGameEngine::TypeManager::GetSignatures(RTTI::IdType id)
{
	Vector<Attributed::Signature> signatures;
	Stack<RTTI::IdType> inheritanceChain = GetInheritanceChain(id);
	while (!inheritanceChain.IsEmpty())
	{
		signatures += GetDerivedMostSignatures(inheritanceChain.Top());
		inheritanceChain.Pop();
	}
	return signatures;
	
	//This method would cache all constructed signature vectors in a hashmap so we don't have to looke it up everytime, but because this dynamically allocates memory for a static object
	//CRTDBG returns a false positive on memory leaks. Because of this I've chosen to
	/*std::pair<bool, Vector<Attributed::Signature>*> foundSignatures = SignaturesMap.ContainsKey(id);
	if (foundSignatures.first)
	{
		return *(foundSignatures.second);
	}
	else
	{
		Vector<Attributed::Signature> signatures;
		Stack<RTTI::IdType> inheritanceChain = GetInheritanceChain(id);
		while (!inheritanceChain.IsEmpty())
		{
			signatures += GetDerivedMostSignatures(inheritanceChain.Top());
			inheritanceChain.Pop();
		}
		return (*(SignaturesMap.Insert(id, signatures).second)).second;
	}*/
}



size_t FIEAGameEngine::TypeManager::GetSignatureCount(RTTI::IdType id)
{
	return TypeRegistryMap.At(id).Signatures.Size();
}

std::pair<bool, RTTI::IdType> FIEAGameEngine::TypeManager::FindParentId(RTTI::IdType id)
{
	std::pair<bool, TypeRegistryEntry const*> foundParentId = TypeRegistryMap.ContainsKey(id);
	if (foundParentId.first)
	{
		return { foundParentId.first, foundParentId.second->ParentId };
	}
	else
	{
		return { false, 0 };
	}

}

Stack<RTTI::IdType> FIEAGameEngine::TypeManager::GetInheritanceChain(RTTI::IdType id)
{
	Stack<RTTI::IdType> chain;
	std::pair<bool, TypeRegistryEntry const*> foundTypeRegistryEntry = TypeRegistryMap.ContainsKey(id);
	while (foundTypeRegistryEntry.first)
	{
		chain.Push(id);
		id = foundTypeRegistryEntry.second->ParentId;
		foundTypeRegistryEntry = TypeRegistryMap.ContainsKey(id);
	}
	return chain;
}

void FIEAGameEngine::TypeManager::Clear()
{
	TypeRegistryMap.Clear();
	//SignaturesMap.Clear();
}

Vector<Attributed::Signature> const& FIEAGameEngine::TypeManager::GetDerivedMostSignatures(RTTI::IdType id)
{
	return TypeRegistryMap.At(id).Signatures;
}

FIEAGameEngine::TypeManager::TypeRegistryEntry::TypeRegistryEntry(Vector<Attributed::Signature> const& signatures, RTTI::IdType parentId) :
	Signatures(signatures), ParentId(parentId)
{

}

FIEAGameEngine::TypeManager::TypeRegistryEntry::TypeRegistryEntry(Vector<Attributed::Signature>&& signatures, RTTI::IdType parentId) :
	Signatures(std::move(signatures)), ParentId(std::move(parentId))
{

}
