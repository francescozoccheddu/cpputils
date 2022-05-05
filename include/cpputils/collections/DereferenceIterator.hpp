#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <iterator>
#include <type_traits>

namespace cpputils::collections
{

	namespace types
	{

		template <typename TFrom, typename TTo>
		inline constexpr TTo dereferenceAndCast(TFrom _from);

	}

	template <
		typename TIterator,
		typename TDereferenceResult = std::remove_pointer_t<std::remove_reference_t<types::DereferenceResult<const TIterator>>>&
	>
		class DereferenceIterator : public collections::Iterator <TIterator, TDereferenceResult, types::dereferenceAndCast<types::DereferenceResult<const TIterator>, TDereferenceResult>>
	{

	public:

		DereferenceIterator(const TIterator& _iterator);
		DereferenceIterator(TIterator&& _iterator);

	};

}

#define CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_IMPLEMENTATION
#include <cpputils-IMPL/collections/DereferenceIterator.tpp>
#undef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_IMPLEMENTATION

#endif