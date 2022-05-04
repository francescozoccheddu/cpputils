#ifndef CPPUTILS_COLLECTIONS_TYPES_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/types.hpp>

namespace cpputils::collections::types
{

	template<typename TFrom, typename TTo>
	inline constexpr TTo cast(TFrom _from)
	{
		return (TTo)(_from);
	}

	template<typename TFrom, typename TTo>
	inline constexpr TTo dereferenceAndCast(TFrom _from)
	{
		return (TTo)(*_from);
	}

	template<typename TFrom, typename TTo>
	inline constexpr DereferenceResult<TTo> castAndDereference(TFrom _from)
	{
		return *(TTo)(_from);
	}

}
