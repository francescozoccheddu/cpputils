#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/DereferenceIterator.hpp>

#include <utility>

namespace cpputils::collections
{

	template<typename TIterator, typename TDereferenceResult>
	DereferenceIterator<TIterator, TDereferenceResult>::DereferenceIterator(const TIterator& _iterator)
		: collections::Iterator <TIterator, TDereferenceResult, types::dereferenceAndCast<types::DereferenceResult<TIterator>, TDereferenceResult>>{ _iterator }
	{}

	template<typename TIterator, typename TDereferenceResult>
	DereferenceIterator<TIterator, TDereferenceResult>::DereferenceIterator(TIterator&& _iterator)
		: collections::Iterator <TIterator, TDereferenceResult, types::dereferenceAndCast<types::DereferenceResult<TIterator>, TDereferenceResult>>{ std::move(_iterator) }
	{}

}
