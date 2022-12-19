#pragma once

#include <iterator>
#include <concepts>

namespace cpputils::iterators
{

    template<typename TIterator, std::integral TIndex = std::iter_difference_t<TIterator>>
    class LinkedIndexIterator final
    {

    private:

        TIterator m_it;
        std::ptrdiff_t m_i;

    public:

        using value_type = TIndex;
        using reference = TIndex;
        using pointer = const std::ptrdiff_t*;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = typename std::template iterator_traits<TIterator>::iterator_category;

        LinkedIndexIterator()
        {}

        LinkedIndexIterator(const TIterator& _it, const TIndex& _index = {})
            : m_it{ _it }, m_i{ static_cast<std::ptrdiff_t>(_index) }
        {}

        reference operator*() const noexcept
        {
            return static_cast<TIndex>(m_i);
        }

        pointer operator->() const noexcept
        {
            return std::addressof(m_i);
        }

        reference operator[](difference_type _offset) const noexcept
        {
            return static_cast<TIndex>(m_i + _offset);
        }

        LinkedIndexIterator& operator++()
        {
            ++m_it;
            ++m_i;
            return *this;
        }

        LinkedIndexIterator operator++(int)
        {
            return { m_it++, m_i++ };
        }

        LinkedIndexIterator& operator+=(difference_type _offset)
        {
            m_it += _offset;
            m_i += _offset;
            return *this;
        }

        LinkedIndexIterator operator+(difference_type _offset) const
        {
            return { m_it + _offset, m_i + _offset };
        }

        friend LinkedIndexIterator operator+(difference_type _offset, const LinkedIndexIterator& _iterator)
        {
            return { _iterator.m_it + _offset, _iterator.m_i + _offset };
        }

        LinkedIndexIterator& operator--()
        {
            --m_it;
            --m_i;
            return *this;
        }

        LinkedIndexIterator operator--(int)
        {
            return { m_it--, m_i-- };
        }

        LinkedIndexIterator& operator-=(difference_type _offset)
        {
            m_it -= _offset;
            m_i -= _offset;
            return *this;
        }

        LinkedIndexIterator operator-(difference_type _offset) const
        {
            return { m_it - _offset, m_i - _offset };
        }

        friend LinkedIndexIterator operator-(difference_type _offset, const LinkedIndexIterator& _iterator)
        {
            return { _iterator.m_it - _offset, _iterator.m_i - _offset };
        }

        bool operator==(const LinkedIndexIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        auto operator<=>(const LinkedIndexIterator& _other) const
        {
            return m_it <=> _other.m_it;
        }

        difference_type operator-(const LinkedIndexIterator& _other) const
        {
            return m_it - _other.m_it;
        }

    };

}