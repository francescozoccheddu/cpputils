#pragma once

#include <iterator>
#include <concepts>

namespace cpputils::range::iterators
{

    template<std::integral TIndex>
    class IndexIterator final
    {

    private:

        TIndex m_it;

    public:

        using value_type = TIndex;
        using reference = TIndex&;
        using pointer = TIndex*;
        using difference_type = TIndex;
        using iterator_category = std::random_access_iterator_tag;

        inline IndexIterator(const TIndex& _it)
            : m_it{ _it }
        {}

        inline value_type operator*() const noexcept
        {
            return m_it;
        }

        inline value_type operator[](difference_type _offset) const noexcept
        {
            return m_it + _offset;
        }

        inline IndexIterator& operator++() noexcept
        {
            ++m_it;
            return *this;
        }

        inline IndexIterator operator++(int) noexcept
        {
            return { m_it++ };
        }

        inline IndexIterator& operator+=(difference_type _offset) noexcept
        {
            m_it += _offset;
            return *this;
        }

        inline IndexIterator operator+(difference_type _offset) const noexcept
        {
            return { m_it + _offset };
        }

        inline IndexIterator& operator--() noexcept
        {
            --m_it;
            return *this;
        }

        inline IndexIterator operator--(int) noexcept
        {
            return { m_it-- };
        }

        inline IndexIterator& operator-=(difference_type _offset) noexcept
        {
            m_it -= _offset;
            return *this;
        }

        inline IndexIterator operator-(difference_type _offset) const noexcept
        {
            return { m_it - _offset };
        }

        inline auto operator<=>(const IndexIterator& _other) const noexcept = default;

        inline difference_type operator-(const IndexIterator& _other) const noexcept
        {
            return m_it - _other.m_it;
        }

    };

}