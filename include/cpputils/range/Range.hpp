#pragma once

#include <cpputils/range/internal/Buffer.hpp>
#include <cpputils/range/internal/Data.hpp>
#include <cpputils/range/iterators/DistinctIterator.hpp>
#include <cpputils/range/iterators/DuplicatedIterator.hpp>
#include <cpputils/range/iterators/FilterIterator.hpp>
#include <type_traits>
#include <iterator>
#include <vector>
#include <list>
#include <array>
#include <unordered_set>
#include <set>
#include <memory>
#include <algorithm>
#include <limits>
#include <utility>

namespace cpputils::range
{

    template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
    class Range final
    {

    private:

        template<typename TOtherIterator, typename TOtherValue>
        friend class Range;

        using Iterator = TIterator;
        using Value = TValue;
        using Data = internal::Data<TIterator, TValue>;
        using Collected = Range<TValue*, TValue>;
        using FilterIt = iterators::FilterIterator<TIterator, TValue>;
        using Filtered = Range<FilterIt>;
        using DistinctIt = iterators::DistinctIterator<typename Collected::Iterator, typename Collected::Value>;
        using Distinct = Range<DistinctIt>;
        using DuplicatedIt = iterators::DuplicatedIterator<typename Collected::Iterator, typename Collected::Value>;
        using Duplicated = Range<DuplicatedIt>;

        std::shared_ptr<Data> m_data;

        Range(const TIterator& _begin, const TIterator& _end, internal::Buffer&& _buffer)
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
            return Filtered{ FilterIt{ begin(), m_data }, FilterIt{ end(), m_data }, m_data->extractBuffer() };
        }

        Collected collect()
        {
            internal::Buffer buffer{ m_data->extractBuffer() };
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<TValue>(), buffer.end<TValue>(), std::move(buffer) };
        }

        Collected cloneAndCollect() const
        {
            internal::Buffer buffer{};
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<TValue>(), buffer.end<TValue>(), std::move(buffer) };
        }

        Collected sort()
        {
            internal::Buffer buffer{ m_data->extractBuffer() };
            buffer.collect(begin(), end());
            std::sort(buffer.begin<TValue>(), buffer.end<TValue>());
            return Collected{ buffer.begin<TValue>(), buffer.end<TValue>(), std::move(buffer) };
        }

        Distinct distinct()
        {
            Collected sorted{ sort() };
            return Distinct{ DistinctIt{ sorted.begin(), sorted.m_data }, DistinctIt{ sorted.end(), sorted.m_data }, sorted.m_data->extractBuffer() };
        }

        Duplicated duplicated()
        {
            Collected sorted{ sort() };
            return Duplicated{ DuplicatedIt{ sorted.begin(), sorted.m_data }, DuplicatedIt{ sorted.end(), sorted.m_data }, sorted.m_data->extractBuffer() };
        }

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