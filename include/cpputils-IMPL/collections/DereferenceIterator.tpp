#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/DereferenceIterator.hpp>

#include <utility>

namespace cpputils::collections
{

	namespace types
	{

		template <typename TFrom, typename TTo>
		inline constexpr TTo dereferenceAndCast(TFrom _from)
		{
			return (TTo)(*_from);
		}

		template <typename TFrom, typename TTo>
		inline constexpr DereferenceResult<TTo> castAndDereference(TFrom _from)
		{
			return *(TTo)(_from);
		}

	}

	template <typename TIterator, typename TDereferenceResult>
	DereferenceIterator<TIterator, TDereferenceResult>::DereferenceIterator(const TIterator& _iterator)
		: collections::Iterator <TIterator, TDereferenceResult, types::dereferenceAndCast<types::DereferenceResult<const TIterator>, TDereferenceResult>>{ _iterator }
	{}

	template <typename TIterator, typename TDereferenceResult>
	DereferenceIterator<TIterator, TDereferenceResult>::DereferenceIterator(TIterator&& _iterator)
		: collections::Iterator <TIterator, TDereferenceResult, types::dereferenceAndCast<types::DereferenceResult<const TIterator>, TDereferenceResult>>{ std::move(_iterator) }
	{}

}
