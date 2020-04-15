#pragma once
#include "ActionList.h"

namespace FIEAGameEngine
{
	class ActionListWhile :
		public ActionList
	{
		RTTI_DECLARATIONS(ActionListWhile, ActionList);
	public:
		/// <summary>
		/// Default action list while constructor
		/// </summary>
		/// <param name="name">Name of the action list</param>
		ActionListWhile(std::string const & name = std::string());

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">ActionListWhile to copy</param>
		ActionListWhile(ActionListWhile const & other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">ActionListWhile to assign to</param>
		/// <returns>Reference this</returns>
		ActionListWhile & operator=(ActionListWhile const & other) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">ActionListWhile to move</param>
		ActionListWhile(ActionListWhile && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">ActionListWhile to assign to</param>
		/// <returns>Reference to this</returns>
		ActionListWhile & operator=(ActionListWhile && other) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~ActionListWhile() = default;

		/// <summary>
		/// Virtual update call that iterates through all actions in the action list while.
		/// </summary>
		virtual void Update(WorldState & worldState) override;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// RTTI to string override. Returns "ActionListWhile".
		/// </summary>
		/// <returns>Returns "ActionList".</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Returns the signatures of action list.
		/// </summary>
		/// <returns>The signatures of action list.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of preamble attribute in action list while.
		/// </summary>
		inline static const std::string mConditionKey = "Condition";

		/// <summary>
		/// Name of preamble attribute in action list while.
		/// </summary>
		inline static const std::string mPreambleKey = "Preamble";

		/// <summary>
		/// Name of increment attribute in action list while.
		/// </summary>
		inline static const std::string mIncrementKey = "Increment";

	private:

		/// <summary>
		/// Conditon of the while loop
		/// </summary>
		int mCondition = 0;

		/// <summary>
		/// Index of preamble attribute in action list while.
		/// </summary>
		inline static const int mPreambleIndex = 5;

		/// <summary>
		/// Index of increment attribute in action list while.
		/// </summary>
		inline static const int mIncrementIndex = 6;
	};

	CONCRETE_FACTORY(ActionListWhile, Scope);
}
