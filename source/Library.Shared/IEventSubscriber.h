#pragma once
#include <thread>
#include <future>

namespace FIEAGameEngine
{
	/// <summary>
	/// Interface to inherit from for objects to subscribe to events.
	/// </summary>
	class IEventSubscriber
	{
	public:
		/// <summary>
		/// Default constructor
		/// </summary>
		IEventSubscriber() = default;

		/// <summary>
		/// Overridden destructors need to remove pointer of themselves from the event queue.
		/// </summary>
		virtual ~IEventSubscriber() = default;

		/// <summary>
		/// Virtual Notify method. Defines what a subscriber does when an event occurs.
		/// </summary>
		/// <param name="publisher">A constant reference to the event that was just delivered to the subscriber.</param>
		virtual void Notify(class EventPublisher const& publisher) = 0;

	protected:
		/// <summary>
		/// 
		/// </summary>
		std::mutex mMutex;
	};
}