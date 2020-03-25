#pragma once

/// <summary>
/// 
/// </summary>

#include "Scope.h"
#include "gsl/gsl"

namespace FIEAGameEngine
{
	/// <summary>
	/// An attributed object contains a scope with external datums pointing to the attributed object's member variables.
	/// The member varaibles in question must be defined in a signatures function defined in the derieved class.
	/// See the attributed foo class for an example implementation.
	/// </summary>

	class Attributed : public Scope
	{
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

			/// <summary>
			/// Signature equivalence operator used by HashMap find in type manager when looking up signature-type table.
			/// </summary>
			/// <returns>Whether the signatures are equal.</returns>
			//bool operator==(Signature const & rhs) const { return mName == rhs.mName && mType == rhs.mType && mSize == rhs.mSize && mOffset == rhs.mOffset; };
			
			/// <summary>
			/// Signature equivalence operator used by HashMap find in type manager when looking up signature-type table.
			/// </summary>
			/// <returns>Whether the signatures are not equal.</returns>
			//bool operator!=(Signature const & rhs) const { return !(*this == rhs); };

		};

	protected:
		/// <summary>
		/// Attributed constructor
		/// </summary>
		/// <param name="id">Type id of the object we are constructing. Must be passed in as vtable is not correctly setup on construction.</param>
		Attributed(IdType id);

		/// <summary>
		/// Attributed move constructor
		/// </summary>
		/// <param name="other"></param>
		Attributed(Attributed && other);

		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <returns>Object we are setting this equal to.</returns>
		Attributed & operator=(Attributed const & other);

		/// <summary>
		/// Attributed copy constructor
		/// </summary>
		/// <param name="other">Object we wish to construct a copy from.</param>
		Attributed(Attributed const & other);

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <returns>Object we are setting this equal to.</returns>
		Attributed & operator=(Attributed && other);

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
		bool IsAttribute(string const & name) const;

		/// <summary>
		/// Returns whether a given key (string) is a prescribed attribute of the attributed object.
		/// </summary>
		/// <param name="name">Key to search scope for.</param>
		/// <returns>Whether the given key is in the prescibed attributes of the attributed object.</returns>
		bool IsPrescribedAttribute(string const & name) const;

		/// <summary>
		/// Returns whether a given key (string) is an auxiliary attribute of the attributed object.
		/// </summary>
		/// <param name="name">Key to search scope for.</param>
		/// <returns>Whether the given key is in the auxiliary attributes of the attributed object.</returns>
		bool IsAuxiliaryAttribute(string const & name) const;

		/// <summary>
		/// Append a default constructed datum to the attributed object at the given key (string).
		/// </summary>
		/// <param name="name">Key to place new datum at.</param>
		/// <returns>A reference to the newly constructed datum at the given key.</returns>
		Datum & AppendAuxiliaryAttribute(string const & name);


		/// <summary>
		/// Append a copy of a datum to the attributed object at the given key (string).
		/// </summary>
		/// <param name="name">Key to place new datum at.</param>
		/// <param name="value">The datum we wish to place a copy of at the given key.</param>
		/// <returns>A reference to the newly constructed datum at the given key.</returns>
		Datum & AppendAuxiliaryAttribute(string const & name, Datum const & value);

		/// <summary>
		/// Returns all attributes of the attributed object.
		/// </summary>
		/// <returns>A vector of pointers to each key datum pair in the attributes of the attributed object.</returns>
		Vector<PairType*> const & Attributes();

		/// <summary>
		/// Returns all prescribed attributes of the attributed object.
		/// </summary>
		/// <returns>A vector of pointers to each key datum pair in the prescribed attributes of the attributed object.</returns>
		Vector<PairType*> PrescribedAttributes();

		/// <summary>
		/// Returns all auxiliary attributes of the attributed object.
		/// </summary>
		/// <returns>A vector of pointers to each key datum pair in the auxiliary attributes of the attributed object.</returns>
		Vector<PairType*> AuxiliaryAttributes();

		/// <summary>
		/// Overload of Scope's virtual clear function. Clear's all auxiliary attributes from the attributed object.
		/// </summary>
		virtual void Clear() override;

		/// <summary>
		/// Overload of Scope's virtual constructor for Attibuted
		/// </summary>
		/// <returns>A scope pinter pointer to the newly created attributed object</returns>
		virtual gsl::owner<Scope*> Clone();

	private:

		/// <summary>
		/// 
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
