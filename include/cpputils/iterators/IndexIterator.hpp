#pragma once

#include <iterator>

namespace cpputils::iterators
{

    template<typename TIndex = std::size_t>
    class IndexIterator final
    {

    private:

        TIndex m_i;

    public:

        using value_type = TIndex;
        using reference = TIndex;
        using pointer = const TIndex*;
        using difference_type = TIndex;
        using iterator_category = std::random_access_iterator_tag;

        IndexIterator(const TIndex& _index = {})
            : m_i{ _index }
        {}

        reference operator*() const
        {
            return m_i;
        }

        pointer operator->() const
        {
            return std::addressof(m_i);
        }

        reference operator[](difference_type _offset) const
        {
            return m_i + _offset;
        }

        IndexIterator& operator++()
        {
            ++m_i;
            return *this;
        }

        IndexIterator operator++(int)
        {
            return { m_i++ };
        }

        IndexIterator& operator+=(difference_type _offset)
        {
            m_i += _offset;
            return *this;
        }

        IndexIterator operator+(difference_type _offset) const
        {
            return { m_i + _offset };
        }

        friend IndexIterator operator+(difference_type _offset, const IndexIterator& _iterator)
        {
            return { _iterator.m_i + _offset };
        }

        IndexIterator& operator--()
        {
            --m_i;
            return *this;
        }

        IndexIterator operator--(int)
        {
            return { m_i-- };
        }

        IndexIterator& operator-=(difference_type _offset)
        {
            m_i -= _offset;
            return *this;
        }

        IndexIterator operator-(difference_type _offset) const
        {
            return { m_i - _offset };
        }

        friend IndexIterator operator-(difference_type _offset, const IndexIterator& _iterator)
        {
            return { _iterator.m_i - _offset };
        }

        bool operator==(const IndexIterator& _other) const
        {
            return m_i == _other.m_i;
        }

        bool operator< (const IndexIterator& _other) const
        {
            return m_i < _other.m_i;
        }

        bool operator> (const IndexIterator& _other) const
        {
            return m_i > _other.m_i;
        }

        bool operator<= (const IndexIterator& _other) const
        {
            return m_i <= _other.m_i;
        }

        bool operator>= (const IndexIterator& _other) const
        {
            return m_i >= _other.m_i;
        }

        difference_type operator-(const IndexIterator& _other) const
        {
            return m_i - _other.m_i;
        }

    };

}