#pragma once

#include <iterator>
#include <concepts>

namespace cpputils::iterators
{

    template<std::integral TIndex = std::size_t>
    class StandaloneIndexIterator final
    {

    private:

        std::ptrdiff_t m_i;

    public:

        using value_type = TIndex;
        using reference = TIndex;
        using pointer = const std::ptrdiff_t*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        StandaloneIndexIterator(const TIndex& _index = {})
            : m_i{ static_cast<std::ptrdiff_t>(_index) }
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