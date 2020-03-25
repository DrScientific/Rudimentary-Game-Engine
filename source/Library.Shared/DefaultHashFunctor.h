#pragma once

#include <string>

namespace FIEAGameEngine
{
	/// <summary>
	/// 
	/// </summary>
	template <typename T>
	struct DefaultHashFunctor
	{
		size_t operator() (T const & key) const
		{
			unsigned char const * byteArray = reinterpret_cast<unsigned char const *>(&key);
			size_t hashValue = 0;
			for (size_t i = 0; i != sizeof(key); i++)
			{
				hashValue += byteArray[i] * (i + 1);
			}
			return hashValue;
		}
	};
	template<>
	struct DefaultHashFunctor<std::string>
	{
		size_t operator() (std::string const & key) const
		{
			size_t hashValue = 0;
			for (size_t i = 0; i != key.size(); i++)
			{
				hashValue = key[i] * (i + 1);
			}
			return hashValue;
		}
	};
	template<>
	struct DefaultHashFunctor<char*>
	{
		size_t operator() (char* const & key) const
		{
			size_t hashValue = 0;
			for (size_t i = 0; key[i] != '\0'; i++)
			{
				hashValue = key[i] * (i + 1);
			}
			return hashValue;
		}
	};
}