#pragma once

#include <iterator>

namespace cpputils::iterators
{

    template<typename TIterator>
    class ReverseIterator final
    {

    private:

        TIterator m_it;

    public:

        using value_type = std::iter_value_t<TIterator>;
        using reference = std::iter_reference_t<TIterator>;
        using pointer = std::remove_reference_t<reference>*;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = typename std::template iterator_traits<TIterator>::iterator_category;

        ReverseIterator()
        {}

        ReverseIterator(const TIterator& _it)
            : m_it{ _it }
        {}

        reference operator*() const
        {
            return *m_it;
        }

        pointer operator->() const
        {
            if constexpr (requires{ m_it.operator->(); })
            {
                return m_it.operator->();
            }
            return std::addressof(*m_it);
        }

        reference operator[](difference_type _offset) const
        {
            return *(m_it - _offset);
        }

        ReverseIterator& operator++()
        {
            --m_it;
            return *this;
        }

        ReverseIterator operator++(int)
        {
            return { m_it-- };
        }

        ReverseIterator& operator+=(difference_type _offset)
        {
            m_it -= _offset;
            return *this;
        }

        ReverseIterator operator+(difference_type _offset) const
        {
            return { m_it - _offset };
        }

        friend ReverseIterator operator+(difference_type _offset, const ReverseIterator& _iterator)
        {
            return { _iterator.m_it - _offset };
        }

        ReverseIterator& operator--()
        {
            ++m_it;
            return *this;
        }

        ReverseIterator operator--(int)
        {
            return { m_it++ };
        }

        ReverseIterator& operator-=(difference_type _offset)
        {
            m_it += _offset;
            return *this;
        }

        ReverseIterator operator-(difference_type _offset) const
        {
            return { m_it + _offset };
        }

        friend ReverseIterator operator-(difference_type _offset, const ReverseIterator& _iterator)
        {
            return { _iterator.m_it + _offset };
        }

        bool operator==(const ReverseIterator& _other) const = default;

        auto operator<=>(const ReverseIterator& _other) const
        {
            return _other.m_it <=> m_it;
        }

        difference_type operator-(const ReverseIterator& _other) const
        {
            return _other.m_it - m_it;
        }

    };

}