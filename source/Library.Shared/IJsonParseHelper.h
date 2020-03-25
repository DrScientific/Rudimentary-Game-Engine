#pragma once

#include <string>
#include "json/json.h"
#include "JsonParseMaster.h"
#include "RTTI.h"
#include "gsl/gsl"

namespace FIEAGameEngine
{
	/// <summary>
	/// Abstract IJsonParseHelper from which all parse handler are derived. PArse handlers are used to parse particular grammars.
	/// </summary>
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, FIEAGameEngine::RTTI);
	public:

		/// <summary>
		/// Virtual destructor
		/// </summary>
		virtual ~IJsonParseHelper() = default;

		/// <summary>
		/// Virtual initialize method to be overriden in derived classes.
		/// </summary>
		virtual void Initialize() {};

		/// <summary>
		/// Pure virtual function that starts a handler by determining if a key value pair appears parseable.
		/// </summary>
		/// <param name="sharedData">The parse master's shared data. It is const because we do not want to alter it until we are sure the parse has succeeded.</param>
		/// <param name="key">The Json key</param>
		/// <param name="jsonValue">The Json value</param>
		/// <param name="isArray">Whether the key value pair is in an array</param>
		/// <returns>Whether the key value pair was successfully parsed.</returns>
		virtual bool StartHandler(JsonParseMaster::SharedData const * const sharedData, std::string const & key, Json::Value jsonValue, bool isArray) = 0;

		/// <summary>
		/// Pure virtual function that ends a handler by determining if we successfully parse the data.
		/// </summary>
		/// <param name="sharedData">The parse master's shared data. If the parse was successful we will alter this data.</param>
		/// <param name="key">The Json key</param>
		/// <returns>Whether the key value pair was successfully parsed.</returns>
		virtual bool EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key) = 0;

		/// <summary>
		/// Parse Helper's Virtual Constructor
		/// </summary>
		/// <returns>A pointer to the newly created parse helper.</returns>
		virtual gsl::owner<IJsonParseHelper*> Create() const = 0;
	};
}