#pragma once

#include <cpputils/range/makeRange.hpp>
#include <cpputils/range/RangeSizer.hpp>
#include <iterator>

namespace cpputils::range
{

    template<typename TIterable>
    auto of(TIterable& _iterable)
    {
        return makeRangeFrom<TIterable>(std::begin(_iterable), std::end(_iterable), _iterable);
    }

    template<typename TIterable>
    auto of(const TIterable& _iterable)
    {
        return makeRangeFrom<TIterable>(std::begin(_iterable), std::end(_iterable), _iterable);
    }

    template<typename TIterable>
    auto ofc(const TIterable& _iterable)
    {
        return makeRangeFrom<TIterable>(std::cbegin(_iterable), std::cend(_iterable), _iterable);
    }

    template<typename TIterable>
    auto ofr(TIterable& _iterable)
    {
        return makeRangeFrom<TIterable>(std::rbegin(_iterable), std::rend(_iterable), _iterable);
    }

    template<typename TIterable>
    auto ofr(const TIterable& _iterable)
    {
        return makeRangeFrom<TIterable>(std::rbegin(_iterable), std::rend(_iterable), _iterable);
    }

    template<typename TIterable>
    auto ofcr(const TIterable& _iterable)
    {
        return makeRangeFrom<TIterable>(std::crbegin(_iterable), std::crend(_iterable), _iterable);
    }

}