#pragma once

/// <summary>
/// 
/// </summary>

#include "Scope.h"
#include "gsl/gsl"
#include "RTTI.h"

namespace FIEAGameEngine
{
	/// <summary>
	/// An attributed object contains a scope with external datums pointing to the attributed object's member variables.
	/// The member varaibles in question must be defined in a signatures function defined in the derieved class.
	/// Any datums pointing to an object's member variables (the datum is using external storage) are refered to as "prescribed attributes."
	/// Any datums pointing to additional variables placed within the object's scope through our scripting language (the datum is using interenal storage) are refered to as "auxilliary attributes." 
	/// See the attributed foo class for an example implementation.
	/// </summary>

	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		/// <summary>
		/// Signature struct used for storing name, type, num elements, and offset of attributed derived classes
		/// </summary>
		struct Signature
		{

			Signature(std::string name, Datum::DatumType type, size_t size, size_t offset);

			std::string mName = "";
			Datum::DatumType mType = Datum::DatumType::Unknown;
			size_t mSize = 0;
			size_t mOffset = 0;
		};

	protected:
		/// <summary>
		/// Attributed constructor
		/// </summary>
		/// <param name="id">Type id of the object we are constructing. Must be passed in as vtable is not correctly setup on construction so we do not have the scope's data members.</param>
		Attributed(IdType id);

		/// <summary>
		/// Attributed copy constructor
		/// </summary>
		/// <param name="other">Object we wish to construct a copy from.</param>
		Attributed(Attributed const& other);

		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <returns>Object we are setting this equal to.</returns>
		Attributed & operator=(Attributed const& other);

		/// <summary>
		/// Attributed move constructor
		/// </summary>
		/// <param name="other"></param>
		Attributed(Attributed && other) noexcept;

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <returns>Object we are setting this equal to.</returns>
		Attributed & operator=(Attributed && other) noexcept;

	public:
		
		/// <summary>
		/// Virtual destructor of Attributed class.
		/// </summary>
		virtual ~Attributed() = default;

		/// <summary>
		/// Returns whether a given key (string) is present in the attributed object.
		/// </summary>
		/// <param name="name">Key to search scope for.</param>
		/// <returns>Whether the given key is in the attributed object.</returns>
		bool IsAttribute(std::string const& name) const;

		/// <summary>
		/// Returns whether a given key (string) is a prescribed attribute of the attributed object.
		/// </summary>
		/// <param name="name">Key to search scope for.</param>
		/// <returns>Whether the given key is in the prescibed attributes of the attributed object.</returns>
		bool IsPrescribedAttribute(std::string const& name) const;

		/// <summary>
		/// Returns whether a given key (string) is an auxiliary attribute of the attributed object.
		/// </summary>
		/// <param name="name">Key to search scope for.</param>
		/// <returns>Whether the given key is in the auxiliary attributes of the attributed object.</returns>
		bool IsAuxiliaryAttribute(std::string const& name) const;

		/// <summary>
		/// Append a default constructed datum to the attributed object at the given key (string).
		/// </summary>
		/// <param name="name">Key to place new datum at.</param>
		/// <returns>A reference to the newly constructed datum at the given key.</returns>
		Datum & AppendAuxiliaryAttribute(std::string const& name);


		/// <summary>
		/// Append a copy of a datum to the attributed object at the given key (string).
		/// </summary>
		/// <param name="name">Key to place new datum at.</param>
		/// <param name="value">The datum we wish to place a copy of at the given key.</param>
		/// <returns>A reference to the newly constructed datum at the given key.</returns>
		Datum & AppendAuxiliaryAttribute(std::string const& name, Datum const& value);

		/// <summary>
		/// Returns all attributes of the attributed object.
		/// </summary>
		/// <returns>A vector of pointers to each key datum pair in the attributes of the attributed object.</returns>
		Vector<PairType*> const& Attributes();

		/// <summary>
		/// Returns all prescribed attributes of the attributed object.
		/// </summary>
		/// <returns>A vector of pointers to each key datum pair in the prescribed attributes of the attributed object.</returns>
		Vector<PairType*> PrescribedAttributes() const;

		/// <summary>
		/// Returns all auxiliary attributes of the attributed object.
		/// </summary>
		/// <returns>A vector of pointers to each key datum pair in the auxiliary attributes of the attributed object.</returns>
		Vector<PairType*> AuxiliaryAttributes() const;

		/// <summary>
		/// Overload of Scope's virtual clear function. Clear's all auxiliary attributes from the attributed object.
		/// Does not clear prescribed attributes since we do not own that memory.
		/// </summary>
		virtual void Clear() override;

		/// <summary>
		/// Overload of Scope's virtual constructor for Attibuted
		/// </summary>
		/// <returns>A scope pinter pointer to the newly created attributed object</returns>
		virtual gsl::owner<Scope*> Clone() const override;
		
		virtual std::string ToString() const override;

	private:

		/// <summary>
		/// TODO: Rembmer and document how this works/what it does.
		/// </summary>
		/// <param name="id"></param>
		void Populate(IdType id);

		/// <summary>
		/// Resets all external pointers to point to this object's member variables.
		/// </summary>
		/// <param name="id">Type id of the object</param>
		void UpdateExternalStorage(IdType id);

		/// <summary>
		/// Communicates the cause of an cannot append auxiliary attribute under prescribed name exception to the user.
		/// </summary>
		inline static const std::string cannotAppendAuxiliaryAttributeUnderPrescribedNameExceptionText = "Cannot append auxiliary attribute under prescribed name.\n";
	};
}
