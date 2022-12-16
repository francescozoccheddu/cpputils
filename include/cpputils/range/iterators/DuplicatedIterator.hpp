#pragma once

#include <cpputils/range/iterators/SkipIterator.hpp>

namespace cpputils::range::iterators
{

    namespace internal
    {

        template<typename TIterator>
        constexpr bool duplicatedShouldSkip(const TIterator& _it, const TIterator& _begin, const TIterator& _end)
        {
            const TIterator next{ std::next(_it) };
            return next != _end && *next != *_it;
        }

    }

    template<typename TIterator, typename TValue>
    class DuplicatedIterator final: public SkipIterator<TIterator, TValue, internal::duplicatedShouldSkip<TIterator>>
    {

    private:

        using Base = SkipIterator<TIterator, TValue, internal::duplicatedShouldSkip<TIterator>>;

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        using Base::Base;

    };

}