#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/DereferenceIterable.hpp>

namespace cpputils::collections
{

	template<
		typename TIterable,
		typename TDereferenceResult,
		typename TDereferenceConstResult
	>
		DereferenceIterable<TIterable, TDereferenceResult, TDereferenceConstResult>::DereferenceIterable(TIterable& _iterable)
		: collections::Iterable
		<
		TIterable,
		TDereferenceResult,
		TDereferenceConstResult,
		types::dereferenceAndCast<types::DereferenceResult<types::Iterator<TIterable>>, TDereferenceResult>,
		types::dereferenceAndCast<types::DereferenceResult<types::ConstIterator<TIterable>>, TDereferenceConstResult>
		>
	{ _iterable }
	{}

}
