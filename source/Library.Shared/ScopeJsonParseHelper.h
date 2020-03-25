#pragma once
#include "IJsonParseHelper.h"
#include <memory>
#include "Stack.h"
#include "Datum.h"
#include "HashMap.h"

namespace FIEAGameEngine
{
	class Scope;

	/// <summary>
	/// Parse helper used to populate scopes from json files.
	/// </summary>
	class ScopeJsonParseHelper final:
		public IJsonParseHelper
	{

	private:
		RTTI_DECLARATIONS(ScopeJsonParseHelper, FIEAGameEngine::IJsonParseHelper);

		/// <summary>
		/// A stack frame consisting of the key of the current datum, it's type, and the scope we are appending the current datum to.
		/// </summary>
		struct StackFrame
		{
			/// <summary>
			/// Constructs a new stack frame
			/// </summary>
			/// <param name="key">Key of the current datum</param>
			/// <param name="type">Datum type of the datum that corresponds to the key</param>
			/// <param name="contextFrame">Scope context we are currently in.</param>
			StackFrame(std::string const key, Datum::DatumType type, Scope* contextFrame);

			/// <summary>
			/// Constructs a new stack frame
			/// </summary>
			/// <param name="key">Key of the current datum</param>
			/// <param name="type">Datum type of the datum that corresponds to the key</param>
			/// <param name="contextFrame">Scope context we are currently in.</param>
			StackFrame(std::string const key, Datum::DatumType type, std::string scopeClass, Scope* contextFrame);

			/// <summary>
			/// Key of the current datum
			/// </summary>
			string const Key;
			
			/// <summary>
			/// Datum type of the datum that corresponds to the key
			/// </summary>
			Datum::DatumType Type;
			
			/// <summary>
			/// 
			/// </summary>
			std::string Class;

			/// <summary>
			/// Scope context we are currently in.
			/// </summary>
			Scope* ContextFrame;
		};

	public:

		/// <summary>
		/// Scope shared data used for populating scopes from json files.
		/// </summary>
		class ScopeSharedData : public JsonParseMaster::SharedData
		{
			friend class ScopeJsonParseHelper;
			RTTI_DECLARATIONS(ScopeSharedData, JsonParseMaster::SharedData);
		public:
			/// <summary>
			/// Shared Pointer constructor
			/// </summary>
			ScopeSharedData(shared_ptr<Scope> & scope);

			/// <summary>
			/// Shared Pointer move constructor
			/// </summary>
			ScopeSharedData(shared_ptr<Scope> && scope);

			/// <summary>
			/// Virtual destructor
			/// </summary>
			virtual ~ScopeSharedData() = default;

			/// <summary>
			/// Virtual constructor
			/// </summary>
			/// <returns>A pointer to the newly constructed object.</returns>
			virtual gsl::owner<JsonParseMaster::SharedData*> Create() const override;

			/// <summary>
			/// Returns a reference to the scope pointed to by the shared pointer.
			/// </summary>
			/// <returns></returns>
			Scope & GetScope();

			/// <summary>
			/// Returns a reference to the scope pointed to by the shared pointer.
			/// </summary>
			/// <returns></returns>
			Scope const & GetScope() const;

		private:

			/// <summary>
			/// Shared pointer pointing to the root scope we will be populating.
			/// </summary>
			shared_ptr<Scope> rootScope;
		};


		ScopeJsonParseHelper() = default;

		virtual ~ScopeJsonParseHelper() = default;

		/// <summary>
		/// Returns true if it appears the ScopeJsonParseHelper can parse a particular key value pair.
		/// </summary>
		/// <param name="sharedData">The parse master's shared data. It is const because we do not want to alter it until we are sure the parse has succeeded.</param>
		/// <param name="key">The Json key</param>
		/// <param name="jsonValue">The Json value</param>
		/// <param name="isArray">Whether the key value pair is in an array</param>
		/// <returns>Whether the key value pair was successfully parsed.</returns>
		virtual bool StartHandler(JsonParseMaster::SharedData  * const sharedData, std::string const & key, Json::Value const & jsonValue, bool const & isArray, size_t const & index) override;

		/// <summary>
		/// Returns true if the ScopeJsonParseHelper correctly parsed a particular key value pair.
		/// </summary>
		/// <param name="sharedData">The parse master's shared data. If the parse was successful we will alter this data.</param>
		/// <param name="key">The Json key</param>
		/// <returns>Whether the key value pair was successfully parsed.</returns>
		virtual bool EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key) override;

		/// <summary>
		/// ScopeJsonParseHelper's Virtual Constructor
		/// </summary>
		/// <returns>A pointer to the newly created parse helper.</returns>
		virtual gsl::owner<IJsonParseHelper*> Create() const override;


	private:

		/// <summary>
		/// Stack of stack frames used to keep track of where we are in the json file while parsing it.
		/// </summary>
		Stack<StackFrame> stack;

		/// <summary>
		/// Static constant hashmap used to convert strings to datum types.
		/// </summary>
		static HashMap<std::string const, Datum::DatumType> const stringToTypeMap;

		/// <summary>
		/// 
		/// </summary>
		inline static const std::string classMustBeTypeScopeText = "An attribute with a class field must be of type scope.\n";
	};
}