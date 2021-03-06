#pragma once

#include <string>
#include <cstdint>

namespace FIEAGameEngine
{
	class RTTI
	{
	public:
		using IdType = std::uint64_t;

		virtual ~RTTI() = default;

		static IdType TypeIdClass() { return 0; };

		virtual std::uint64_t TypeIdInstance() const = 0;

		virtual RTTI* QueryInterface(const IdType)
		{
			return nullptr;
		}

		virtual bool Is(IdType) const
		{
			return false;
		}

		virtual bool Is(const std::string&) const
		{
			return false;
		}

		template <typename T>
		T* As() const
		{
			return (Is(T::TypeIdClass()) ? reinterpret_cast<T*>(const_cast<RTTI*>(this)) : nullptr);
		}

		virtual std::string ToString() const
		{
			return "RTTI";
		}

		virtual bool Equals(const RTTI* other) const
		{
			return this == other;
		}
	};

#define RTTI_DECLARATIONS(Type, ParentType)																				\
		public:																											\
			static std::string TypeName() { return std::string(#Type); }												\
			static IdType TypeIdClass() { return sRunTimeTypeId; }														\
			static IdType ParentTypeIdClass() { return ParentType::TypeIdClass(); }										\
			virtual IdType TypeIdInstance() const override { return Type::TypeIdClass(); }								\
			virtual FIEAGameEngine::RTTI* QueryInterface(const IdType id) override										\
            {																											\
				return (id == sRunTimeTypeId ? reinterpret_cast<FIEAGameEngine::RTTI*>(this) : ParentType::QueryInterface(id)); \
            }																											\
			virtual bool Is(IdType id) const override																	\
			{																											\
				return (id == sRunTimeTypeId ? true : ParentType::Is(id));												\
			}																											\
			virtual bool Is(const std::string& name) const override														\
			{																											\
				return (name == TypeName() ? true : ParentType::Is(name));												\
			}																											\
			private:																									\
				static IdType sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type) RTTI::IdType Type::sRunTimeTypeId = reinterpret_cast<RTTI::IdType>(&Type::sRunTimeTypeId);
}