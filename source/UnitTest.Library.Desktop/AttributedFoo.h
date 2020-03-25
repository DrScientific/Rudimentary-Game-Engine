#pragma once
#include "Attributed.h"
#include "RTTI.h"

namespace UnitTests
{
	/// <summary>
	/// Class for testing all types of members that may be contained within an attributed class.
	/// </summary>
	class AttributedFoo final : public FIEAGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, FIEAGameEngine::Attributed);
		static const std::size_t ArraySize = 5;

	public:
		AttributedFoo();
		AttributedFoo(const AttributedFoo&) = default;
		AttributedFoo(AttributedFoo&&) noexcept = default ;
		AttributedFoo& operator=(const AttributedFoo&) = default;
		AttributedFoo& operator=(AttributedFoo&&) noexcept = default;
		virtual ~AttributedFoo() = default;

		int ExternalInteger = 0;
		float ExternalFloat = 0;
		std::string ExternalString;
		glm::vec4 ExternalVector;
		glm::mat4x4 ExternalMatrix;

		int ExternalIntegerArray[ArraySize];
		float ExternalFloatArray[ArraySize];
		std::string ExternalStringArray[ArraySize];
		glm::vec4 ExternalVectorArray[ArraySize];
		glm::mat4x4 ExternalMatrixArray[ArraySize];

		virtual std::string ToString() const override;
		virtual gsl::owner<Scope*> Clone() const override;

		static const FIEAGameEngine::Vector<Signature> Signatures();

	};
}
