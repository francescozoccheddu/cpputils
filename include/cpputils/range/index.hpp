#pragma once

#include <iterator>
#include <cstddef>
#include <concepts>
#include <cpputils/range/iterators/IndexIterator.hpp>

namespace cpputils::range
{

    template<std::integral TIndex = std::size_t>
    auto index(TIndex _count, TIndex _from = {})
    {
        return Range<iterators::IndexIterator<TIndex>>{ { _from }, { _from + _count } };
    }

    template<typename TIterable>
    auto index(const TIterable& _iterable)
    {
        return index(std::size(_iterable), {});
    }

}