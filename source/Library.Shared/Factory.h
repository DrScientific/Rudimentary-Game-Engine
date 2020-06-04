#pragma once
#include <string>
#include "UnorderedMap.h"
#include <gsl/gsl>
#include <assert.h>

namespace FIEAGameEngine
{
	/// <summary>
	/// The Factory class serves two roles, that of an abstract factory from which all factories derive, as well as the role of a singleton factory manager class.
	/// It constains a static unordered map of all concrete factories that can produce objects of types derived from the Factory's templated type.
	/// </summary>
	template <class AbstractProductT> class Factory
	{
	public:
		/// <summary>
		/// Default factory constructor
		/// </summary>
		Factory() = default;
		
		/// <summary>
		/// Default factory virtual destructor
		/// </summary>
		virtual ~Factory() = default;
		
		/// <summary>
		/// Pure virtual function which returns the name of the classes the concrete factory instantiates.
		/// </summary>
		/// <returns>The name of the class the factory produces.</returns>
		virtual std::string const GetClassName() const = 0;
		
		/// <summary>
		/// Static method which returns the factory which produces objects with the type of the passed in class name.
		/// </summary>
		/// <param name="className">Name of the class we want the factory of.</param>
		/// <returns>A pointer to the concerete factory th</returns>
		static Factory<AbstractProductT> const* Find(std::string const& className);
		
		/// <summary>
		/// Static method which returns a pointer to a newly created object of type className, if a concrete factory of that type exists. Otherwise returns nullptr.
		/// </summary>
		/// <param name="className">The class name of the object type we wish to instantiate.</param>
		/// <returns>A pointer to a newly created object of type className, if a concrete factory of that type exists. Otherwise returns nullptr.</returns>
		static gsl::owner<AbstractProductT*> Create(std::string const& className);

	protected:
		/// <summary>
		/// Adds a concrete factory to the static unorederd map of factories where it's key is the name of the products it produces.
		/// </summary>
		/// <param name="pFactory">A reference to the factory we are adding to the static unordered map.</param>
		static void Add(Factory<AbstractProductT> & pFactory);

		/// <summary>
		/// Removes a concrete factory from the static unordered map of factories.
		/// </summary>
		/// <param name="pFactory">A reference to the factory we are removing from the static unordered map.</param>
		static void Remove(Factory<AbstractProductT> & pFactory);

	private:
		
		/// <summary>
		/// Returns a pointer to a newly created object which the concrete factory can produce.
		/// </summary>
		/// <returns>Returns a pointer to a newly created object which the concrete factory can produce.</returns>
		virtual gsl::owner<AbstractProductT*> Create() const = 0;

		/// <summary>
		/// Static unordered map of concrete factories that have been created. A factory's key is the class name of the productes it creates.
		/// </summary>
		static UnorderedMap<std::string const, Factory<AbstractProductT> const* > sFactoryTable;

		/// <summary>
		/// Communicats the cause of a Cannot Create Duplicate Factory exception to the user.
		/// </summary>
		inline static const std::string cannotCreateDuplicateFactory = "Factory already exists, cannot create duplicate factory.\n";
	};

	/// <summary>
	/// Concerete Factory macro. Can be placed in the header file of any class inorder to allow for the declaration of a factory of that class type.
	/// </summary>
	#define CONCRETE_FACTORY( ConcreteProductT, AbstractProductT )							\
    class ConcreteProductT ## Factory final: FIEAGameEngine::Factory<AbstractProductT>		\
    {																						\
        public:																				\
			ConcreteProductT ## Factory()  { Add   ( *this ) ; }							\
			~ConcreteProductT ## Factory()  { Remove( *this ) ; }							\
            virtual std::string const GetClassName() const									\
			{ return # ConcreteProductT ; }													\
            virtual gsl::owner<AbstractProductT *>  Create() const							\
            {																				\
                AbstractProductT * product = new ConcreteProductT() ;						\
                assert( product != nullptr ) ;												\
                return product ;															\
            }																				\
	};	

}


#include "Factory.inl"