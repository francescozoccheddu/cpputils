#pragma once

#include <cpputils/range/Range.hpp>
#include <cpputils/range/iterators/ZipIterator.hpp>

namespace cpputils::range
{

    template<typename TIterable, typename ... TIterables>
    auto zip(TIterable& _iterable, TIterables& ..._iterables)
    {
        return Range{ iterators::ZipIterator{ std::begin(_iterable), std::begin(_iterables)...}, iterators::ZipIterator{ std::end(_iterable), std::end(_iterables)...} };
    }

    template<typename TIterable, typename ... TIterables>
    auto zip(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return Range{ iterators::ZipIterator{ std::begin(_iterable), std::begin(_iterables)...}, iterators::ZipIterator{ std::end(_iterable), std::end(_iterables)...} };
    }

    template<typename TIterable, typename ... TIterables>
    auto zipc(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return Range{ iterators::ZipIterator{ std::cbegin(_iterable), std::cbegin(_iterables)...}, iterators::ZipIterator{ std::cend(_iterable), std::cend(_iterables)...} };
    }

    template<typename TIterable, typename ... TIterables>
    auto zipr(TIterable& _iterable, TIterables& ..._iterables)
    {
        return Range{ iterators::ZipIterator{ std::rbegin(_iterable), std::rbegin(_iterables)...}, iterators::ZipIterator{ std::rend(_iterable), std::rend(_iterables)...} };
    }

    template<typename TIterable, typename ... TIterables>
    auto zipr(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return Range{ iterators::ZipIterator{ std::rbegin(_iterable), std::rbegin(_iterables)...}, iterators::ZipIterator{ std::rend(_iterable), std::rend(_iterables)...} };
    }

    template<typename TIterable, typename ... TIterables>
    auto zipcr(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return Range{ iterators::ZipIterator{ std::crbegin(_iterable), std::crbegin(_iterables)...}, iterators::ZipIterator{ std::crend(_iterable), std::crend(_iterables)...} };
    }

}