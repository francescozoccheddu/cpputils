#pragma once

#include <cpputils/range/iterators/internal/category.hpp>
#include <memory>
#include <iterator>
#include <type_traits>

namespace cpputils::range::iterators::internal
{

    template<typename TIterator, typename TReference = std::iter_reference_t<const TIterator>, typename TCategory = Category<const TIterator>>
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