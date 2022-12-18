#pragma once

#include <cpputils/range/RangeMaker.hpp>
#include <iterator>

namespace cpputils::range
{

    template<typename TIterable>
    auto of(TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.make(std::begin(_iterable), std::end(_iterable));
    }

    template<typename TIterable>
    auto of(const TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.make(std::begin(_iterable), std::end(_iterable));
    }

    template<typename TIterable>
    auto ofc(const TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.make(std::cbegin(_iterable), std::cend(_iterable));
    }

    template<typename TIterable>
    auto ofr(TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.make(std::rbegin(_iterable), std::rend(_iterable));
    }

    template<typename TIterable>
    auto ofr(const TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.make(std::rbegin(_iterable), std::rend(_iterable));
    }

    template<typename TIterable>
    auto ofcr(const TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.make(std::crbegin(_iterable), std::crend(_iterable));
    }

}