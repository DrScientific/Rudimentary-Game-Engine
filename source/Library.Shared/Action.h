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
		Action & operator=(Action const & rhs) = default;

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
		Action & operator=(Action && rhs) = default;

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
		/// Sets the name field of the action
		/// </summary>
		/// /// <param name="name">The new name of the action.</param>
		void SetName(std::string const & name);

		/// <summary>
		/// Virtual update call that varies on concrete actions.
		/// </summary>
		virtual void Update(WorldState & worldState)= 0;

		/// <summary>
		/// Name of name attribute in action.
		/// </summary>
		inline static const std::string mNameKey = "Name";

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
		/// Index of name attribute in action.
		/// </summary>
		inline static const int mNameIndex = 1;

		inline static const std::string actionCannotExistWithoutParentExceptionText = "Action cannot exist without parent. Pass a non null parameter into the constructor.\n";
	};
}