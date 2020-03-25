#pragma once
#include "IJsonParseHelper.h"

namespace FIEAGameEngine
{
	class IDepthTestParseHelper final :
		public IJsonParseHelper
	{
		RTTI_DECLARATIONS(IDepthTestParseHelper, FIEAGameEngine::IJsonParseHelper);
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
			/// The max depth
			/// </summary>
			size_t mMaxDepth = 0;

		private:
			
		};

		/// <summary>
		/// Default constructor
		/// </summary>
		IDepthTestParseHelper() = default;

		/// <summary>
		/// Virtual destructor
		/// </summary>
		virtual ~IDepthTestParseHelper() = default;

		/// <summary>
		/// Virtual constructor
		/// </summary>
		/// <returns>A pointer to the newly constructed object.</returns>
		gsl::owner<IJsonParseHelper*> Create() const override;

		virtual void Initialize() override;

		virtual bool StartHandler(JsonParseMaster::SharedData  * const sharedData, std::string const & key, Json::Value const & jsonValue, bool const & isArray, size_t const & index);

		virtual bool EndHandler(JsonParseMaster::SharedData * const sharedData, std::string const & key)  override;

	private:

		size_t mStartHandlerCount = 0;
		size_t mEndHandlerCount = 0;
		/// <summary>
		/// Temporary size_t value used to store max depth before it is committed to shared data
		/// </summary>
		size_t mHandlerMaxDepth = 0;
	};

}