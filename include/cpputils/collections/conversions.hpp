#ifndef CPPUTILS_COLLECTIONS_CONVERSIONS_INCLUDED
#define CPPUTILS_COLLECTIONS_CONVERSIONS_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <type_traits>
#include <cstddef>
#include <array>
#include <vector>

namespace cpputils::collections::conversions
{

	template <
		std::size_t TSize,
		typename TFromIterable,
		typename TOutputType = typename std::iter_value_t<types::BeginResult<TFromIterable>>,
		TOutputType(*TConverter)(types::DereferenceResult<types::BeginResult<TFromIterable>>) = types::cast<types::DereferenceResult<types::BeginResult<TFromIterable>>, TOutputType>,
		bool TThrowIfFromIsSmaller = true,
		bool TThrowIfToIsLarger = true
	>
		std::array<TOutputType, TSize> toArray(TFromIterable&& _iterable);

	template <
		typename TFromIterable,
		typename TOutputType = typename std::iter_value_t<types::BeginResult<TFromIterable>>,
		TOutputType(*TConverter)(types::DereferenceResult<types::BeginResult<TFromIterable>>) = types::cast<types::DereferenceResult<types::BeginResult<TFromIterable>>, TOutputType>
	>
		std::vector<TOutputType> toVector(TFromIterable&& _iterable);

	template <
		typename TFromIterable,
		typename TToIterable,
		typename TOutputType = typename std::iter_value_t<types::BeginResult<TFromIterable>>,
		TOutputType(*TConverter)(types::DereferenceResult<types::BeginResult<TFromIterable>>) = types::cast<types::DereferenceResult<types::BeginResult<TFromIterable>>, TOutputType>,
		bool TThrowIfFromIsSmaller = true,
		bool TThrowIfToIsLarger = true
	>
		void copy(TFromIterable&& _from, TToIterable& _to);

}

#define CPPUTILS_COLLECTIONS_CONVERSIONS_IMPLEMENTATION
#include <cpputils-IMPL/collections/conversions.tpp>
#undef CPPUTILS_COLLECTIONS_CONVERSIONS_IMPLEMENTATION

#endif