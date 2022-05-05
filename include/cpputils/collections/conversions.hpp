#ifndef CPPUTILS_COLLECTIONS_CONVERSIONS_INCLUDED
#define CPPUTILS_COLLECTIONS_CONVERSIONS_INCLUDED

#include <cpputils/collections/types.hpp>
#include <type_traits>
#include <cstddef>
#include <array>
#include <vector>

namespace cpputils::collections::conversions
{

	template<
		std::size_t TSize,
		typename TFromIterable,
		typename TOutputType = typename types::Iterator<TFromIterable>::value_type,
		TOutputType(*TConverter)(types::DereferenceResult<types::Iterator<TFromIterable>>) = types::cast<types::DereferenceResult<types::Iterator<TFromIterable>>, TOutputType>,
		bool TThrowIfFromIsSmaller = true,
		bool TThrowIfToIsLarger = true
	>
		std::array<TOutputType, TSize> toArray(TFromIterable&& _iterable);

	template<
		typename TFromIterable,
		typename TOutputType = typename types::Iterator<TFromIterable>::value_type,
		TOutputType(*TConverter)(types::DereferenceResult<types::Iterator<TFromIterable>>) = types::cast<types::DereferenceResult<types::Iterator<TFromIterable>>, TOutputType>
	>
		std::vector<TOutputType> toVector(TFromIterable&& _iterable);

	template<
		typename TFromIterable,
		typename TToIterable,
		typename TOutputType = typename types::Iterator<TFromIterable>::value_type,
		TOutputType(*TConverter)(types::DereferenceResult<types::Iterator<TFromIterable>>) = types::cast<types::DereferenceResult<types::Iterator<TFromIterable>>, TOutputType>,
		bool TThrowIfFromIsSmaller = true,
		bool TThrowIfToIsLarger = true
	>
		void copy(TFromIterable&& _from, TToIterable& _to);

}

#define CPPUTILS_COLLECTIONS_CONVERSIONS_IMPLEMENTATION
#include <cpputils-IMPL/collections/conversions.tpp>
#undef CPPUTILS_COLLECTIONS_CONVERSIONS_IMPLEMENTATION

#endif