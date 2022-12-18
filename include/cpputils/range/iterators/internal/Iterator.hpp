#pragma once

#include <memory>
#include <iterator>
#include <type_traits>

namespace cpputils::range::iterators::internal
{

    template<typename TIterator>
    using BidirectionalCategory = std::conditional_t<std::bidirectional_iterator<TIterator>, std::bidirectional_iterator_tag, std::forward_iterator_tag>;

    template<typename TIterator>
    using RandomAccessCategory = std::conditional_t<std::random_access_iterator<TIterator>, std::random_access_iterator_tag, BidirectionalCategory<TIterator>>;

    template<typename TIterator, typename TReference = std::iter_reference_t<const TIterator>, typename TCategory = RandomAccessCategory<const TIterator>>
    class Iterator
    {

    private:

        std::shared_ptr<range::internal::Data<TIterator>> m_data;

    protected:

        Iterator(const std::shared_ptr<range::internal::Data<TIterator>>& _data): m_data{ _data } {}

    public:

        using value_type = std::remove_cvref_t<TReference>;
        using reference = TReference;
        using pointer = std::remove_reference_t<TReference>*;
        using difference_type = std::iter_difference_t<const TIterator>;
        using iterator_category = TCategory;

        inline const TIterator& begin() const noexcept
        {
            return m_data->begin();
        }

        inline const TIterator& end() const noexcept
        {
            return m_data->end();
        }

    };

}