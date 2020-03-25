#pragma once
#include "Action.h"

namespace FIEAGameEngine
{
	/// <summary>
	/// 
	/// </summary>
	class CreateAction :
		public Action
	{
	public:
		CreateAction();
		virtual ~CreateAction();

	public:
		RTTI_DECLARATIONS(CreateAction, Attributed);
	public:
		/// <summary>
		/// Default action list constructor
		/// </summary>
		/// <param name="name">Name of the action list</param>
		CreateAction(std::string const & name = std::string());

		/// <summary>
		/// Default copy constructor
		/// </summary>
		/// <param name="other">ActionList to copy</param>
		CreateAction(ActionList const & other) = default;

		/// <summary>
		/// Default assignment operator
		/// </summary>
		/// <param name="other">ActionList to assign to</param>
		/// <returns>Reference this</returns>
		ActionList & operator=(ActionList const & rhs) = default;

		/// <summary>
		/// Default move constructor 
		/// </summary>
		/// <param name="other">ActionList to move</param>
		ActionList(ActionList && other) = default;

		/// <summary>
		/// Default move assignment operator
		/// </summary>
		/// <param name="other">ActionList to assign to</param>
		/// <returns>Reference to this</returns>
		ActionList & operator=(ActionList && rhs) = default;

		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~ActionList() = default;

		/// <summary>
		/// Adopts an existing scope placing it at the provided key. If the new key is the actions key, verifies that the child scope is an action. Removes the scope from it's previous parent.
		/// </summary>
		/// <param name="child">Scope to adopt.</param>
		/// <param name="newChildKey">Key to place the newly adopted scope at.</param>
		virtual void Adopt(Scope & child, std::string const & newChildKey) override;

		/// <summary>
		/// Returns a datum containing all actions contained by this action list.
		/// </summary>
		Datum & Actions();

		/// <summary>
		/// Returns a datum containing all actions contained by this action list.
		/// </summary>
		Datum const & Actions() const;

		/// <summary>
		/// Creates a new action and inserts it into this action list's Actions attribute.
		/// </summary>
		/// <param name="className">Class name of the action</param>
		/// <returns>A reference to the newly created action.</returns>
		Action & CreateAction(std::string name, std::string className);

		/// <summary>
		/// Virtual update call that iterates through all actions in the action list.
		/// </summary>
		virtual void Update(WorldState & worldState) override;

		/// <summary>
		/// RTTI to string override. Returns "ActionList".
		/// </summary>
		/// <returns>Returns "ActionList".</returns>
		virtual std::string ToString() const override;

		/// <summary>
		/// Returns the signatures of action list.
		/// </summary>
		/// <returns>The signatures of action list.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of sectors attribute in scope.
		/// </summary>
		inline static const std::string mActionsKey = "Actions";


	protected:

		/// <summary>
		/// Action List IdType Constructor
		/// </summary>
		/// <param name="typeId">RTTI type ID of the function</param>
		ActionList(ActionList::IdType typeId);

		/// <summary>
		/// Action List Constructor. All other constructors forwarded to this constructor.
		/// </summary>
		/// <param name="typeId">RTTI type ID of the function</param>
		/// <param name="name">Name of the Action List</param>
		ActionList(ActionList::IdType typeId, string const & name);

		/// <summary>
		/// Index of sectors attribute in scope.
		/// </summary>
		inline static const int mActionsIndex = 2;

		inline static const std::string nonActionInActionsText = "Only Action objects can be added to the Actions field.\n";
	};

	CONCRETE_FACTORY(ActionList, Scope);
	};

}