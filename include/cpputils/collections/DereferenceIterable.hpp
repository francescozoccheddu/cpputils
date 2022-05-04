#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_INCLUDED

#include <cpputils/collections/types.hpp>
#include <cpputils/collections/Iterable.hpp>
#include <type_traits>

namespace cpputils::collections
{

	template<
		typename TIterable,
		typename TDereferenceResult = std::remove_pointer_t<std::remove_reference_t<types::DereferenceResult<types::Iterator<TIterable>>>>&,
		typename TDereferenceConstResult = std::remove_pointer_t<std::remove_reference_t<types::DereferenceResult<types::ConstIterator<TIterable>>>>&
	>
		class DereferenceIterable
		: public collections::Iterable
		<
		TIterable,
		TDereferenceResult,
		TDereferenceConstResult,
		types::dereferenceAndCast<types::DereferenceResult<types::Iterator<TIterable>>, TDereferenceResult>,
		types::dereferenceAndCast<types::DereferenceResult<types::ConstIterator<TIterable>>, TDereferenceConstResult>
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