#pragma once
#include "Action.h"
#include "Factory.h"

namespace FIEAGameEngine
{
	class CreateAction :
	public Action
{
		RTTI_DECLARATIONS(CreateAction, Action);
	public:
		/// <summary>
		/// Default create action constructor
		/// </summary>
		/// <param name="name">Name of the create action</param>
		CreateAction(std::string const & name = std::string());

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">CreateAction to copy</param>
		CreateAction(CreateAction const & other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">CreateAction to assign to</param>
		/// <returns>Reference this</returns>
		CreateAction & operator=(CreateAction const & rhs) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">CreateAction to move</param>
		CreateAction(CreateAction && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">CreateAction to assign to</param>
		/// <returns>Reference to this</returns>
		CreateAction & operator=(CreateAction && rhs) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~CreateAction() = default;

		/// <summary>
		/// Virtual update call that iterates through all actions in the create action.
		/// </summary>
		virtual void Update(WorldState &) override;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// RTTI to string override. Returns "CreateAction".
		/// </summary>
		/// <returns>Returns "CreateAction".</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Returns the signatures of create action.
		/// </summary>
		/// <returns>The signatures of create action.</returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Name of class name attribute in create action.
		/// </summary>
		inline static const std::string mClassNameKey = "ClassName";

		/// <summary>
		/// Index of actions attribute in create action.
		/// </summary>
		inline static const size_t mClassNameIndex = 2;

		/// <summary>
		/// Name of instance name attribute in create action.
		/// </summary>
		inline static const std::string mInstanceNameKey = "InstanceName";

		/// <summary>
		/// Index of instance name attribute in create action.
		/// </summary>
		inline static const size_t mInstanceIndex = 3;

	protected:

		/// <summary>
		/// Name of the class of the action we're creating.
		/// </summary>
		std::string mClassName;

		/// <summary>
		/// Name of the instance of the action we're creating.
		/// </summary>
		std::string mInstanceName;
	};

	CONCRETE_FACTORY(CreateAction, Scope);
};

