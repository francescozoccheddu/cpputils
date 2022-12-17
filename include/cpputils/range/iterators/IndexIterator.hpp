#pragma once

#include <iterator>

namespace cpputils::range::iterators
{

    template<typename TIndex>
    class IndexIterator final
    {

    private:

        TIndex m_it;

    public:

        using value_type = TIndex;
        using reference = TIndex&;
        using pointer = TIndex*;
        using difference_type = TIndex;
        using iterator_category = std::bidirectional_iterator_tag;

        IndexIterator(const TIndex& _it)
            : m_it{ _it }
        {}

        value_type operator*() const
        {
            return m_it;
        }

        pointer operator->() const
        {
            return std::addressof(m_it);
        }

        value_type operator[](difference_type _offset) const
        {
            return m_it + _offset;
        }

        IndexIterator& operator++()
        {
            ++m_it;
            return *this;
        }

        IndexIterator operator++(int)
        {
            return { m_it++ };
        }

        IndexIterator& operator+=(difference_type _offset)
        {
            m_it += _offset;
            return *this;
        }

        IndexIterator operator+(difference_type _offset) const
        {
            return { m_it + _offset };
        }

        IndexIterator& operator--()
        {
            --m_it;
            return *this;
        }

        IndexIterator operator--(int)
        {
            return { m_it-- };
        }

        IndexIterator& operator-=(difference_type _offset)
        {
            m_it -= _offset;
            return *this;
        }

        IndexIterator operator-(difference_type _offset) const
        {
            return { m_it - _offset };
        }

        bool operator==(const IndexIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        difference_type operator-(const IndexIterator& _other) const
        {
            return m_it - _other.m_it;
        }

    };

}