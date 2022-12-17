#pragma once

#include <cpputils/range/iterators/SkipIterator.hpp>

namespace cpputils::range::iterators
{

    namespace internal
    {

        template<typename TIterator>
        constexpr bool filterShouldSkip(const TIterator& _it, const TIterator& _begin, const TIterator& _end)
        {
            return !*_it;
        }

    }

    template<typename TIterator>
    class FilterIterator final: public SkipIterator<TIterator, internal::filterShouldSkip<TIterator>>
    {

    private:

        using Base = SkipIterator<TIterator, internal::filterShouldSkip<TIterator>>;

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        using Base::Base;

    };

}