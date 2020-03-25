#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "Vector.h"
#include "RTTI.h"
#include "gsl/gsl"

namespace FIEAGameEngine
{
	class IJsonParseHelper;


	/// <summary>
	/// A JsonParseMaster contains a vector of ParseHandlers which it uses to parse varying Json grammars.
	/// </summary>
	class JsonParseMaster final: public RTTI
	{
		
		RTTI_DECLARATIONS(JsonParseMaster, FIEAGameEngine::RTTI);
	public:
		/// <summary>
		/// Shared data is an abstract class from which different shared data types storing different shared datas may be derived.
		/// </summary>
		class SharedData : public RTTI
		{
			friend class JsonParseMaster;
			RTTI_DECLARATIONS(SharedData, FIEAGameEngine::RTTI);
		public:

			/// <summary>
			/// Virtual destructor for Shared Datas
			/// </summary>
			virtual ~SharedData();
	
			/// <summary>
			/// Virtual constructor for Shared Datas
			/// </summary>
			/// <returns>A pointer to the newly created object.</returns>
			virtual gsl::owner<SharedData*> Create() const = 0;

			/// <summary>
			/// Virtual initialize call to initialize derived shared data members.
			/// </summary>
			virtual void Initialize() {};

			/// <summary>
			/// Returns the parse master that owns this shared data.
			/// </summary>
			/// <returns>Returns the parse master that owns this shared data.</returns>
			JsonParseMaster* GetJsonParseMaster();

			/// <summary>
			/// Increments the current depth of the shared data.
			/// </summary>
			/// <returns>Returns the current depth of the shared data.</returns>
			size_t const IncrementDepth();

			/// <summary>
			/// Decrements the current depth of the shared data.
			/// </summary>
			/// <returns>Returns the current depth of the shared data.</returns>
			size_t const DecrementDepth();

			/// <summary>
			/// Returns the current depth of the shared data.
			/// </summary>
			/// <returns>Returns the current depth of the shared data.</returns>
			size_t const Depth();

		protected:

			/// <summary>
			/// Set's the parse master of the shared data object.
			/// </summary>
			/// <param name="master">The new parse master that will own the shared data.</param>
			void SetJsonParseMaster(JsonParseMaster * master);

			/// <summary>
			/// The parse master that owns the shared data
			/// </summary>
			JsonParseMaster* mMaster = nullptr;

			/// <summary>
			/// The current depth of the shared data
			/// </summary>
			size_t mDepth = 0;
		};

		
		/// <summary>
		/// Parse Master Constructor
		/// </summary>
		/// <param name="sharedData">A pointer to the parse master's shared data.</param>
		JsonParseMaster(SharedData * sharedData = nullptr);

		JsonParseMaster(JsonParseMaster const &) = delete;

		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">Parse master whose data is move into this parse master</param>
		JsonParseMaster(JsonParseMaster && other);
		
		/// <summary>
		/// Parse Master Destructor
		/// </summary>
		~JsonParseMaster();

		JsonParseMaster& operator=(JsonParseMaster const & other) = delete;

		/// <summary>
		/// Move assignment operator
		/// </summary>
		/// <param name="other">Parse master whose data is move into this parse master</param>
		/// <returns>A reference to this parse master.</returns>
		JsonParseMaster& operator=(JsonParseMaster && other);

		/// <summary>
		/// Calls the initialize function of all contained parse helpers.
		/// </summary>
		void Initialize();

		/// <summary>
		/// Clones a parse master creating a new set of shared data and parse helpers owned by the new parse master.
		/// </summary>
		/// <returns>A pointer to the new parse master.</returns>
		gsl::owner<JsonParseMaster*> Clone();

		/// <summary>
		/// Add a parse helper to the parse master
		/// </summary>
		/// <param name="helper">The parse helper to add to the parse master.</param>
		void AddHelper(IJsonParseHelper & helper);

		/// <summary>
		/// Remove a parse helper to the parse master
		/// </summary>
		/// <param name="helper">The parse helper to remove from the parse master</param>
		void RemoveHelper(IJsonParseHelper & helper);

		/// <summary>
		/// Attempt to parse a string.
		/// </summary>
		/// <param name="jsonString">The string to parse</param>
		/// <returns>Whether the parse was successful</returns>
		bool Parse(std::string jsonString);

		/// <summary>
		/// Attempt to parse a file.
		/// </summary>
		/// <param name="jsonFile">The path to the file we want to parse.</param>
		/// <returns>Whether the parse was successful</returns>
		bool ParseFromFile(std::string jsonFile);

		/// <summary>
		/// Attempt to parse an istream
		/// </summary>
		/// <param name="jsonIStream">The istream to parse</param>
		/// <returns>Whether the parse was successful</returns>
		bool Parse(std::istream & jsonIStream);

		/// <summary>
		/// Returns the name of the current file we are parsing.
		/// </summary>
		/// <returns>Returns the name of the current file we are parsing.</returns>
		std::string GetFileName();

		/// <summary>
		/// Returns a pointer to the shared data owned by this parse master.
		/// </summary>
		/// <returns>Returns a pointer to the shared data owned by this parse master.</returns>
		SharedData* GetSharedData();

		/// <summary>
		/// Sets a new shared data for this parse master.
		/// TODO Decide whether to make this work safely if the old shared data is owned by this parse handler by deleting the old shared data
		/// or to pass that responsibility off to the user so that they can move that data and use it after we set the new shared data.
		/// </summary>
		/// <param name="sharedData">The new shared data the parse master will point at.</param>
		void SetSharedData(SharedData* sharedData);

	private:

		/// <summary>
		/// Parses the members of a given Json::Value
		/// </summary>
		/// <param name="jsonValue">The Json::Value to parse.</param>
		/// <returns>Whether the members of the Json::Value were successfully parsed.</returns>
		bool ParseMembers(Json::Value jsonValue);

		/// <summary>
		/// Parses a string-key Json::Value-value pair.
		/// </summary>
		/// <param name="key">Key</param>
		/// <param name="value">Value</param>
		/// <param name="isInArray">Whether the key value pair is in an array.</param>
		/// <returns>Whether the key-value pair was successfully parsed.</returns>
		bool Parse(std::string key, Json::Value value, bool isInArray);

		/// <summary>
		/// Vector of parse handlers employed by the parse master.
		/// </summary>
		Vector<std::pair<bool, IJsonParseHelper*>> mParseHandlers;

		/// <summary>
		/// The name of the current file we are parsing.
		/// </summary>
		std::string mCurrentFileBeingParsed = "";

		/// <summary>
		/// Whether the parse master is responsible for the memory of the shared data it is pointing to.
		/// </summary>
		bool doesOwnSharedData = false;

		/// <summary>
		/// Whether the parse master owns the shared data it points to.
		/// </summary>
		SharedData * mSharedData = nullptr;

		/// <summary>
		/// Communicates the cause of a may not adopt ancestor exception to the user.
		/// </summary>
		inline static const std::string sharedDataUninitializedExceptionText = "Shared data is pointing to nullptr.\n";
	};
}