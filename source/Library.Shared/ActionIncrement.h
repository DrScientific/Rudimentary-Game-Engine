#pragma once
#include "Action.h"
#include "Factory.h"

namespace FIEAGameEngine
{
	class ActionIncrement final :
		public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);
	public:
		
		/// <summary>
		/// Default Action Increment constructor
		/// </summary>
		/// <param name="name">Name of the action list</param>
		ActionIncrement(std::string const& name = std::string());

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">ActionIncrement to copy</param>
		ActionIncrement(ActionIncrement const& other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">ActionIncrement to assign to</param>
		/// <returns>Reference this</returns>
		ActionIncrement & operator=(ActionIncrement const& other) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">ActionIncrement to move</param>
		ActionIncrement(ActionIncrement && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">ActionIncrement to assign to</param>
		/// <returns>Reference to this</returns>
		ActionIncrement & operator=(ActionIncrement && other) = default;

		/// <summary>
		/// 
		/// </summary>
		virtual ~ActionIncrement() = default;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// Virtual update call.
		/// </summary>
		virtual void Update(WorldState &) override;

		/// <summary>
		/// RTTI to string override. Returns "ActionIncrement".
		/// </summary>
		/// <returns>Returns "ActionIncrement".</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Returns the signatures of action increment.
		/// </summary>
		/// <returns>The signatures of action increment.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of target game container attribute in action increment.
		/// </summary>
		inline static const std::string mTargetGameContainerKey = "TargetGameContainer";

		/// <summary>
		/// Name of target name attribute in action increment.
		/// </summary>
		inline static const std::string mTargetNameKey = "TargetName";

		/// <summary>
		/// Name of target attribute attribute in action increment.
		/// </summary>
		inline static const std::string mTargetAttributeKey = "TargetAttribute";

		/// <summary>
		/// Name of step attribute in action increment.
		/// </summary>
		inline static const std::string mStepKey = "Step";

	protected:
		
		/// <summary>
		/// Key of object types we check for the attribute in. Examples : "Actions", "Entities", "Sectors"...
		/// </summary>
		std::string mTargetGameContainer;

		/// <summary>
		/// Name of the object instance in the game container.
		/// </summary>
		std::string mTargetName;

		/// <summary>
		/// Name of the attribute in the object instance.
		/// </summary>
		std::string mTargetAttribute;

		/// <summary>
		/// 
		/// </summary>
		int mStep = 1;
	};

	CONCRETE_FACTORY(ActionIncrement, Scope);
}