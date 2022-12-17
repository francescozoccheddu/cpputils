#pragma once

#include <cpputils/range/internal/Buffer.hpp>
#include <cpputils/range/internal/Data.hpp>
#include <cpputils/range/iterators/DistinctIterator.hpp>
#include <cpputils/range/iterators/DuplicatedIterator.hpp>
#include <cpputils/range/iterators/FilterIterator.hpp>
#include <cpputils/mixins/NonCopyable.hpp>
#include <type_traits>
#include <iterator>
#include <vector>
#include <list>
#include <array>
#include <unordered_set>
#include <memory>
#include <algorithm>
#include <limits>
#include <utility>

namespace cpputils::range
{

    template<typename TIterator>
    class Range final: private mixins::NonCopyable
    {

    private:

        template<typename TOtherIterator>
        friend class Range;

        using Iterator = TIterator;
        using Value = std::remove_reference_t<std::iter_reference_t<const TIterator>>;
        using Data = internal::Data<TIterator>;
        using Collected = Range<Value*>;
        using FilterIt = iterators::FilterIterator<TIterator>;
        using Filtered = Range<FilterIt>;
        using DistinctIt = iterators::DistinctIterator<typename Collected::Iterator>;
        using Distinct = Range<DistinctIt>;
        using DuplicatedIt = iterators::DuplicatedIterator<typename Collected::Iterator>;
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

        std::iter_reference_t<const TIterator> operator[](const std::iter_difference_t<const TIterator>& _offset) const
        {
            return *std::next(begin(), _offset);
        }

        std::iter_reference_t<const TIterator> first() const
        {
            return *begin();
        }

        std::iter_reference_t<const TIterator> last() const
        {
            if constexpr (std::bidirectional_iterator<const TIterator>)
            {
                return *(std::prev(end()));
            }
            else
            {
                return (*this)[count() - 1];
            }
        }

        std::iter_difference_t<const TIterator> count() const
        {
            return std::distance(begin(), end());
        }

        Filtered filter()
        {
            return Filtered{ FilterIt{ begin(), m_data }, FilterIt{ end(), m_data }, m_data->extractBuffer() };
        }

        Collected collect()
        {
            internal::Buffer buffer{ m_data->extractBuffer() };
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<Value>(), buffer.end<Value>(), std::move(buffer) };
        }

        Collected cloneAndCollect() const
        {
            internal::Buffer buffer{};
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<Value>(), buffer.end<Value>(), std::move(buffer) };
        }

        Collected sort()
        {
            internal::Buffer buffer{ m_data->extractBuffer() };
            buffer.collect(begin(), end());
            std::sort(buffer.begin<Value>(), buffer.end<Value>());
            return Collected{ buffer.begin<Value>(), buffer.end<Value>(), std::move(buffer) };
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

        std::vector<Value> toVector() const
        {
            return std::vector<Value>(begin(), end());
        }

        template<std::size_t TSize>
        std::array<Value, TSize> toArray(const Value& _defaultValue = {}) const
        {
            std::array<Value, TSize> out;
            std::size_t i{};
            TIterator it{ begin() };
            while (i < TSize && it != end())
            {
                out[i++] = *(it++);
            }
            while (i < TSize)
            {
                out[i++] = _defaultValue;
            }
            return out;
        }

        std::list<Value> toList() const
        {
            return std::list<Value>(begin(), end());
        }

        std::unordered_set<Value> toUnorderedSet() const
        {
            return std::unordered_set<Value>(begin(), end());
        }

        template<typename TOutIterator>
        void assign(const TOutIterator& _begin) const
        {
            TOutIterator it{ _begin };
            for (const Value& value : *this)
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
        void assign(const TOutIterator& _begin, const TOutIterator& _end, const Value& _defaultValue) const
        {
            TOutIterator outIt{ assign(_begin, _end) };
            while (outIt != _end)
            {
                *(outIt++) = _defaultValue;
            }
        }

    };

}