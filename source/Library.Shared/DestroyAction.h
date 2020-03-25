#pragma once
#include "Action.h"
#include "Factory.h"

namespace FIEAGameEngine
{
	class DestroyAction :
		public Action
	{
		RTTI_DECLARATIONS(DestroyAction, Action);
	public:
		/// <summary>
		/// Default destroy action constructor
		/// </summary>
		/// <param name="name">Name of the destroy action</param>
		DestroyAction(std::string const & name = std::string());

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">DestroyAction to copy</param>
		DestroyAction(DestroyAction const & other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">DestroyAction to assign to</param>
		/// <returns>Reference this</returns>
		DestroyAction & operator=(DestroyAction const & rhs) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">DestroyAction to move</param>
		DestroyAction(DestroyAction && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">DestroyAction to assign to</param>
		/// <returns>Reference to this</returns>
		DestroyAction & operator=(DestroyAction && rhs) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~DestroyAction() = default;

		/// <summary>
		/// Virtual update call that iterates through all actions in the destroy action.
		/// </summary>
		virtual void Update(WorldState & worldState) override;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// RTTI to string override. Returns "DestroyAction".
		/// </summary>
		/// <returns>Returns "DestroyAction".</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Returns the signatures of destroy action.
		/// </summary>
		/// <returns>The signatures of destroy action.</returns>
		static const Vector<Signature> Signatures();

		/// <summary>
		/// Name of target attribute in destroy action.
		/// </summary>
		inline static const std::string mTargetKey = "Target";

	protected:

		/// <summary>
		/// Name of the instance of the action we're destroying.
		/// </summary>
		std::string mTarget;
	};

	CONCRETE_FACTORY(DestroyAction, Scope);
}