#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/DereferenceIterator.hpp>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterator, typename TDereferenceResult>
		inline constexpr TDereferenceResult dereferenceIteratorDereferenceCCast(const TIterator& _iterator)
		{
			return (TDereferenceResult)(**_iterator);
		}

	}

	template<typename TIterator, typename TDereferenceResult, typename TCategory, typename TDifferenceType>
	DereferenceIterator<TIterator, TDereferenceResult, TCategory, TDifferenceType>::DereferenceIterator(const TIterator& _iterator)
		: collections::Iterator <TIterator, TDereferenceResult, internal::dereferenceIteratorDereferenceCCast<TIterator, TDereferenceResult>, TCategory, TDifferenceType>{ _iterator }
	{}

	template<typename TIterator, typename TDereferenceResult, typename TCategory, typename TDifferenceType>
	DereferenceIterator<TIterator, TDereferenceResult, TCategory, TDifferenceType>::DereferenceIterator(TIterator&& _iterator)
		: collections::Iterator <TIterator, TDereferenceResult, internal::dereferenceIteratorDereferenceCCast<TIterator, TDereferenceResult>, TCategory, TDifferenceType>{ std::move(_iterator) }
	{}

}
