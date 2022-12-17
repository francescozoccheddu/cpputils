#pragma once

#include <cpputils/range/Range.hpp>
#include <cpputils/range/enumerate.hpp>
#include <cpputils/range/index.hpp>

namespace cpputils::range
{

    template<typename TIterable, typename ... TIterables>
    auto enumerate(TIterable& _iterable, TIterables& ..._iterables)
    {
        return zip(index(_iterable), _iterable, _iterables...);
    }

    template<typename TIterable, typename ... TIterables>
    auto enumerate(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return zip(index(_iterable), _iterable, _iterables...);
    }

    template<typename TIterable, typename ... TIterables>
    auto enumeratec(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return zipc(index(_iterable), _iterable, _iterables...);
    }

}