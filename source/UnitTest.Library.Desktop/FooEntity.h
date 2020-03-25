#pragma once
#include "Entity.h"
#include "IEventSubscriber.h"

namespace UnitTests
{
	class FooEntity :
		public FIEAGameEngine::Entity, public FIEAGameEngine::IEventSubscriber
	{
	public:
		FooEntity();
		virtual ~FooEntity();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="publisher"></param>
		virtual void Notify(class FIEAGameEngine::EventPublisher const & publisher);

		int mData;
	};

	CONCRETE_FACTORY(FooEntity, FIEAGameEngine::Scope);
}