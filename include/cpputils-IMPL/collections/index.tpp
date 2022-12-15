#ifndef CPPUTILS_COLLECTIONS_INDEX_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/index.hpp>

#include <iterator>

namespace cpputils::collections
{

	template<typename TIterator, typename TIndex = std::size_t>
	const Iota<TIndex> index(const TIterator& _iterator)
	{
		return index<TIndex>(_iterator, TIndex{});
	}

	template<typename TIndex, typename TIterator>
	const Iota<TIndex> index(const TIterator& _iterator, TIndex _start)
	{
		return iota<TIndex>(static_cast<TIndex>(std::size(_iterator)), _start);
	}

	template<typename TIndex>
	const Iota<TIndex> iota(TIndex _count, TIndex _start)
	{
		return std::ranges::views::iota(_start, _start + _count);
	}

}
