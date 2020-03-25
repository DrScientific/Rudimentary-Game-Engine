#pragma once

#include <string>

namespace FIEAGameEngine
{
	size_t AdditiveHash(uint8_t const* data, size_t size);

	template <typename T>
	struct DefaultHashFunctor
	{
		size_t operator() (T const & key) const
		{
			uint8_t const * byteArray = reinterpret_cast<uint8_t const *>(&key);
			return AdditiveHash(byteArray, sizeof(T));
		}
	};

	template<>
	struct DefaultHashFunctor<std::string>
	{
		size_t operator() (std::string const & key) const
		{
			uint8_t const * byteArray = reinterpret_cast<uint8_t const *>(key.c_str());
			return AdditiveHash(byteArray,key.size());
		}
	};

	template<>
	struct DefaultHashFunctor<const std::string>
	{
		size_t operator() (std::string const & key) const
		{
			uint8_t const * byteArray = reinterpret_cast<uint8_t const *>(key.c_str());
			return AdditiveHash(byteArray,key.size());
		}
	};

	template<>
	struct DefaultHashFunctor<char*>
	{
		size_t operator() (char* const & key) const
		{
			uint8_t const * byteArray = reinterpret_cast<uint8_t const *>(key);
			return AdditiveHash(byteArray, strlen(key));
		}
	};

	template<>
	struct DefaultHashFunctor<const char*>
	{
		size_t operator() (char* const & key) const
		{
			uint8_t const * byteArray = reinterpret_cast<uint8_t const *>(key);
			return AdditiveHash(byteArray, strlen(key));
		}
	};
}