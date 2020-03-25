#pragma once
#include "Attributed.h"
#include "Factory.h"

namespace FIEAGameEngine
{

	class Entity;
	class World;
	class WorldState;

	/// <summary>
	/// The sector class is used to contain collections of entities.
	/// </summary>
	class Sector final :
		public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed);
	public:
		/// <summary>
		/// Default sector constructor.
		/// </summary>
		/// <param name="name">Name of sector.</param>
		Sector(std::string const & name = std::string());

		/// <summary>
		/// Default copy constructor.
		/// </summary>
		/// <param name="sector">Sector to copy.</param>
		Sector(Sector const & other) = default;

		/// <summary>
		/// Default assignment operator.
		/// </summary>
		/// <param name="other">Sector to assign to.</param>
		/// <returns>A reference to this.</returns>
		Sector & operator=(Sector const & rhs) = default;

		/// <summary>
		/// Default move constructor.
		/// </summary>
		/// <param name="sector">Sector to move.</param>
		Sector(Sector && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">Sector to move</param>
		/// <returns>A reference to this.</returns>
		Sector & operator=(Sector && rhs) = default;

		/// <summary>
		/// Destructor
		/// </summary>
		~Sector() = default;

		/// <summary>
		/// Adopts an existing scope placing it at the provided key. If the new key is the entities key, verifies that the child scope is an entity. Removes the scope from it's previous parent.
		/// </summary>
		/// <param name="child">Scope to adopt.</param>
		/// <param name="newChildKey">Key to place the newly adopted scope at.</param>
		virtual void Adopt(Scope & child, std::string const & newChildKey) override;

		/// <summary>
		/// Returns the name of the sector.
		/// </summary>
		/// <returns>The name of the sector.</returns>
		std::string Name() const;

		/// <summary>
		/// Sets the name of the sector.
		/// </summary>
		/// <param name="name">The new name of the sector.</param>
		void SetName(std::string const & name);

		/// <summary>
		/// Get the world containing this sector.
		/// </summary>
		/// <returns>The world containing this sector.</returns>
		World const * GetWorld() const;

		/// <summary>
		/// Moves the sector to a new world.
		/// </summary>
		/// <param name="world">The new world to parent the sector to.</param>
		void SetWorld(World * const world);

		/// <summary>
		/// Returns whether the sector is awake.
		/// </summary>
		/// <returns>Whether the sector is awake.</returns>
		bool IsAwake() const;

		/// <summary>
		/// 
		/// </summary>
		void SetIsAwake(bool const & awake);

		/// <summary>
		/// Sets whether the entity is awake.
		/// </summary>
		void Wake();

		/// <summary>
		/// Sets whether the entity is asleep.
		/// </summary>
		void Sleep();

		/// <summary>
		/// Returns a datum containing all entities contained by this sector.
		/// </summary>
		Datum & Entities();

		/// <summary>
		/// Returns a datum containing all entities contained by this sector.
		/// </summary>
		Datum const & Entities() const;

		/// <summary>
		/// Creates a new entity and inserts it into this sector's Entities attribute.
		/// </summary>
		/// <param name="className">Class name of the entity</param>
		/// <returns>A reference to the newly created entity.</returns>
		Entity & CreateEntity(std::string name, std::string className);

		/// <summary>
		/// Calls update on all awake entities in this sector.
		/// </summary>
		void Update(WorldState & worldState);

		/// <summary>
		/// RTTI to string override. Returns "Sector".
		/// </summary>
		/// <returns>Returns "Sector"</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Virtual constructor overriden from scope.
		/// </summary>
		/// <returns>A pointer to the newly constructed object</returns>
		virtual gsl::owner<Scope*> Clone() const override;

		/// <summary>
		/// Returns the signatures of sector.
		/// </summary>
		/// <returns>The signatures of sector.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();


		/// <summary>
		/// Name of sectors attribute in scope.
		/// </summary>
		inline static const std::string mEntitiesKey = "Entities";

		/// <summary>
		/// Index of sectors attribute in scope.
		/// </summary>
		inline static const int mEntitiesIndex = 3;

	private:

		/// <summary>
		/// The name of the sector.
		/// </summary>
		std::string mName;

		/// <summary>
		/// Whether the sector is awake.
		/// </summary>
		int mIsAwake = 0;

		inline static const std::string nonEntityInEntitiesText = "Only Entity objects can be added to the Entities field.\n";
	};

	CONCRETE_FACTORY(Sector, Scope);
}