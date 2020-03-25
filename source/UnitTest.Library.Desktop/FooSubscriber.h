#pragma once
#include "IEventSubscriber.h"

namespace UnitTests
{
	class FooSubscriber :
		public FIEAGameEngine::IEventSubscriber
	{
	public:
		
		/// <summary>
		/// 
		/// </summary>
		FooSubscriber(int data = 0);

		/// <summary>
		/// 
		/// </summary>
		~FooSubscriber();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="publisher"></param>
		virtual void Notify(class FIEAGameEngine::EventPublisher const & publisher) override;

		int mData = 0;

	private:

		
	};

}