#pragma once

#include <iterator>
#include <cstddef>
#include <cpputils/iterators/IndexIterator.hpp>
#include <cpputils/iterators/LinkedIndexIterator.hpp>
#include <cpputils/range/Range.hpp>
#include <cpputils/range/makeRange.hpp>
#include <cpputils/range/RangeSizer.hpp>

namespace cpputils::range
{

    template<typename TIndex = std::size_t>
    auto count(TIndex _count, TIndex _from = {})
    {
        return Range<iterators::IndexIterator<TIndex>>{ { _from }, { _from + _count }, static_cast<std::size_t>(_count) };
    }

    template<std::size_t TCount>
    auto count(std::size_t _from = {})
    {
        return Range<iterators::IndexIterator<std::size_t>, TCount>{ { _from }, { _from + TCount } };
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto index(TIterable& _iterable)
    {
        const RangeSizer<TIterable> sizer{ _iterable };
        return makeRangeFrom<TIterable>(iterators::IndexIterator<TIndex>{}, iterators::IndexIterator<TIndex>{ sizer.size() }, _iterable);
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto index(const TIterable& _iterable)
    {
        const RangeSizer<TIterable> sizer{ _iterable };
        return makeRangeFrom<TIterable>(iterators::IndexIterator<TIndex>{}, iterators::IndexIterator<TIndex>{ sizer.size() }, _iterable);
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto indexLazy(TIterable& _iterable)
    {
        return makeRangeFrom<TIterable, iterators::LinkedIndexIterator<decltype(std::begin(_iterable))>>({ std::begin(_iterable) }, { std::end(_iterable) }, _iterable);
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto indexLazy(const TIterable& _iterable)
    {
        return makeRangeFrom<TIterable, iterators::LinkedIndexIterator<decltype(std::begin(_iterable))>>({ std::begin(_iterable) }, { std::end(_iterable) }, _iterable);
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto indexLazyc(const TIterable& _iterable)
    {
        return makeRangeFrom<TIterable, iterators::LinkedIndexIterator<decltype(std::cbegin(_iterable))>>({ std::cbegin(_iterable) }, { std::cend(_iterable) }, _iterable);
    }

}