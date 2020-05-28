#pragma once
#include "Reaction.h"
#include "Factory.h"
#include "Attributed.h"

namespace FIEAGameEngine
{
	class ReactionAttributed :
		public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);
	public:
		
		/// <summary>
		/// Default Constructor
		/// </summary>
		/// <param name="name">The name of the reaction attributed.</param>
		/// <param name="subtype">The subtype of the reaction attributed.</param>
		ReactionAttributed(std::string name = std::string(), std::string subtype = std::string());

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		ReactionAttributed(ReactionAttributed const& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		ReactionAttributed & operator=(ReactionAttributed const& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		ReactionAttributed(ReactionAttributed && other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		ReactionAttributed & operator=(ReactionAttributed && other);

		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~ReactionAttributed();

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns></returns>
		virtual gsl::owner<ReactionAttributed*> Clone() const override;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="publisher"></param>
		virtual void Notify(class FIEAGameEngine::EventPublisher const& publisher) override;

		/// <summary>
		/// Returns the signatures of reaction attributed.
		/// </summary>
		/// <returns>The signatures of reaction attributed.</returns>
		static const FIEAGameEngine::Vector<Signature> Signatures();

		/// <summary>
		/// Name of subtype attribute in reaction attributed.
		/// </summary>
		inline static const std::string mSubtypeKey = "Subtype";


	private:

		/// <summary>
		/// The subtype of the reaction attributed.
		/// </summary>
		std::string mSubtype;

		/// <summary>
		/// The world of the reaction attributed.
		/// </summary>
		class World* mWorld = nullptr;
	};

	CONCRETE_FACTORY(ReactionAttributed, Scope)
}