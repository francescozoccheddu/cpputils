#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/DereferenceIterable.hpp>

namespace cpputils::collections
{

	template<
		typename TIterable,
		typename TDereferenceResult,
		typename TDereferenceConstResult,
		typename TCategory,
		typename TDifferenceType,
		typename TConstCategory,
		typename TConstDifferenceType
	>
		DereferenceIterable<TIterable, TDereferenceResult, TDereferenceConstResult, TCategory, TDifferenceType, TConstCategory, TConstDifferenceType>::DereferenceIterable(TIterable& _iterable)
		: collections::Iterable
		<TIterable,
		TDereferenceResult,
		internal::dereferenceIteratorDereferenceCCast<typename internal::IterableIterator<TIterable>, TDereferenceResult>,
		TDereferenceConstResult,
		internal::dereferenceIteratorDereferenceCCast<typename internal::IterableConstIterator<TIterable>, TDereferenceConstResult>,
		TCategory,
		TDifferenceType
		>{ _iterable }
	{}

}
