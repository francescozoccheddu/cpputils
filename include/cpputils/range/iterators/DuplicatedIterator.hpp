#pragma once

#include <cpputils/range/iterators/SkipIterator.hpp>

namespace cpputils::range::iterators
{

    namespace internal
    {

        template<typename TIterator>
        constexpr bool duplicatedShouldSkip(const TIterator& _it, const IteratorBase<TIterator>& _this)
        {
            const TIterator next{ std::next(_it) };
            return next != _this.end() && *next != *_it;
        }

    }

    template<typename TIterator>
    class DuplicatedIterator final: public SkipIterator<TIterator, internal::duplicatedShouldSkip<TIterator>>
    {

    private:

        using Base = SkipIterator<TIterator, internal::duplicatedShouldSkip<TIterator>>;

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        using Base::Base;

    };

}