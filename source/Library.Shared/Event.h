#pragma once

#include "EventPublisher.h"
#include <set>
#include <memory>
#include <algorithm>

namespace FIEAGameEngine
{
	class IEventSubscriber;

	template <typename T>
	class Event :
		public EventPublisher
	{
		RTTI_DECLARATIONS(Event<T>, EventPublisher);
	public:
		
		/// <summary>
		/// Concrete Event Constructor
		/// </summary>
		/// <param name="message">The payload of the event.</param>
		Event(T const & message);

		/// <summary>
		/// Concrete Event Move Constructor
		/// </summary>
		/// <param name="message">The payload of the event.</param>
		Event(T const && message = T());

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The event we are creating a copy of.</param>
		Event(Event const & other) = default;

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The event we are creating a copy of.</param>
		Event(Event && other) = default;

		/// <summary>
		/// Assignment Operator.
		/// </summary>
		/// <param name="rhs">The event on the right hand side of the expression we are setting our event equal to.</param>
		/// <returns>A reference to the event on the left hand side of the operator.</returns>
		Event& operator=(Event const & rhs) = default;

		/// <summary>
		/// Move Assignment operator
		/// </summary>
		/// <param name="rhs">The event on the right hand side of the expression we are setting our event equal to.</param>
		/// <returns>A reference to the event on the left hand side of the operator.</returns>
		Event& operator=(Event && rhs) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~Event() = default;

		/// <summary>
		/// Subscurbes the passed in subscriber to the event.
		/// </summary>
		/// <param name="subscriber">The subscriber to subscribe to the event.</param>
		static void Subscribe(IEventSubscriber * subscriber);
		
		/// <summary>
		/// Unsubscribes the passed in subscriber from the event.
		/// </summary>
		/// <param name="subscriber">The subscriber to unsubscribe from the event.</param>
		static void Unsubscribe(IEventSubscriber * subscriber);

		/// <summary>
		/// Unsubscribes all subscribers from the event.
		/// </summary>
		static void UnsubscribeAll();

		/// <summary>
		/// Returns the message stored by the event.
		/// </summary>
		/// <returns></returns>
		T const & GetMessage() const;

		/// <summary>
		/// RTTI to string override. Returns "Event".
		/// </summary>
		/// <returns>Returns "Event".</returns>
		virtual std::string ToString() const override;


	private:

		/// <summary>
		/// The message stored by the event.
		/// </summary>
		T mMessage;

		/// <summary>
		/// A list of the event's subscribers.
		/// </summary>
		static std::set<IEventSubscriber *> mSubscribers;
	};
}

#include "Event.inl"