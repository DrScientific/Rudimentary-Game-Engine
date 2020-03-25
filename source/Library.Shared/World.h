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
		explicit World(GameTime time);

		/// <summary>
		/// Destructor.
		/// </summary>
		~World() = default;

		/// <summary>
		/// Adopts an existing scope placing it at the provided key. If the new key is "Sectors", verifies that the child scope is a sector. Removes the scope from it's previous parent.
		/// </summary>
		/// <param name="child">Scope to adopt.</param>
		/// <param name="newChildKey">Key to place the newly adopted scope at.</param>
		virtual void Adopt(Scope & child, std::string const & newChildKey) override;

		/// <summary>
		/// Returns the name of the world.
		/// </summary>
		/// <returns>The name of the world.</returns>
		std::string Name();

		/// <summary>
		/// Sets the name of the world.
		/// </summary>
		/// <param name="name">The new name of the world.</param>
		void SetName(std::string name);

		/// <summary>
		/// Returns the sectors contained by this world.
		/// </summary>
		/// <returns>The sectors contained by this world.</returns>
		Datum & Sectors();

		/// <summary>
		/// Creates a new sector and inserts it into this world's Sectors attribute.
		/// </summary>
		/// <param name="className">Class name of the sector</param>
		/// <returns>A reference to the newly created sector.</returns>
		Sector & CreateSector(std::string name, std::string className);

		/// <summary>
		/// Returns whether the world is awake.
		/// </summary>
		/// <returns>Whether the world is awake.</returns>
		bool IsAwake() const;

		/// <summary>
		/// Sets whether the world is awake.
		/// </summary>
		void SetIsAwake(bool const & awake);

		/// <summary>
		/// Wakes the world.
		/// </summary>
		void Wake();

		/// <summary>
		/// Puts the world to sleep.
		/// </summary>
		void Sleep();

		/// <summary>
		/// Calls the update call of the actions contained by the world.
		/// </summary>
		void Update(WorldState & worldState);

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
		/// Returns the signatures of entity.
		/// </summary>
		/// <returns>The signatures of entity.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// World state of the world.
		/// </summary>
		WorldState mState;

	private:

		/// <summary>
		/// The name of the world.
		/// </summary>
		std::string mName;

		/// <summary>
		/// Whether the world is awake.
		/// </summary>
		int mIsAwake = 0;

		inline static const std::string nonSectorInSectorsText = "Only Sector objects can be added to the \"Sectors\" field.\n";
	};
}