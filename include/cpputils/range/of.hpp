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

    template<typename TIterable, typename TValue = std::iter_value_t<internal::BeginResult<TIterable&>>>
    Range<internal::BeginResult<TIterable&>, TValue> of(TIterable& _iterable)
    {
        return Range{ std::begin(_iterable), std::end(_iterable) };
    }

    template<typename TIterable, typename TValue = std::iter_value_t<internal::BeginResult<const TIterable&>>>
    Range<internal::BeginResult<const TIterable&>, TValue> of(const TIterable& _iterable)
    {
        return Range{ std::begin(_iterable), std::end(_iterable) };
    }

    template<typename TIterable, typename TValue = std::iter_value_t<internal::CBeginResult<const TIterable&>>>
    Range<internal::CBeginResult<const TIterable&>, TValue> ofc(const TIterable& _iterable)
    {
        return Range{ std::cbegin(_iterable), std::cend(_iterable) };
    }

    template<typename TIterable, typename TValue = std::iter_value_t<internal::RBeginResult<TIterable&>>>
    Range<internal::RBeginResult<TIterable&>, TValue> ofr(TIterable& _iterable)
    {
        return Range{ std::rbegin(_iterable), std::rend(_iterable) };
    }

    template<typename TIterable, typename TValue = std::iter_value_t<internal::RBeginResult<const TIterable&>>>
    Range<internal::RBeginResult<const TIterable&>, TValue> ofr(const TIterable& _iterable)
    {
        return Range{ std::rbegin(_iterable), std::rend(_iterable) };
    }

    template<typename TIterable, typename TValue = std::iter_value_t<internal::CRBeginResult<const TIterable&>>>
    Range<internal::CRBeginResult<const TIterable&>, TValue> ofcr(const TIterable& _iterable)
    {
        return Range{ std::crbegin(_iterable), std::crend(_iterable) };
    }

}