#pragma once

#include <cpputils/range/makeRange.hpp>
#include <cpputils/range/RangeSizer.hpp>
#include <iterator>

namespace cpputils::range
{

    template<typename TIterable>
    auto of(TIterable& _iterable)
    {
        return makeRange<decltype(std::begin(_iterable)), internal::compTimeSize<TIterable>>(std::begin(_iterable), std::end(_iterable), RangeSizer<TIterable>{_iterable}.sizeHint());
    }

    template<typename TIterable>
    auto of(const TIterable& _iterable)
    {
        return makeRange<decltype(std::begin(_iterable)), internal::compTimeSize<TIterable>>(std::begin(_iterable), std::end(_iterable), RangeSizer<TIterable>{_iterable}.sizeHint());
    }

    template<typename TIterable>
    auto ofc(const TIterable& _iterable)
    {
        return makeRange<decltype(std::cbegin(_iterable)), internal::compTimeSize<TIterable>>(std::cbegin(_iterable), std::cend(_iterable), RangeSizer<TIterable>{_iterable}.sizeHint());
    }

    template<typename TIterable>
    auto ofr(TIterable& _iterable)
    {
        return makeRange<decltype(std::rbegin(_iterable)), internal::compTimeSize<TIterable>>(std::rbegin(_iterable), std::rend(_iterable), RangeSizer<TIterable>{_iterable}.sizeHint());
    }

    template<typename TIterable>
    auto ofr(const TIterable& _iterable)
    {
        return makeRange<decltype(std::rbegin(_iterable)), internal::compTimeSize<TIterable>>(std::rbegin(_iterable), std::rend(_iterable), RangeSizer<TIterable>{_iterable}.sizeHint());
    }

    template<typename TIterable>
    auto ofcr(const TIterable& _iterable)
    {
        return makeRange<decltype(std::crbegin(_iterable)), internal::compTimeSize<TIterable>>(std::crbegin(_iterable), std::crend(_iterable), RangeSizer<TIterable>{_iterable}.sizeHint());
    }

}