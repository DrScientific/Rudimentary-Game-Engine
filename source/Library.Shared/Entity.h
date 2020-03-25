#pragma once
#include "Attributed.h"
#include "Factory.h"

namespace FIEAGameEngine
{
	class Sector;
	class WorldState;

	/// <summary>
	/// The entity class is similar to the actor class in unreal. It is the parent class from which a majority of game objects will derive.
	/// </summary>
	class Entity :
		public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed);
	public:

		/// <summary>
		/// Default entity constructor
		/// </summary>
		/// <param name="sector">Parent of entity</param>
		Entity(Sector * const sector = nullptr);

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">Entity to copy</param>
		Entity(Entity const & other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">Entity to assign to</param>
		/// <returns>Reference this</returns>
		Entity & operator=(Entity const & rhs) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">Entity to move</param>
		Entity(Entity && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">Entity to assign to</param>
		/// <returns>Reference to this</returns>
		Entity & operator=(Entity && rhs) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~Entity();

		/// <summary>
		/// Returns the name of the entity
		/// </summary>
		/// <returns>The name of the entity</returns>
		std::string Name() const;

		/// <summary>
		/// Sets the name field of the entity
		/// </summary>
		/// /// <param name="name">The new name of the entity.</param>
		void SetName(std::string const & name);

		/// <summary>
		/// Get the sector containing this entity.
		/// </summary>
		/// <returns>The sector containing this entity.</returns>
		Sector const * GetSector() const;

		/// <summary>
		/// Moves the entity to a new sector
		/// </summary>
		/// <param name="newSector">The new sector to parent the entity to.</param>
		void SetSector(Sector * const newSector);
		
		/// <summary>
		/// Returns whether the entity is awake.
		/// </summary>
		/// <returns>Whether the entity is awake.</returns>
		bool IsAwake() const;

		/// <summary>
		/// Sets whether the entity is awake.
		/// </summary>
		void SetIsAwake(bool const & awake);

		/// <summary>
		/// Wakes the entity.
		/// </summary>
		void Wake();

		/// <summary>
		/// Puts the entity to sleep.
		/// </summary>
		void Sleep();

		/// <summary>
		/// Calls the update call of the actions contained by the entity
		/// </summary>
		void Update(WorldState & worldState);

		/// <summary>
		/// RTTI to string override. Returns "Entity".
		/// </summary>
		/// <returns>Returns "Entity".</returns>
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

	private:
		/// <summary>
		/// The name of the entity.
		/// </summary>
		std::string mName;

		/// <summary>
		/// Whether the entity is awake.
		/// </summary>
		int mIsAwake = 0;
	};

	CONCRETE_FACTORY(Entity, FIEAGameEngine::Scope);
}