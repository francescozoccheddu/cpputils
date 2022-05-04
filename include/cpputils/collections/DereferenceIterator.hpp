#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <type_traits>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterator, typename TDereferenceResult>
		inline constexpr TDereferenceResult dereferenceIteratorDereferenceCCast(const TIterator& _iterator);

	}

	template<
		typename TIterator,
		typename TDereferenceResult = std::remove_pointer_t<typename TIterator::value_type>&,
		typename TCategory = typename TIterator::iterator_category,
		typename TDifferenceType = typename TIterator::difference_type
	>
		class DereferenceIterator : public collections::Iterator <TIterator, TDereferenceResult, internal::dereferenceIteratorDereferenceCCast<TIterator, TDereferenceResult>, TCategory, TDifferenceType>
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