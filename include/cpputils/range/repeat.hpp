#pragma once

#include <iterator>
#include <cstddef>
#include <cpputils/range/index.hpp>

namespace cpputils::range
{

    template<typename TValue>
    auto repeat(std::size_t _count, const TValue& _value = {})
    {
        return count(_count).map([_value](std::size_t _s) { return _value; });
    }

    template<std::size_t TCount, typename TValue>
    auto repeat(const TValue& _value = {})
    {
        return count<TCount>().map([_value](std::size_t _s) { return _value; });
    }

}