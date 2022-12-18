#pragma once

#include <optional>
#include <cstddef>
#include <iterator>

namespace cpputils::range
{

    template<typename TIterable>
    std::optional<std::size_t> sizeHint(const TIterable& _iterable)
    {
        if constexpr (requires{ std::size(_iterable); })
        {
            return std::size(_iterable);
        }
        else
        {
            return std::nullopt;
        }
    }

}