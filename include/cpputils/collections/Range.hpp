#pragma once

#include <type_traits>
#include <iterator>
#include <vector>
#include <list>
#include <array>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <memory>
#include <algorithm>
#include <limits>
#include <utility>
#include <variant>

namespace cpputils::collections
{

    class Buffer final
    {

    private:

        std::unique_ptr<char[]> m_data{};
        std::size_t m_capacity{};
        std::size_t m_size{};

    public:

        template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
        void collect(const TIterator& _begin, const TIterator& _end)
        {
            const std::size_t size{ static_cast<std::size_t>(std::distance(_begin, _end)) };
            const std::size_t capacity{ size * sizeof(TValue) };
            if (capacity > m_capacity)
            {
                m_capacity = capacity;
                m_data = std::make_unique<char[]>(capacity);
            }
            m_size = size;
            if constexpr (std::is_pointer_v<TIterator>)
            {
                if (reinterpret_cast<const char*>(_begin) == m_data.get())
                {
                    return;
                }
            }
            TValue* outIt{ reinterpret_cast<TValue*>(m_data.get()) };
            TIterator inIt{ _begin };
            while (inIt != _end)
            {
                *(outIt++) = static_cast<TValue>(*(inIt++));
            }
        }

        template<typename TValue>
        inline TValue* begin() const noexcept
        {
            return reinterpret_cast<TValue*>(m_data.get());
        }

        template<typename TValue>
        inline TValue* end() const noexcept
        {
            return begin<TValue>() + m_size;
        }

    };

    template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
    class RangeData final
    {

    private:

        Buffer m_buffer;
        TIterator m_begin, m_end;

    public:

        RangeData(const TIterator& _begin, const TIterator& _end, Buffer&& _buffer)
            : m_buffer{ std::move(_buffer) }, m_begin{ _begin }, m_end{ _end }
        {}

        RangeData(const TIterator& _begin, const TIterator& _end)
            : m_buffer{}, m_begin{ _begin }, m_end{ _end }
        {}

        inline const TIterator& begin() const noexcept
        {
            return m_begin;
        }

        inline const TIterator& end() const noexcept
        {
            return m_end;
        }

        inline Buffer&& extractBuffer() noexcept
        {
            return std::move(m_buffer);
        }

    };

    template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
    class Iterator
    {

    private:

        std::shared_ptr<RangeData<TIterator, TValue>> m_rangeData;

    public:

        using value_type = TValue;
        using reference = TValue&;
        using pointer = TValue*;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = std::conditional_t<std::bidirectional_iterator<TIterator>, std::bidirectional_iterator_tag, std::forward_iterator_tag>;

    protected:

        Iterator(const std::shared_ptr<RangeData<TIterator, TValue>>& _rangeData): m_rangeData{ _rangeData } {}

        const TIterator& begin() const
        {
            return m_rangeData->begin();
        }

        const TIterator& end() const
        {
            return m_rangeData->end();
        }

    };

    template<typename TIterator, typename TValue>
    class FilterIterator final: public Iterator<TIterator, TValue>
    {

    private:

        using Base = Iterator<TIterator, TValue>;

        TIterator m_it;


        void advance()
        {
            while (m_it != this->end() && !*m_it)
            {
                ++m_it;
            }
        }

        void advanceReverse()
        {
            while (m_it != this->begin() && !*m_it)
            {
                --m_it;
            }
        }

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        FilterIterator(const TIterator& _it, const std::shared_ptr<RangeData<TIterator, TValue>>& _rangeData)
            : Base{ _rangeData }, m_it{ _it }
        {
            advance();
        }

        reference operator*() const
        {
            return *m_it;
        }

        pointer operator->() const
        {
            return m_it.operator->();
        }

        reference operator[](difference_type _offset) const
        {
            return *((*this) + _offset);
        }

        FilterIterator& operator++()
        {
            if (m_it != this->end())
            {
                ++m_it;
            }
            advance();
            return *this;
        }

        FilterIterator operator++(int) const
        {
            FilterIterator clone{ *this };
            ++clone;
            return clone;
        }

        FilterIterator& operator+=(difference_type _offset)
        {
            while (m_it != this->end() && _offset != 0)
            {
                ++m_it;
                advance();
                --_offset;
            }
            return *this;
        }

        FilterIterator operator+(difference_type _offset) const
        {
            FilterIterator clone{ *this };
            clone += _offset;
            return clone;
        }

        FilterIterator& operator--()
        {
            if (m_it != this->begin())
            {
                --m_it;
            }
            advanceReverse();
            return *this;
        }

        FilterIterator operator--(int) const
        {
            FilterIterator clone{ *this };
            --clone;
            return clone;
        }

        FilterIterator& operator-=(difference_type _offset)
        {
            while (m_it != this->begin() && _offset != 0)
            {
                --m_it;
                advanceReverse();
                --_offset;
            }
            return *this;
        }

        FilterIterator operator-(difference_type _offset) const
        {
            FilterIterator clone{ *this };
            clone -= _offset;
            return clone;
        }

        bool operator==(const FilterIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        difference_type operator-(const FilterIterator& _other) const
        {
            difference_type count{};
            TIterator it{ _other.m_it };
            while (it != m_it && !*it)
            {
                ++it;
                --count;
            }
            return count;
        }

    };

    template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
    class Range final
    {

    private:

        template<typename TOtherIterator, typename TOtherValue>
        friend class Range;

        using Data = RangeData<TIterator, TValue>;
        using Collected = Range<TValue*, TValue>;
        using Filter = FilterIterator<TIterator, TValue>;
        using Filtered = Range<Filter>;

        std::shared_ptr<Data> m_data;

        Range(const TIterator& _begin, const TIterator& _end, Buffer&& _buffer)
            : m_data{ std::make_shared<Data>(_begin, _end, std::move(_buffer)) }
        {}

    public:

        Range(const TIterator& _begin, const TIterator& _end)
            : m_data{ std::make_shared<Data>(_begin, _end) }
        {}

        TIterator begin() const
        {
            return m_data->begin();
        }

        TIterator end() const
        {
            return m_data->end();
        }

        auto operator[](const std::iter_difference_t<TIterator>& _offset) const
        {
            return *std::next(begin(), _offset);
        }

        const TValue& first() const
        {
            return *begin();
        }

        const TValue& last() const
        {
            if constexpr (std::bidirectional_iterator<TIterator>)
            {
                return *(std::prev(end()));
            }
            else
            {
                return (*this)[count() - 1];
            }
        }

        std::iterator_traits<TIterator>::difference_type count() const
        {
            return static_cast<std::size_t>(std::distance(begin(), end()));
        }

        Filtered filter()
        {
            return Filtered{ Filter{ begin(), m_data }, Filter{ end(), m_data }, m_data->extractBuffer() };
        }

        Collected collect()
        {
            Buffer buffer{ m_data->extractBuffer() };
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<TValue>(), buffer.end<TValue>(), std::move(buffer) };
        }

        Collected cloneAndCollect() const
        {
            Buffer buffer{};
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<TValue>(), buffer.end<TValue>(), std::move(buffer) };
        }

        Collected sort();

        Collected distinct();

        Collected duplicated();

        std::vector<TValue> toVector() const;

        template<std::size_t TSize>
        std::array<TValue, TSize> toArray() const;

        std::list<TValue> toList() const;

        std::unordered_set<TValue> toUnorderedSet() const;

        std::set<TValue> toSet() const;

        template<typename TOutIterator>
        void assign(const TOutIterator& _begin) const
        {
            TOutIterator it{ _begin };
            for (TValue& value : *this)
            {
                *(it++) = value;
            }
        }

        template<typename TOutIterator>
        TOutIterator assign(const TOutIterator& _begin, const TOutIterator& _end) const
        {
            TOutIterator outIt{ _begin };
            TIterator inIt{ begin() };
            while (inIt != end() && outIt != _end)
            {
                *(outIt++) = *(inIt++);
            }
            return outIt;
        }

        template<typename TOutIterator>
        void assign(const TOutIterator& _begin, const TOutIterator& _end, const TValue& _defaultValue) const
        {
            TOutIterator outIt{ assign(_begin, _end) };
            while (outIt != _end)
            {
                *(outIt++) = _defaultValue;
            }
        }

    };

}