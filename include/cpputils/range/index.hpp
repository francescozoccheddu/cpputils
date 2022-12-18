#pragma once

#include <iterator>
#include <cstddef>
#include <concepts>
#include <cpputils/iterators/StandaloneIndexIterator.hpp>
#include <cpputils/iterators/LinkedIndexIterator.hpp>
#include <cpputils/range/Range.hpp>
#include <cpputils/range/sizeHint.hpp>

namespace cpputils::range
{

    template<std::integral TIndex = std::size_t>
    auto index(TIndex _count, TIndex _from = {})
    {
        return Range<iterators::StandaloneIndexIterator<TIndex>>{ { _from }, { _from + _count }, static_cast<std::size_t>(_count) };
    }

    template<std::integral TIndex = std::size_t, typename TIterable>
    auto index(TIterable& _iterable)
    {
        return index<TIndex>(static_cast<TIndex>(std::size(_iterable)), TIndex{});
    }

    template<std::integral TIndex = std::size_t, typename TIterable>
    auto index(const TIterable& _iterable)
    {
        return index<TIndex>(static_cast<TIndex>(std::size(_iterable)), TIndex{});
    }

    template<std::integral TIndex = std::size_t, typename TIterable>
    auto indexLazy(TIterable& _iterable)
    {
        return Range<iterators::LinkedIndexIterator<decltype(std::begin(_iterable)), TIndex>>{ { std::begin(_iterable) }, { std::end(_iterable) }, sizeHint(_iterable) };
    }

    template<std::integral TIndex = std::size_t, typename TIterable>
    auto indexLazy(const TIterable& _iterable)
    {
        return Range<iterators::LinkedIndexIterator<decltype(std::begin(_iterable)), TIndex>>{ { std::begin(_iterable) }, { std::end(_iterable) }, sizeHint(_iterable) };
    }

    template<std::integral TIndex = std::size_t, typename TIterable>
    auto indexLazyc(const TIterable& _iterable)
    {
        return Range<iterators::LinkedIndexIterator<decltype(std::cbegin(_iterable)), TIndex>>{ { std::cbegin(_iterable) }, { std::cend(_iterable) }, sizeHint(_iterable) };
    }

}