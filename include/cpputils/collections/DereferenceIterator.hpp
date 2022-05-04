#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED

#include <cpputils/collections/types.hpp>
#include <cpputils/collections/Iterator.hpp>
#include <type_traits>

namespace cpputils::collections
{

	template<
		typename TIterator,
		typename TDereferenceResult = std::remove_pointer_t<std::remove_reference_t<types::DereferenceResult<TIterator>>>&
	>
		class DereferenceIterator : public collections::Iterator <TIterator, TDereferenceResult, types::dereferenceAndCast<types::DereferenceResult<TIterator>, TDereferenceResult>>
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