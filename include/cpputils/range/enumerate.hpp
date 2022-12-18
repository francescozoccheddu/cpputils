#pragma once

#include <cpputils/range/zip.hpp>
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

    template<typename TIterable, typename ... TIterables>
    auto enumerateLazy(TIterable& _iterable, TIterables& ..._iterables)
    {
        return zip(indexLazy(_iterable), _iterable, _iterables...);
    }

    template<typename TIterable, typename ... TIterables>
    auto enumerateLazy(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return zip(indexLazy(_iterable), _iterable, _iterables...);
    }

    template<typename TIterable, typename ... TIterables>
    auto enumerateLazyc(const TIterable& _iterable, const TIterables& ..._iterables)
    {
        return zipc(indexLazy(_iterable), _iterable, _iterables...);
    }

}