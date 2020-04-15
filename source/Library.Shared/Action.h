#pragma once
#include "Attributed.h"

namespace FIEAGameEngine
{
	class Entity;
	class WorldState;

	/// <summary>
	/// 
	/// </summary>
	class Action :
		public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);
	public:
		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">Action to copy</param>
		Action(Action const & other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">Action to assign to</param>
		/// <returns>Reference this</returns>
		Action & operator=(Action const & other) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">Action to move</param>
		Action(Action && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">Action to assign to</param>
		/// <returns>Reference to this</returns>
		Action & operator=(Action && other) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~Action() = default;

		/// <summary>
		/// Returns the name of the action
		/// </summary>
		/// <returns>The name of the action</returns>
		std::string const & Name() const;


		/// <summary>
		/// Returns whether the action should only be called every update.
		/// </summary>
		/// <returns>Whether the action should only be called every update.</returns>
		bool IsContinuous() const;

		/// <summary>
		/// Sets the name field of the action
		/// </summary>
		/// <param name="name">The new name of the action.</param>
		void SetName(std::string const & name);

		/// <summary>
		/// Set the new state as to whether the action should only be called every update.
		/// </summary>
		/// <param name="isContinuous">The new state as to whether the action should only be called every update.</param>
		void SetIsContinuous(bool isContinuous);

		/// <summary>
		/// Virtual update call that varies on concrete actions.
		/// </summary>
		virtual void Update(WorldState & worldState)= 0;


		/// <summary>
		/// Returns the signatures of action.
		/// </summary>
		/// <returns>The signatures of action.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of name attribute in action.
		/// </summary>
		inline static const std::string mNameKey = "Name";

		/// <summary>
		/// Name of IsContinuous attribute in action.
		/// </summary>
		inline static const std::string mIsContinuousKey = "IsContinuous";

	protected:

		/// <summary>
		/// Action Consturctor. All other constructors forwarded to this constructor.
		/// </summary>
		/// <param name="typeId">RTTI type ID of derived action.</param>
		/// <param name="name">Name of the action.</param>
		Action(RTTI::IdType typeId, std::string const & name = std::string());

		/// <summary>
		/// The name of the action.
		/// </summary>
		std::string mName;

		/// <summary>
		/// Whether the action should only be called every update. If not the action is call on this update, then removed from the event queue.
		/// </summary>
		int mIsContinuous = 0;

		inline static const std::string actionCannotExistWithoutParentExceptionText = "Action cannot exist without parent. Pass a non null parameter into the constructor.\n";
	};
}