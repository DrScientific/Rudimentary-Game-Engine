#include "pch.h"
#include "DefaultHashFunctor.h"


namespace FIEAGameEngine
{
	size_t AdditiveHash(uint8_t const* data, size_t size)
	{
		size_t hashValue = 0;
		for (size_t i = 0; i < size; i++)
		{
			hashValue += data[i] * size_t(33);
		}

		return hashValue;
	}
}