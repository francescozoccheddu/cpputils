#pragma once

#include <cpputils/range/Range.hpp>

namespace cpputils::range
{

    template<typename TIterable>
    auto of(TIterable& _iterable)
    {
        return Range{ std::begin(_iterable), std::end(_iterable), sizeHint(_iterable) };
    }

    template<typename TIterable>
    auto of(const TIterable& _iterable)
    {
        return Range{ std::begin(_iterable), std::end(_iterable), sizeHint(_iterable) };
    }

    template<typename TIterable>
    auto ofc(const TIterable& _iterable)
    {
        return Range{ std::cbegin(_iterable), std::cend(_iterable), sizeHint(_iterable) };
    }

    template<typename TIterable>
    auto ofr(TIterable& _iterable)
    {
        return Range{ std::rbegin(_iterable), std::rend(_iterable), sizeHint(_iterable) };
    }

    template<typename TIterable>
    auto ofr(const TIterable& _iterable)
    {
        return Range{ std::rbegin(_iterable), std::rend(_iterable), sizeHint(_iterable) };
    }

    template<typename TIterable>
    auto ofcr(const TIterable& _iterable)
    {
        return Range{ std::crbegin(_iterable), std::crend(_iterable), sizeHint(_iterable) };
    }

}