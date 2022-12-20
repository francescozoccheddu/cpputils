#pragma once

#include <iterator>
#include <cpputils/range/makeRange.hpp>
#include <cpputils/range/RangeSizer.hpp>
#include <cpputils/iterators/JoinIterator.hpp>

namespace cpputils::range
{

    template<typename TFirstIterable, typename TSecondIterable>
    auto join(const TFirstIterable& _firstIterable, const TSecondIterable& _secondIterable)
    {
        const RangeSizer<TFirstIterable> firstSizer{ _firstIterable };
        const RangeSizer<TSecondIterable> secondSizer{ _secondIterable };
        auto firstEnd{ std::end(_firstIterable) };
        auto secondBegin{ std::begin(_secondIterable) };
        return makeRange<iterators::JoinIterator<
            decltype(firstEnd),
            decltype(secondBegin)>,
            internal::sumCompTimeSizes(firstSizer.compTimeSize, secondSizer.compTimeSize)
        >(
            iterators::JoinIterator{ std::begin(_firstIterable), firstEnd, secondBegin, iterators::joinFirstTag },
            iterators::JoinIterator{ std::end(_secondIterable), firstEnd, secondBegin, iterators::joinSecondTag },
            internal::sumSizeHints(firstSizer.sizeHint(), secondSizer.sizeHint())
            );
    }

}