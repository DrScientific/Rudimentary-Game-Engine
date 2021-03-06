#pragma once
#include "GameClock.h"
#include "GameTime.h"
#include "EventQueue.h"

namespace FIEAGameEngine
{
	class World;
	class Sector;
	class Entity;
	class Action;

	class WorldState
	{
	public:
		/// <summary>
		/// 
		/// </summary>
		WorldState(GameTime & time);
		
		/// <summary>
		/// 
		/// </summary>
		~WorldState() = default;
		
		/// <summary>
		/// 
		/// </summary>
		World * mWorld = nullptr;
		
		/// <summary>
		/// 
		/// </summary>
		Sector * mSector = nullptr;
		
		/// <summary>
		/// 
		/// </summary>
		Entity * mEntity = nullptr;
		
		/// <summary>
		/// 
		/// </summary>
		Action * mAction = nullptr;

		/// <summary>
		/// 
		/// </summary>
		GameTime * mGameTime = nullptr;
		
	};

}