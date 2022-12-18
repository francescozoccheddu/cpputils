#pragma once

#include <array>
#include <iterator>
#include <initializer_list>
#include <utility>

namespace cpputils::collections
{

    template<typename TValue, std::size_t TCapacity>
    class FixedVector final
    {

    private:

        std::array<TValue, TCapacity> m_data;
        std::size_t m_size;

    public:

        using value_type = TValue;
        using pointer = TValue*;
        using const_pointer = const TValue*;
        using reference = TValue&;
        using const_reference = const TValue&;
        using iterator = TValue*;
        using const_iterator = const TValue*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        FixedVector(): m_size{}
        {}

        FixedVector(std::size_t _size, const TValue& _defaultValue = {}): m_size{}
        {
            resize(_size, _defaultValue);
        }

        FixedVector(std::initializer_list<TValue> _values)
        {
            assign(_values.begin(), _values.end());
        }

        template<typename TIterator>
        FixedVector(const TIterator& _begin, const TIterator& _end)
        {
            assign(_begin, _end);
        }

        static constexpr std::size_t capacity()
        {
            return TCapacity;
        }

        std::size_t size() const
        {
            return m_size;
        }

        bool empty() const
        {
            return m_size == 0;
        }

        void resize(std::size_t _size, const TValue& _defaultValue = {})
        {
            while (_size > m_size)
            {
                m_data[m_size++] = _defaultValue;
            }
        }

        TValue& operator[](std::size_t _index)
        {
            return m_data[_index];
        }

        const TValue& operator[](std::size_t _index) const
        {
            return m_data[_index];
        }

        TValue& first()
        {
            return m_data[0];
        }

        const TValue& first() const
        {
            return m_data[0];
        }

        TValue& last()
        {
            return m_data[m_size - 1];
        }

        const TValue& last() const
        {
            return m_data[m_size - 1];
        }

        void addLast(const TValue& _value)
        {
            m_data[m_size++] = _value;
        }

        TValue&& removeLast()
        {
            --m_size;
            return std::move(m_data[m_size]);
        }

        void clear()
        {
            m_size = 0;
        }

        template<typename TIterator>
        void assign(const TIterator& _begin, const TIterator& _end)
        {
            clear();
            TIterator it{ _begin };
            while (it != _end)
            {
                addLast(*(it++));
            }
        }

        inline iterator begin() noexcept
        {
            return &m_data[0];
        }

        inline iterator end() noexcept
        {
            return begin() + m_size;
        }

        inline const_iterator begin() const noexcept
        {
            return cbegin();
        }

        inline const_iterator end() const noexcept
        {
            return cend();
        }

        inline const_iterator cbegin() const noexcept
        {
            return &m_data[0];
        }

        inline const_iterator cend() const noexcept
        {
            return cbegin() + m_size;
        }

        inline reverse_iterator rbegin() noexcept
        {
            return std::reverse_iterator(end());
        }

        inline reverse_iterator rend() noexcept
        {
            return std::reverse_iterator(begin());
        }

        inline const_reverse_iterator rbegin() const noexcept
        {
            return std::reverse_iterator(cend());
        }

        inline const_reverse_iterator rend() const noexcept
        {
            return std::reverse_iterator(cbegin());
        }

        inline const_reverse_iterator crbegin() const noexcept
        {
            return std::reverse_iterator(cend());
        }

        inline const_reverse_iterator crend() const noexcept
        {
            return std::reverse_iterator(cbegin());
        }

    };

}