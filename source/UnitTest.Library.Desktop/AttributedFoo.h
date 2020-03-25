#pragma once
#include "Attributed.h"
namespace UnitTests
{
	/// <summary>
	/// Class for testing all types of members that may be contained within an attributed class.
	/// </summary>
	class AttributedFoo final : public Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, FIEAGameEngine::RTTI);
		static const std::size_t ArraySize = 5;

	public:
		AttributedFoo();
		AttributedFoo(const AttributedFoo&) = default;
		AttributedFoo(AttributedFoo&&) = default;
		AttributedFoo& operator=(const AttributedFoo&) = default;
		AttributedFoo& operator=(AttributedFoo&&) = default;
		~AttributedFoo() = default;

		int ExternalInteger = 0;
		float ExternalFloat = 0;
		std::string ExternalString = "";
		glm::mat4x4 ExternalMatrix;
		glm::vec4 ExternalVector;

		int ExternalIntegerArray[ArraySize];
		float ExternalFloatArray[ArraySize];
		std::string ExternalStringArray[ArraySize];
		glm::mat4x4 ExternalMatrixArray[ArraySize];
		glm::vec4 ExternalVectorArray[ArraySize];
		virtual std::string ToString() const override;

		static const FIEAGameEngine::Vector<Signature> Signatures();

	};
}
