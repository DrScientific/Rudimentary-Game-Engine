#include "Event.h"
#include "IEventSubscriber.h"

namespace FIEAGameEngine
{
	template<typename T>
	std::set<IEventSubscriber *> Event<T>::mSubscribers;

	template<typename T>
	RTTI_DEFINITIONS(Event<T>);

	template<typename T>
	inline Event<T>::Event(T const & message) : EventPublisher(&mSubscribers), mMessage(message)
	{

	}

	template<typename T>
	inline Event<T>::Event(T const && message) : EventPublisher(&mSubscribers), mMessage(message)
	{
	}

	template<typename T>
	inline void Event<T>::Subscribe(IEventSubscriber * subscriber)
	{
		mSubscribers.insert(subscriber);
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(IEventSubscriber * subscriber)
	{
		mSubscribers.erase(subscriber);
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		mSubscribers.clear();
	}

	template<typename T>
	inline T const & Event<T>::GetMessage() const
	{
		return mMessage;
	}
	template<typename T>
	inline std::string Event<T>::ToString() const
	{
		return "Event";
	}
}