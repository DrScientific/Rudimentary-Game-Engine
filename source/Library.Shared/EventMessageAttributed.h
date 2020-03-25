#pragma once
#include "Attributed.h"

namespace FIEAGameEngine
{
	/// <summary>
	/// A payload for events to pass auxilliary attributes to reactions.
	/// </summary>
	class EventMessageAttributed :
		public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed);
	public:

		/// <summary>
		/// Constructor which takes in a subtyoe and a world pointer.
		/// </summary>
		/// <param name="subtype">Subtype of the event message attributed.</param>
		/// <param name="mWorld">World pointer of the event message attributed.</param>
		EventMessageAttributed(std::string subtype, class World * mWorld);

		/// <summary>
		/// Constructor which takes in a subtyoe, a world pointer, and a vector of auxiliary attributes to append.
		/// </summary>
		/// <param name="subtype">Subtype of the event message attributed.</param>
		/// <param name="mWorld">World pointer of the event message attributed.</param>
		/// <param name="auxilliaryAttributes">Auxiliary attributes to append to the EventMessageAttributed.</param>
		EventMessageAttributed(std::string subtype, class World * mWorld, Vector<std::pair<std::string const, Datum>*> auxilliaryAttributes);
		
		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~EventMessageAttributed();

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// Returns the subtype of the Event Message Attributed.
		/// </summary>
		/// <returns>The subtype of the Event Message Attributed.</returns>
		std::string const & Subtype() const;

		/// <summary>
		/// Returns the signatures of event message attributed.
		/// </summary>
		/// <returns>The signatures of event message attributed.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of subtype attribute in event message attributed.
		/// </summary>
		inline static const std::string mSubtypeKey = "Subtype";

		/// <summary>
		/// Name of subtype attribute in event message attributed.
		/// </summary>
		inline static const std::size_t mSubtypeIndex = 1;


		/// <summary>
		/// The subtype of the Event Message Attributed.
		/// </summary>
		std::string mSubtype;

		/// <summary>
		/// The world containing the Event Message Attributed.
		/// </summary>
		class World * mWorld;

	};

}