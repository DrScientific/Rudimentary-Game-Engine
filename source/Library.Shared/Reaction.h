#pragma once
#include "ActionList.h"
#include "IEventSubscriber.h"

namespace FIEAGameEngine
{
	/// <summary>
	/// An abstract class that is both action list and an event subscriber.
	/// </summary>
	class Reaction :
		public ActionList, public IEventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList);
	public:

		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~Reaction() = default;



		/// <summary>
		/// Virtual update call that overrides action list update, such that no behavior is executed on update.
		/// </summary>
		virtual void Update(WorldState &) {};

	protected:
		/// <summary>
		/// Action Consturctor. All other constructors forwarded to this constructor.
		/// </summary>
		/// <param name="typeId">RTTI type ID of derived action.</param>
		/// <param name="name">Name of the action.</param>
		Reaction(RTTI::IdType typeId, std::string const & name = std::string());
	};

	
}