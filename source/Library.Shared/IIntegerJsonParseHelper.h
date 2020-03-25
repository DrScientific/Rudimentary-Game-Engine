#pragma once
#include "IJsonParseHelper.h"

namespace FIEAGameEngine
{
	class IIntegerJsonParseHelper final :
		public IJsonParseHelper
	{
		RTTI_DECLARATIONS(IIntegerJsonParseHelper, FIEAGameEngine::IJsonParseHelper);
	public:

		class SharedData : public JsonParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedData, FIEAGameEngine::JsonParseMaster::SharedData);
		public:
			/// <summary>
			/// Default constructor
			/// </summary>
			SharedData() = default;

			/// <summary>
			/// Virtual destructor
			/// </summary>
			virtual ~SharedData() = default;

			/// <summary>
			/// Virtual constructor
			/// </summary>
			/// <returns>A pointer to the newly constructed object.</returns>
			virtual gsl::owner<JsonParseMaster::SharedData*> Create() const override;

			/// <summary>
			/// Initialize the shared data.
			/// </summary>
			virtual void Initialize() override;

			/// <summary>
			/// The parsed integer from the json.
			/// </summary>
			int parsedInt = 0;
		};

		/// <summary>
		/// Default constructor
		/// </summary>
		IIntegerJsonParseHelper() = default;

		/// <summary>
		/// Virtual destructor
		/// </summary>
		virtual ~IIntegerJsonParseHelper() = default;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns>A pointer to the newly constructed object.</returns>
		gsl::owner<IJsonParseHelper*> Create() const override;

		void Initialize();

		bool StartHandler(JsonParseMaster::SharedData const * const sharedData, std::string const & key, Json::Value jsonValue, bool isArray) override;

		bool EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key) override;

	private:

		/// <summary>
		/// Temporary integer value used to store parsed int before it is commited to shared data.
		/// </summary>
		int tempInt = 0;
		
	};
}