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

        std::iter_reference_t<const TIterator> first(std::iter_reference_t<const TIterator> _else) const
        {
            return empty() ? _else : first();
        }

        std::iter_reference_t<const TIterator> last(std::iter_reference_t<const TIterator> _else) const
        {
            return empty() ? _else : last();
        }

        std::iter_reference_t<const TIterator> single(std::iter_reference_t<const TIterator> _else) const
        {
            return count() != 1 ? _else : single();
        }

        std::iter_reference_t<const TIterator> first() const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            return *begin();
        }

        std::iter_reference_t<const TIterator> last() const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            if constexpr (std::bidirectional_iterator<const TIterator>)
            {
                return *(std::prev(end()));
            }
            else
            {
                return (*this)[count() - 1];
            }
        }

        std::iter_reference_t<const TIterator> single() const
        {
            if (count() != 1)
            {
                throw std::logic_error{ "not a singleton" };
            }
            return first();
        }

        std::iter_difference_t<const TIterator> count() const
        {
            return std::distance(begin(), end());
        }

        bool empty() const
        {
            return begin() == end();
        }

        Filtered filter()
        {
            std::shared_ptr<Data> data{ std::move(m_data) };
            return Filtered{ FilterIt{ data->begin(), data }, FilterIt{ data->end(), data }, data->extractBuffer() };
        }

        Collected collect()
        {
            std::shared_ptr<Data> data{ std::move(m_data) };
            internal::Buffer buffer{ data->extractBuffer() };
            buffer.collect(data->begin(), data->end());
            return Collected{ buffer.begin<Value>(), buffer.end<Value>(), std::move(buffer) };
        }

        Collected clone() const
        {
            internal::Buffer buffer{};
            buffer.collect(begin(), end());
            return Collected{ buffer.begin<Value>(), buffer.end<Value>(), std::move(buffer) };
        }

        template<typename TCompare>
        Collected sort()
        {
            std::shared_ptr<Data> data{ std::move(m_data) };
            internal::Buffer buffer{ data->extractBuffer() };
            buffer.collect(data->begin(), data->end());
            std::sort(buffer.begin<Value>(), buffer.end<Value>());
            return Collected{ buffer.begin<Value>(), buffer.end<Value>(), std::move(buffer) };
        }

        Distinct distinct()
        {
            Collected sorted{ sort() };
            std::shared_ptr<Data> data{ std::move(sorted.m_data) };
            return Distinct{ DistinctIt{ data->begin(), data }, DistinctIt{ data->end(), data }, data->extractBuffer() };
        }

        Duplicated duplicated()
        {
            Collected sorted{ sort() };
            std::shared_ptr<Data> data{ std::move(sorted.m_data) };
            return Duplicated{ DuplicatedIt{ data->begin(), data }, DuplicatedIt{ data->end(), data }, data->extractBuffer() };
        }

        template<typename TAccumulator, typename TReduce>
        TAccumulator reduce(const TReduce& _reduce, const TAccumulator& _start) const
        {
            TAccumulator accumulator{ _start };
            for (auto& value : *this)
            {
                accumulator = _reduce(value, accumulator);
            }
            return accumulator;
        }

        template<typename TCompare>
        std::iter_reference_t<const TIterator> best(const TCompare& _compare, std::iter_reference_t<const TIterator> _else) const
        {
            return empty() ? _else : best(_compare);
        }

        template<typename TCompare>
        TIterator best(const TCompare& _compare) const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            return *bestIt(_compare);
        }

        template<typename TCompare>
        TIterator bestIt(const TCompare& _compare) const
        {
            TIterator best{ begin() };
            TIterator it{ begin() };
            while (it != end())
            {
                if (_compare(*it, *best))
                {
                    best = it;
                }
                it++;
            }
            return best;
        }

        std::iter_reference_t<const TIterator> min(std::iter_reference_t<const TIterator> _else) const
        {
            return empty() ? _else : min();
        }

        std::iter_reference_t<const TIterator> max(std::iter_reference_t<const TIterator> _else) const
        {
            return empty() ? _else : max();
        }

        std::iter_reference_t<const TIterator> min() const
        {
            return best(std::less<std::iter_value_t<const TIterator>>{});
        }

        std::iter_reference_t<const TIterator> max() const
        {
            return best(std::greater<std::iter_value_t<const TIterator>>{});
        }

        template<typename TSum = std::iter_value_t<const TIterator>>
        TSum sum() const
        {
            return reduce([](std::iter_reference_t<const TIterator> _value, TSum _accumulator) {
                return static_cast<TSum>(_value) + _accumulator;
            }, TSum{});
        }

        template<typename TSum = std::iter_value_t<const TIterator>>
        TSum avg(TSum _else) const
        {
            return empty() ? _else : avg();
        }

        template<typename TSum = std::iter_value_t<const TIterator>>
        TSum avg() const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            return sum<TSum>() / static_cast<TSum>(count());
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
            for (auto& value : *this)
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