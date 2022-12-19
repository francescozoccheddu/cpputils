#pragma once

#include <iterator>
#include <cstddef>
#include <concepts>
#include <cpputils/iterators/StandaloneIndexIterator.hpp>
#include <cpputils/iterators/LinkedIndexIterator.hpp>
#include <cpputils/range/Range.hpp>
#include <cpputils/range/RangeMaker.hpp>

namespace cpputils::range
{

    template<typename TIndex = std::size_t>
    auto count(TIndex _count, TIndex _from = {})
    {
        return Range<iterators::StandaloneIndexIterator<TIndex>>{ { _from }, { _from + _count }, static_cast<std::size_t>(_count) };
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto index(TIterable& _iterable)
    {
        const RangeMaker<TIterable> maker{ _iterable };
        return maker.make(iterators::StandaloneIndexIterator<TIndex>{}, iterators::StandaloneIndexIterator<TIndex>{ maker.size() });
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto index(const TIterable& _iterable)
    {
        const RangeMaker<TIterable> maker{ _iterable };
        return maker.make(iterators::StandaloneIndexIterator<TIndex>{}, iterators::StandaloneIndexIterator<TIndex>{ maker.size() });
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto indexLazy(TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.template make<iterators::LinkedIndexIterator<decltype(std::begin(_iterable)), TIndex>>({ std::begin(_iterable) }, { std::end(_iterable) });
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto indexLazy(const TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.template make<iterators::LinkedIndexIterator<decltype(std::begin(_iterable)), TIndex>>({ std::begin(_iterable) }, { std::end(_iterable) });
    }

    template<typename TIndex = std::size_t, typename TIterable>
    auto indexLazyc(const TIterable& _iterable)
    {
        return RangeMaker<TIterable>{_iterable}.template make<iterators::LinkedIndexIterator<decltype(std::cbegin(_iterable)), TIndex>>({ std::cbegin(_iterable) }, { std::cend(_iterable) });
    }

}