#pragma once

#include <optional>
#include <cstddef>
#include <cpputils/range/RangeSizer.hpp>
#include <cpputils/range/Range.hpp>

namespace cpputils::range
{

    template<typename TIterator, std::size_t TCompTimeSize = noCompTimeSize>
    inline auto makeRange(const TIterator& _begin, const TIterator& _end, const std::optional<std::size_t>& _sizeHint = std::nullopt)
    {
        if constexpr (TCompTimeSize != noCompTimeSize)
        {
            return Range<TIterator, TCompTimeSize>{ _begin, _end };
        }
        else
        {
            return Range<TIterator>{ _begin, _end, _sizeHint};
        }
    }

    template<typename TIterable, typename TIterator>
    inline auto makeRangeFrom(const TIterator& _begin, const TIterator& _end, const TIterable& _sourceIterable)
    {
        return makeRange<TIterator, internal::compTimeSize<TIterable>>(_begin, _end, RangeSizer<TIterable>{_sourceIterable}.sizeHint());
    }

}