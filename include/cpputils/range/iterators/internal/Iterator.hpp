#pragma once

#include <cpputils/range/iterators/internal/IteratorBase.hpp>
#include <memory>
#include <iterator>
#include <type_traits>

namespace cpputils::range::iterators::internal
{

    template<typename TIterator>
    using Category = std::conditional_t<std::bidirectional_iterator<TIterator>, std::bidirectional_iterator_tag, std::forward_iterator_tag>;

    template<typename TIterator, typename TReference = std::iter_reference_t<const TIterator>>
    class Iterator: public IteratorBase<TIterator>
    {

    public:

        using value_type = std::remove_cvref_t<TReference>;
        using reference = TReference;
        using pointer = std::remove_reference_t<TReference>*;
        using difference_type = std::iter_difference_t<const TIterator>;
        using iterator_category = Category<const TIterator>;

    protected:

        using IteratorBase<TIterator>::IteratorBase;

    };

}