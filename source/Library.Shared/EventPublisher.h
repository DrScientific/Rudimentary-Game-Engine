#pragma once
#include "RTTI.h"
#include <set>
#include <chrono>
#include <memory>
#include <thread>
#include <future>

namespace FIEAGameEngine
{
	class IEventSubscriber;

	/// <summary>
	/// Abstract base class of events. Allows the Event queue to store a variety of event types.
	/// </summary>
	class EventPublisher :
		public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI);
	public:
		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The event publisher we are creating a copy of.</param>
		EventPublisher(EventPublisher const & other) = default;

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The event publisher we are creating a copy of.</param>
		EventPublisher(EventPublisher && other) = default;


		/// <summary>
		/// Assignment Operator.
		/// </summary>
		/// <param name="rhs">The event publisher on the right hand side of the expression we are setting our event publisher equal to.</param>
		/// <returns>A reference to the event publisher on the left hand side of the operator.</returns>
		EventPublisher& operator=(EventPublisher const & rhs) = default;

		/// <summary>
		/// Move Assignment operator
		/// </summary>
		/// <param name="rhs">The event publisher on the right hand side of the expression we are setting our event publisher equal to.</param>
		/// <returns>A reference to the event publisher on the left hand side of the operator.</returns>
		EventPublisher& operator=(EventPublisher && rhs) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~EventPublisher() = default;

		/// <summary>
		/// Sets the time the event was queued as well as it's delay until it is ready to be published.
		/// </summary>
		/// <param name="timeEnqueued">The time the event was enqueued (typically the current time.)</param>
		/// <param name="delay">The delay until the event is ready to be published.</param>
		void SetTime(std::chrono::high_resolution_clock::time_point timeEnqueued, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/// <summary>
		/// Returns the time the event was placed on the event queue
		/// </summary>
		/// <returns>The time the event was placed on the event queue.</returns>
		std::chrono::high_resolution_clock::time_point TimeEnqueued() const;

		/// <summary>
		/// Returns the number of milliseconds the event should wait to be published after the time it was enqueued.
		/// </summary>
		/// <returns>The number of milliseconds the event should wait to be published after the time it was enqueued.</returns>
		std::chrono::milliseconds Delay() const;

		/// <summary>
		/// Given a current time returns if the event should be published.
		/// </summary>
		/// <returns>Whether the event should be published.</returns>
		bool IsExpired(std::chrono::high_resolution_clock::time_point currentTime) const;

		/// <summary>
		/// Calls notify on all subscribers subscribed to this event. 
		/// </summary>
		void Deliver();

	protected:
		/// <summary>
		/// Constructs an event publisher given a pointer to the set of event subscribers. Only called by a concrete event's constructor.
		/// </summary>
		/// <param name="subscribers">List of event subscribers contained by the concrete event.</param>
		EventPublisher(std::set<IEventSubscriber *> * const subscribers, std::recursive_mutex * const lock);

	private:

		/// <summary>
		/// Pointer to the set of event subscriber pointers stored in the concrete event. This pointer is set on construction when the subscriber pointer is passed
		/// </summary>
		std::set<IEventSubscriber *> * const mSubscribersPtr;

		/// <summary>
		/// The time the event was placed on the event queue.
		/// </summary>
		std::chrono::high_resolution_clock::time_point mTimeEnqueued;

		/// <summary>
		/// The number of milliseconds the event should wait to be published after the time it was enqueued.
		/// </summary>
		std::chrono::milliseconds mDelay;

		/// <summary>
		/// 
		/// </summary>
		std::recursive_mutex* const mMutexPtr;
	};

}