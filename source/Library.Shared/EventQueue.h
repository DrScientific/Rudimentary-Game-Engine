#pragma once
#include "GameTime.h"
#include "Vector.h"
#include <chrono>
#include <memory>
#include <vector>
#include <thread>
#include <future>


namespace FIEAGameEngine
{
	class WorldState;

	class EventPublisher;

	/// <summary>
	/// Queue of a variety of events which are delivered to subscribers when they have expired.
	/// </summary>
	class EventQueue final
	{
	public:
		/// <summary>
		/// Defauklt Constructor
		/// </summary>
		EventQueue() = default;
		
		/// <summary>
		/// Default Destructor
		/// </summary>
		~EventQueue() = default;

		/// <summary>
		/// Enqueues and event on the event queue.
		/// </summary>
		/// <param name="eventToQueue">The event to queue.</param>
		/// <param name="currentTime">The time the event was queued.</param>
		/// <param name="delay">The delay from the time the event is queued to when the event should be published.</param>
		void Enqueue(std::shared_ptr<EventPublisher> eventToQueue, GameTime const& currentTime, std::chrono::milliseconds delay = std::chrono::milliseconds(0));

		/// <summary>
		/// Delivers the passed in event.
		/// </summary>
		/// <param name="eventToSend">The event to send.</param>
		void Send(std::shared_ptr<EventPublisher> eventToSend);

		/// <summary>
		/// Event queue update called in world update. Delivers expired events and removes them from the queue.
		/// </summary>
		/// <param name="worldState">The world state of the world containing the event queue. Used to compare world time to the expiration times of the events in the queue.</param>
		void Update(WorldState & worldState);

		/// <summary>
		/// Clears the event queue of elements.
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns whether the event queue is empty.
		/// </summary>
		/// <returns>Whether the event queue is empty.</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Returns the size of the event queue.
		/// </summary>
		/// <returns>The size of the event queue.</returns>
		size_t Size() const;

	private:
		
		/// <summary>
		/// Queue of events to publish.
		/// </summary>
		Vector<std::shared_ptr<EventPublisher>> mEvents;

		/// <summary>
		/// Queue of events waiting to be added to the event queue.
		/// </summary>
		Vector<std::shared_ptr<EventPublisher>> mPendingEvents;

		/// <summary>
		/// 
		/// </summary>
		mutable std::recursive_mutex mMutex;
	};
}
