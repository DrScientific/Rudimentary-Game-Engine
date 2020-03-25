#pragma once
#include "Scope.h"

namespace FIEAGameEngine
{
	class ActionScope :
		public Scope
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		ActionScope();
		
		/// <summary>
		/// 
		/// </summary>
		virtual ~ActionScope() = 0;


	};

}