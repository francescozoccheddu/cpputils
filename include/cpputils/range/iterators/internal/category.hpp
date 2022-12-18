#pragma once

#include <iterator>
#include <type_traits>

namespace cpputils::range::iterators::internal
{

    template<typename TIterator>
    using Category = std::iterator_traits<TIterator>::template iterator_category;

    template<typename TCategory>
    constexpr bool isRandomAccessCategory = std::is_same_v<std::random_access_iterator_tag, TCategory>;

    template<typename TCategory>
    constexpr bool isBidirectionalCategory = std::is_same_v<std::bidirectional_iterator_tag, TCategory> || isRandomAccessCategory<TCategory>;

    template<typename TCategory>
    constexpr bool isForwardCategory = std::is_same_v<std::forward_iterator_tag, TCategory> || isBidirectionalCategory<TCategory>;

    template<typename TIterator>
    constexpr bool isRandomAccessIterator = isRandomAccessCategory<Category<TIterator>>;

    template<typename TIterator>
    constexpr bool isBidirectionalIterator = isBidirectionalCategory<Category<TIterator>>;

    template<typename TIterator>
    constexpr bool isForwardIterator = isForwardCategory<Category<TIterator>>;

}