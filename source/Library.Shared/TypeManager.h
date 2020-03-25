#pragma once
#include "Vector.h"
#include "HashMap.h"
#include "RTTI.h"
#include "Attributed.h"


namespace FIEAGameEngine
{

	class TypeManager
	{
	public:
		static TypeManager & GetTypeManager();

	private:

		TypeManager();
		~TypeManager();

		static TypeManager* mInstance;

		HashMap <RTTI::IdType const, Vector <Attributed::Signature>> SignatureMap;

	public:
		TypeManager(TypeManager const &) = delete;
		void operator=(TypeManager const&) = delete;

		void RegisterType(RTTI::IdType id, Vector <Attributed::Signature> signatures);
		Vector<Attributed::Signature> & GetTypeSignature(RTTI::IdType id);
		void UnregisterType(RTTI::IdType id);
		void Clear();
	};

}