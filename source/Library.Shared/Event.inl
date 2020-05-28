#include "Event.h"
#include "IEventSubscriber.h"

using namespace std;

namespace FIEAGameEngine
{
	template<typename T>
	std::set<IEventSubscriber *> Event<T>::mSubscribers;

	template<typename T>
	std::recursive_mutex Event<T>::mMutex;

	template<typename T>
	RTTI_DEFINITIONS(Event<T>);

	template<typename T>
	inline Event<T>::Event(T const& message) : EventPublisher(&mSubscribers, &mMutex), mMessage(message)
	{

	}

	template<typename T>
	inline Event<T>::Event(T const&& message) : EventPublisher(&mSubscribers, &mMutex), mMessage(message)
	{
	}

	template<typename T>
	inline void Event<T>::Subscribe(IEventSubscriber & subscriber)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		mSubscribers.insert(&subscriber);
	}

	template<typename T>
	inline void Event<T>::Unsubscribe(IEventSubscriber & subscriber)
	{
		lock_guard<recursive_mutex> lock(mMutex);
		mSubscribers.erase(&subscriber);
	}

	template<typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		lock_guard<recursive_mutex> lock(mMutex);
		mSubscribers.clear();
	}

	template<typename T>
	inline bool Event<T>::HasSubscribers()
	{
		lock_guard<recursive_mutex> lock(mMutex);
		return mSubscribers.size();
	}

	

	template<typename T>
	inline T const& Event<T>::GetMessage() const
	{
		lock_guard<recursive_mutex> lock(mMutex);
		return mMessage;
	}
	template<typename T>
	inline std::string Event<T>::ToString() const
	{
		lock_guard<recursive_mutex> lock(mMutex);
		return "Event";
	}
}