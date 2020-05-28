#pragma once
#include "ActionList.h"
#include "Factory.h"
#include <chrono>

namespace FIEAGameEngine
{
	/// <summary>
	/// An action that queues an event when update is called on the action.
	/// The event queued stores an EventMessageAttributed payload which passes the auxilliary attributes of the action event on to the reaction attributed.
	/// Because many reactions will be listening for an EventMessageAttributedEvent
	/// </summary>
	class ActionEvent :
		public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);
	public:
		
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="name">Action Event Name</param>
		/// <param name="delay">Action Event </param>
		ActionEvent(std::string const& name = std::string(), int const& delay = 0);
		
		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~ActionEvent() = default;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<ActionEvent*> Clone() const override;

		/// <summary>
		/// Create an attributed event, assign its world and subtype, copy all auxiliary parameters into the event and queue the event with the given delay.
		/// </summary>
		/// <param name="worldState"></param>
		void Update(WorldState & worldState);

		/// <summary>
		/// Returns the signatures of action event.
		/// </summary>
		/// <returns>The signatures of action event.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of subtype attribute in action.
		/// </summary>
		inline static const std::string mSubtypeKey = "Subtype";

		/// <summary>
		/// Name of delay attribute in action.
		/// </summary>
		inline static const std::string mDelayKey = "Delay";

	private:

		/// <summary>
		/// The subtype of the action event.
		/// </summary>
		std::string mSubtype;

		/// <summary>
		/// The delay of the reaction.
		/// </summary>
		int mDelay = 0;
	};
	
	CONCRETE_FACTORY(ActionEvent, Scope)
}