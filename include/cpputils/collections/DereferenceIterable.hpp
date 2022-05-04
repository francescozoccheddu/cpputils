#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_INCLUDED

#include <cpputils/collections/DereferenceIterator.hpp>
#include <cpputils/collections/Iterable.hpp>
#include <type_traits>

namespace cpputils::collections
{

	template<
		typename TIterable,
		typename TDereferenceResult = std::remove_pointer_t<typename internal::IterableIterator<TIterable>::value_type>,
		typename TDereferenceConstResult = std::remove_pointer_t<typename internal::IterableConstIterator<TIterable>::value_type>,
		typename TCategory = typename internal::IterableIterator<TIterable>::iterator_category,
		typename TDifferenceType = typename internal::IterableIterator<TIterable>::difference_type,
		typename TConstCategory = typename internal::IterableConstIterator<TIterable>::iterator_category,
		typename TConstDifferenceType = typename internal::IterableConstIterator<TIterable>::difference_type
	>
		class DereferenceIterable
		: public collections::Iterable
		<
		TIterable,
		TDereferenceResult,
		internal::dereferenceIteratorDereferenceCCast<typename internal::IterableIterator<TIterable>, TDereferenceResult>,
		TDereferenceConstResult,
		internal::dereferenceIteratorDereferenceCCast<typename internal::IterableConstIterator<TIterable>, TDereferenceConstResult>,
		TCategory,
		TDifferenceType
		>
	{

	public:

		DereferenceIterable(TIterable& _iterator);

	};

}

#define CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_IMPLEMENTATION
#include <cpputils-IMPL/collections/DereferenceIterable.tpp>
#undef CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_IMPLEMENTATION

#endif