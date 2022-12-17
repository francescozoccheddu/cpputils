#pragma once

#include <cpputils/range/Range.hpp>

namespace cpputils::range
{

    namespace internal
    {

        template <typename TIterable>
        using BeginResult = decltype(std::begin(std::declval<TIterable>()));

        template <typename TIterable>
        using CBeginResult = decltype(std::cbegin(std::declval<TIterable>()));

        template <typename TIterable>
        using RBeginResult = decltype(std::rbegin(std::declval<TIterable>()));

        template <typename TIterable>
        using CRBeginResult = decltype(std::crbegin(std::declval<TIterable>()));

    }

    template<typename TIterable>
    Range<internal::BeginResult<TIterable&>> of(TIterable& _iterable)
    {
        return Range{ std::begin(_iterable), std::end(_iterable) };
    }

    template<typename TIterable>
    Range<internal::BeginResult<const TIterable&>> of(const TIterable& _iterable)
    {
        return Range{ std::begin(_iterable), std::end(_iterable) };
    }

    template<typename TIterable>
    Range<internal::CBeginResult<const TIterable&>> ofc(const TIterable& _iterable)
    {
        return Range{ std::cbegin(_iterable), std::cend(_iterable) };
    }

    template<typename TIterable>
    Range<internal::RBeginResult<TIterable&>> ofr(TIterable& _iterable)
    {
        return Range{ std::rbegin(_iterable), std::rend(_iterable) };
    }

    template<typename TIterable>
    Range<internal::RBeginResult<const TIterable&>> ofr(const TIterable& _iterable)
    {
        return Range{ std::rbegin(_iterable), std::rend(_iterable) };
    }

    template<typename TIterable>
    Range<internal::CRBeginResult<const TIterable&>> ofcr(const TIterable& _iterable)
    {
        return Range{ std::crbegin(_iterable), std::crend(_iterable) };
    }

}