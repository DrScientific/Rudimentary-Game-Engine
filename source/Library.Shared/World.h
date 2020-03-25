#pragma once
#include "Attributed.h"
#include "Factory.h"
#include "WorldState.h"

namespace FIEAGameEngine
{
	class Sector;

	class World final :
		public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed);
	public:
		/// <summary>
		/// World Constructor.
		/// </summary>
		/// <param name="time">GameTime of the world to be used by world state.</param>
		explicit World(GameTime & time);

		/// <summary>
		/// World Constructor.
		/// </summary>
		/// <param name="time">GameTime of the world to be used by world state.</param>
		explicit World(GameTime & time, std::string const & name);

		/// <summary>
		/// Destructor.
		/// </summary>
		~World() = default;

		/// <summary>
		/// Adopts an existing scope placing it at the provided key. If the new key is the sectors key, verifies that the child scope is a sector. Removes the scope from it's previous parent.
		/// </summary>
		/// <param name="child">Scope to adopt.</param>
		/// <param name="newChildKey">Key to place the newly adopted scope at.</param>
		virtual void Adopt(Scope & child, std::string const & newChildKey) override;

		/// <summary>
		/// Returns the name of the world.
		/// </summary>
		/// <returns>The name of the world.</returns>
		std::string Name() const;

		/// <summary>
		/// Sets the name of the world.
		/// </summary>
		/// <param name="name">The new name of the world.</param>
		void SetName(std::string const & name);

		/// <summary>
		/// Returns the sectors contained by this world.
		/// </summary>
		/// <returns>The sectors contained by this world.</returns>
		Datum & Sectors();

		/// <summary>
		/// Returns the sectors contained by this world.
		/// </summary>
		/// <returns>The sectors contained by this world.</returns>
		Datum const & Sectors() const;

		/// <summary>
		/// Creates a new sector and inserts it into this world's Sectors attribute.
		/// </summary>
		/// <param name="className">Class name of the sector</param>
		/// <returns>A reference to the newly created sector.</returns>
		
		/// <summary>
		/// Creates a new sector and inserts it into this world's Sectors attribute.
		/// </summary>
		/// <param name="name">The name of the news sector</param>
		/// <returns>A reference to the newly created sector.</returns>
		Sector & CreateSector(std::string const & name);

		/// <summary>
		/// Calls the update call of the actions contained by the world.
		/// </summary>
		void Update();

		/// <summary>
		/// RTTI to string override. Returns "World".
		/// </summary>
		/// <returns>Returns "World".</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Virtual constructor overriden from scope.
		/// </summary>
		/// <returns>A pointer to the newly constructed object</returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// 
		/// </summary>
		void AddActionToGraveYard(Action * actionToDelete);

		/// <summary>
		/// Returns the signatures of entity.
		/// </summary>
		/// <returns>The signatures of entity.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// World state of the world.
		/// </summary>
		WorldState mState;

		/// <summary>
		/// World's current queue of events
		/// </summary>
		EventQueue mEventQueue;

		/// <summary>
		/// Name of sectors attribute in scope.
		/// </summary>
		inline static const std::string mSectorsKey = "Sectors";

		/// <summary>
		/// Index of sectors attribute in scope.
		/// </summary>
		inline static const int mSectorsIndex = 2;

	private:

		/// <summary>
		/// The name of the world.
		/// </summary>
		std::string mName;

		/// <summary>
		/// A vector of actions that need to be deleted.
		/// </summary>
		Vector<Action *> mGraveyard;

		/// <summary>
		/// 
		/// </summary>
		void ClearGraveYard();

		inline static const std::string nonSectorInSectorsText = "Only Sector objects can be added to the Sectors field.\n";
	};
}