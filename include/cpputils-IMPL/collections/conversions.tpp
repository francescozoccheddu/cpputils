#ifndef CPPUTILS_COLLECTIONS_CONVERSIONS_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/conversions.hpp>

#include <stdexcept>
#include <iterator>

namespace cpputils::collections::conversions
{

	template<
		std::size_t TSize,
		typename TFromIterable,
		typename TOutputType,
		TOutputType(*TConverter)(types::DereferenceResult<types::Iterator<TFromIterable>>),
		bool TThrowIfFromIsSmaller,
		bool TThrowIfToIsLarger
	>
		std::array<TOutputType, TSize> toArray(TFromIterable& _from)
	{
		std::array<TOutputType, TSize> to;
		copy<TFromIterable, std::array<TOutputType, TSize>, TOutputType, TConverter, TThrowIfFromIsSmaller, TThrowIfToIsLarger>(_from, to);
		return to;
	}

	template<
		typename TFromIterable,
		typename TOutputType,
		TOutputType(*TConverter)(types::DereferenceResult<types::Iterator<TFromIterable>>)
	>
		std::vector<TOutputType> toVector(TFromIterable& _from)
	{
		std::vector<TOutputType> to(std::size(_from));
		copy<TFromIterable, std::vector<TOutputType>, TOutputType, TConverter>(_from, to);
		return to;
	}

	template<
		typename TFromIterable,
		typename TToIterable,
		typename TOutputType,
		TOutputType(*TConverter)(types::DereferenceResult<types::Iterator<TFromIterable>>),
		bool TThrowIfToIsSmaller,
		bool TThrowIfToIsLarger
	>
		void copy(TFromIterable& _from, TToIterable& _to)
	{
		const std::size_t fromSize{ std::size(_from) };
		const std::size_t toSize{ std::size(_to) };
		if (TThrowIfToIsSmaller && fromSize < toSize)
		{
			throw std::logic_error{ "_from size < _to size" };
		}
		if (TThrowIfToIsLarger && fromSize > toSize)
		{
			throw std::logic_error{ "_from size > _to size" };
		}
		auto fromIt{ _from.begin() };
		auto toIt{ _to.begin() };
		const auto fromEnd{ _from.end() };
		const auto toEnd{ _to.end() };
		while (fromIt != fromEnd && toIt != toEnd)
		{
			*toIt = TConverter(*fromIt);
			++toIt;
			++fromIt;
		}
	}

}
