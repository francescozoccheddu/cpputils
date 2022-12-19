#pragma once

#include <iterator>

namespace cpputils::iterators
{

    template<typename TIndex = std::size_t>
    class StandaloneIndexIterator final
    {

    private:

        TIndex m_i;

    public:

        using value_type = TIndex;
        using reference = TIndex;
        using pointer = const TIndex*;
        using difference_type = TIndex;
        using iterator_category = std::random_access_iterator_tag;

        StandaloneIndexIterator(const TIndex& _index = {})
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

        StandaloneIndexIterator& operator++()
        {
            ++m_i;
            return *this;
        }

        StandaloneIndexIterator operator++(int)
        {
            return { m_i++ };
        }

        StandaloneIndexIterator& operator+=(difference_type _offset)
        {
            m_i += _offset;
            return *this;
        }

        StandaloneIndexIterator operator+(difference_type _offset) const
        {
            return { m_i + _offset };
        }

        friend StandaloneIndexIterator operator+(difference_type _offset, const StandaloneIndexIterator& _iterator)
        {
            return { _iterator.m_i + _offset };
        }

        StandaloneIndexIterator& operator--()
        {
            --m_i;
            return *this;
        }

        StandaloneIndexIterator operator--(int)
        {
            return { m_i-- };
        }

        StandaloneIndexIterator& operator-=(difference_type _offset)
        {
            m_i -= _offset;
            return *this;
        }

        StandaloneIndexIterator operator-(difference_type _offset) const
        {
            return { m_i - _offset };
        }

        friend StandaloneIndexIterator operator-(difference_type _offset, const StandaloneIndexIterator& _iterator)
        {
            return { _iterator.m_i - _offset };
        }

        bool operator==(const StandaloneIndexIterator& _other) const
        {
            return m_i == _other.m_i;
        }

        bool operator< (const StandaloneIndexIterator& _other) const
        {
            return m_i < _other.m_i;
        }

        bool operator> (const StandaloneIndexIterator& _other) const
        {
            return m_i > _other.m_i;
        }

        bool operator<= (const StandaloneIndexIterator& _other) const
        {
            return m_i <= _other.m_i;
        }

        bool operator>= (const StandaloneIndexIterator& _other) const
        {
            return m_i >= _other.m_i;
        }

        difference_type operator-(const StandaloneIndexIterator& _other) const
        {
            return m_i - _other.m_i;
        }

    };

}