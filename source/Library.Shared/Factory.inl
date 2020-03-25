#include "pch.h"
#include "Factory.h"

using namespace std;

namespace FIEAGameEngine
{
	template<typename AbstractProductT>
	HashMap<std::string const, Factory<AbstractProductT> const * > Factory<AbstractProductT>::sFactoryTable;

	
	template<typename AbstractProductT>
	inline Factory<AbstractProductT> const * Factory<AbstractProductT>::Find(std::string const & className)
	{
		Factory<AbstractProductT> const * foundPtr = nullptr;
		HashMap<std::string const, Factory<AbstractProductT> const * >::Iterator foundIt = sFactoryTable.Find(className);
		if (foundIt != sFactoryTable.end())
		{
			foundPtr = (*foundIt).second;
		}
		return foundPtr;
	}

	template<typename AbstractProductT>
	inline gsl::owner<AbstractProductT*> Factory<AbstractProductT>::Create(std::string const & className)
	{
		Factory<AbstractProductT> const * foundPtr = nullptr;
		AbstractProductT * newProduct = nullptr;
		
		foundPtr = Find(className);
		if (foundPtr != nullptr)
		{
			newProduct = foundPtr->Create();
		}
		return newProduct;
	}

	template<typename AbstractProductT>
	inline void Factory<AbstractProductT>::Add(Factory<AbstractProductT> & pFactory)
	{
		if (Find(pFactory.GetClassName()) != nullptr)
		{
			throw exception(cannotCreateDuplicateFactory.c_str());
		}
		sFactoryTable.Insert(pFactory.GetClassName(), &pFactory);
	}

	template<typename AbstractProductT>
	inline void Factory<AbstractProductT>::Remove(Factory<AbstractProductT> & pFactory)
	{
		sFactoryTable.Remove(pFactory.GetClassName());
	}
}