#pragma once

#include <cpputils/range/internal/Data.hpp>
#include <memory>
#include <iterator>
#include <type_traits>

namespace cpputils::range::internal
{

    template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
    class Iterator
    {

    private:

        std::shared_ptr<internal::Data<TIterator, TValue>> m_data;

    public:

        using value_type = TValue;
        using reference = TValue&;
        using pointer = TValue*;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = std::conditional_t<std::bidirectional_iterator<TIterator>, std::bidirectional_iterator_tag, std::forward_iterator_tag>;

    protected:

        Iterator(const std::shared_ptr<internal::Data<TIterator, TValue>>& _data): m_data{ _data } {}

        const TIterator& begin() const
        {
            return m_data->begin();
        }

        const TIterator& end() const
        {
            return m_data->end();
        }

    };

}