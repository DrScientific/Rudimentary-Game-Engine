#pragma once
#include "HashMap.h"
#include "Attributed.h"
#include "Stack.h"


#define REGISTER_TYPE(Type) TypeManager::RegisterType(Type::TypeIdClass(), Type::Signatures(), Type::ParentTypeIdClass());

namespace FIEAGameEngine
{
	class TypeManager final
	{
	public:
		TypeManager() = delete;
		TypeManager(TypeManager const &) = delete;
		TypeManager(TypeManager &&) = delete;
		TypeManager& operator=(TypeManager const&) = delete;
		TypeManager operator=(TypeManager &&) = delete;
		~TypeManager() = default;

		static void RegisterType(RTTI::IdType id, Vector <Attributed::Signature> const & signatures, RTTI::IdType parentId);
		static void RegisterType(RTTI::IdType id, Vector <Attributed::Signature> && signatures, RTTI::IdType parentId);
		static void UnregisterType(RTTI::IdType id);
		static Vector<Attributed::Signature> GetSignatures(RTTI::IdType id);
		
		//See comment above SignaturesMap at end of file.
		//static Vector<Attributed::Signature> const & GetSignatures(RTTI::IdType id);

		static size_t GetSignatureCount(RTTI::IdType id);
		static std::pair<bool, RTTI::IdType> FindParentId(RTTI::IdType id);
		
		
		static void Clear();

	private:
		static Vector<Attributed::Signature> const& GetDerivedMostSignatures(RTTI::IdType id);
		static Stack<RTTI::IdType> GetInheritanceChain(RTTI::IdType id);

		struct TypeRegistryEntry final
		{
			TypeRegistryEntry(Vector<Attributed::Signature> const & signatures, RTTI::IdType parentId);
			TypeRegistryEntry(Vector<Attributed::Signature>&& signatures, RTTI::IdType parentId);

			Vector<Attributed::Signature> const Signatures;
			RTTI::IdType const ParentId;
		};

		using TypeRegistryType = HashMap<RTTI::IdType const, TypeRegistryEntry const>;
		static TypeRegistryType TypeRegistryMap;
		
		//It would be nice to use this as a cache for signatures retrieved from the type registry map, but that dynamically allocates static memory which returns a false positive for
		//memory leaks in CRTDBG
		//static HashMap<RTTI::IdType const, Vector<Attributed::Signature>> SignaturesMap;
	};

}