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

        reference operator*() const noexcept
        {
            return m_i;
        }

        pointer operator->() const noexcept
        {
            return std::addressof(m_i);
        }

        reference operator[](difference_type _offset) const noexcept
        {
            return m_i + _offset;
        }

        StandaloneIndexIterator& operator++() noexcept
        {
            ++m_i;
            return *this;
        }

        StandaloneIndexIterator operator++(int) noexcept
        {
            return { m_i++ };
        }

        StandaloneIndexIterator& operator+=(difference_type _offset) noexcept
        {
            m_i += _offset;
            return *this;
        }

        StandaloneIndexIterator operator+(difference_type _offset) const noexcept
        {
            return { m_i + _offset };
        }

        friend StandaloneIndexIterator operator+(difference_type _offset, const StandaloneIndexIterator& _iterator) noexcept
        {
            return { _iterator.m_i + _offset };
        }

        StandaloneIndexIterator& operator--() noexcept
        {
            --m_i;
            return *this;
        }

        StandaloneIndexIterator operator--(int) noexcept
        {
            return { m_i-- };
        }

        StandaloneIndexIterator& operator-=(difference_type _offset) noexcept
        {
            m_i -= _offset;
            return *this;
        }

        StandaloneIndexIterator operator-(difference_type _offset) const noexcept
        {
            return { m_i - _offset };
        }

        friend StandaloneIndexIterator operator-(difference_type _offset, const StandaloneIndexIterator& _iterator) noexcept
        {
            return { _iterator.m_i - _offset };
        }

        bool operator==(const StandaloneIndexIterator& _other) const noexcept = default;

        auto operator<=>(const StandaloneIndexIterator& _other) const noexcept = default;

        difference_type operator-(const StandaloneIndexIterator& _other) const noexcept
        {
            return m_i - _other.m_i;
        }

    };

}