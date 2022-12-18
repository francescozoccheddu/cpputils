#pragma once

#include <iterator>

namespace cpputils::iterators
{

    template<std::input_iterator TIterator, std::invocable<const std::iter_reference_t<TIterator>> TMapper>
    class MapIterator final
    {

    private:

        TIterator m_it;
        TMapper m_mapper;

    public:

        using value_type = std::invoke_result_t<TMapper, const std::iter_reference_t<TIterator>>;
        using reference = value_type;
        using pointer = value_type;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = typename std::template iterator_traits<TIterator>::iterator_category;

        MapIterator(const TMapper& _mapper = {})
            : m_mapper{ _mapper }
        {}

        MapIterator(const TIterator& _it, const TMapper& _mapper = {})
            : m_it{ _it }, m_mapper{ _mapper }
        {}

        const TMapper& mapper() const
        {
            return m_mapper;
        }

        reference operator*() const
        {
            return m_mapper(*m_it);
        }

        pointer operator->() const
        {
            if constexpr (requires{ m_it.operator->(); })
            {
                return m_mapper(*(m_it.operator->()));
            }
            return m_mapper(*m_it);
        }

        reference operator[](difference_type _offset) const
        {
            return m_mapper(m_it[_offset]);
        }

        MapIterator& operator++()
        {
            ++m_it;
            return *this;
        }

        MapIterator operator++(int)
        {
            return { m_it++, m_mapper };
        }

        MapIterator& operator+=(difference_type _offset)
        {
            m_it += _offset;
            return *this;
        }

        MapIterator operator+(difference_type _offset) const
        {
            return { m_it + _offset, m_mapper };
        }

        friend MapIterator operator+(difference_type _offset, const MapIterator& _iterator)
        {
            return { _iterator.m_it + _offset, _iterator.m_mapper };
        }

        MapIterator& operator--()
        {
            --m_it;
            return *this;
        }

        MapIterator operator--(int)
        {
            return { m_it--, m_mapper };
        }

        MapIterator& operator-=(difference_type _offset)
        {
            m_it -= _offset;
            return *this;
        }

        MapIterator operator-(difference_type _offset) const
        {
            return { m_it - _offset, m_mapper };
        }

        friend MapIterator operator-(difference_type _offset, const MapIterator& _iterator)
        {
            return { _iterator.m_it - _offset, _iterator.m_mapper };
        }

        bool operator==(const MapIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        auto operator<=>(const MapIterator& _other) const
        {
            return m_it <=> _other.m_it;
        }

        difference_type operator-(const MapIterator& _other) const
        {
            return m_it - _other.m_it;
        }

    };

}