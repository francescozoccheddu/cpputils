#ifndef CPPUTILS_COLLECTIONS_INDEX_INCLUDED
#define CPPUTILS_COLLECTIONS_INDEX_INCLUDED

#include <ranges>

namespace cpputils::collections
{

    template<typename TIndex>
    using Iota = std::ranges::iota_view < TIndex, TIndex>;

    template<typename TIterator, typename TIndex = std::size_t>
    const Iota<TIndex> index(const TIterator& _iterator);

    template<typename TIndex, typename TIterator>
    const Iota<TIndex> index(const TIterator& _iterator, TIndex _start);

    template<typename TIndex>
    const Iota<TIndex> iota(TIndex _count, TIndex _start = std::size_t{});

}

#define CPPUTILS_COLLECTIONS_INDEX_IMPLEMENTATION
#include <cpputils-IMPL/collections/index.tpp>
#undef CPPUTILS_COLLECTIONS_INDEX_IMPLEMENTATION

#endif