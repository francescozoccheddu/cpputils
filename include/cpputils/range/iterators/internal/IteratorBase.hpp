#pragma once

#include <cpputils/range/internal/Data.hpp>
#include <memory>
#include <iterator>
#include <type_traits>

namespace cpputils::range::iterators::internal
{

    template<typename TIterator>
    class IteratorBase
    {

    private:

        std::shared_ptr<range::internal::Data<TIterator>> m_data;

    protected:

        IteratorBase(const std::shared_ptr<range::internal::Data<TIterator>>& _data): m_data{ _data } {}

    public:

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