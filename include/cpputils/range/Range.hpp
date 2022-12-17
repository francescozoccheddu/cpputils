#pragma once

#include <cpputils/range/internal/Buffer.hpp>
#include <cpputils/range/internal/Data.hpp>
#include <cpputils/range/internal/consts.hpp>
#include <cpputils/range/iterators/DistinctIterator.hpp>
#include <cpputils/range/iterators/DuplicatedIterator.hpp>
#include <cpputils/range/iterators/FilterIterator.hpp>
#include <cpputils/range/iterators/MapIterator.hpp>
#include <cpputils/range/iterators/ReverseIterator.hpp>
#include <cpputils/range/iterators/IndexIterator.hpp>
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

    namespace internal
    {

        template<typename TInReference, typename TOutReference>
        struct Caster final
        {

            inline TOutReference operator()(TInReference _value) const noexcept
            {
                return static_cast<TOutReference>(_value);
            };

        };

        template<typename TInReference>
        struct Addresser final
        {

            inline std::remove_reference_t<TInReference>* operator()(TInReference _value) const noexcept
            {
                return std::addressof(_value);
            };

        };

        template<typename TInReference>
        struct Dereferencer final
        {

            inline std::remove_pointer_t<std::remove_reference_t<TInReference>> operator()(TInReference _value) const noexcept
            {
                return *_value;
            };

        };

    }

    template<typename TIterator>
    class Range final: private mixins::NonCopyable
    {

    public:

        using Iterator = TIterator;
        using Value = std::iter_value_t<const Iterator>;
        using Reference = std::iter_reference_t<const Iterator>;
        using Offset = std::iter_difference_t<const Iterator>;
        using Data = internal::Data<Iterator>;
        using Collected = Range<const Value*>;
        using Filtered = Range<iterators::FilterIterator<Iterator>>;
        using Distinct = Range<iterators::DistinctIterator<typename Collected::Iterator>>;
        using Duplicated = Range<iterators::DuplicatedIterator<typename Collected::Iterator>>;
        template<typename TMapper>
        using Mapped = Range<iterators::MapIterator<TIterator, TMapper>>;
        template<typename TOutReference>
        using Casted = Mapped<internal::Caster<Reference, TOutReference>>;
        using Const = Casted<internal::consts::RefOrPtr<Reference>>;
        using Addressed = Mapped<internal::Addresser<Reference>>;
        using Dereferenced = Mapped<internal::Dereferencer<Reference>>;
        using Reversed = Range<iterators::ReverseIterator<Iterator>>;
        template<typename TIndex>
        using Index = Range<iterators::IndexIterator<TIndex>>;

    private:

        template<typename TOtherIterator>
        friend class Range;

        std::shared_ptr<Data> m_data;

        Range(const Iterator& _begin, const Iterator& _end, internal::Buffer&& _buffer)
            : m_data{ std::make_shared<Data>(_begin, _end, std::move(_buffer)) }
        {}

    public:

        Range(const Iterator& _begin, const Iterator& _end)
            : m_data{ std::make_shared<Data>(_begin, _end) }
        {}

        Iterator begin() const
        {
            return m_data->begin();
        }

        Iterator end() const
        {
            return m_data->end();
        }

        Reference operator[](const Offset& _offset) const
        {
            return *std::next(begin(), _offset);
        }

        Reference first(Reference _else) const
        {
            return empty() ? _else : first();
        }

        Reference last(Reference _else) const
        {
            return empty() ? _else : last();
        }

        Reference single(Reference _else) const
        {
            return size() != 1 ? _else : single();
        }

        Reference first() const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            return *begin();
        }

        Reference last() const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            if constexpr (std::bidirectional_iterator<const Iterator>)
            {
                return *(std::prev(end()));
            }
            else
            {
                return (*this)[size() - 1];
            }
        }

        Reference single() const
        {
            if (size() != 1)
            {
                throw std::logic_error{ "not a singleton" };
            }
            return first();
        }

        Offset size() const
        {
            return std::distance(begin(), end());
        }

        bool empty() const
        {
            return begin() == end();
        }

        template<typename TIndex = Offset>
        Index<TIndex> index() const
        {
            return Index<TIndex>{ { TIndex{} }, { TIndex{ size() } } };
        }

        Range take(Offset _size)
        {
            const Offset maxSize{ size() };
            std::shared_ptr<Data> data{ std::move(m_data) };
            return Range{ data->begin(), std::next(data->begin(),std::min(_size, maxSize)), data->extractBuffer() };
        }

        Range skip(Offset _size)
        {
            const Offset maxSize{ size() };
            std::shared_ptr<Data> data{ std::move(m_data) };
            return Range{ std::next(data->begin(), std::min(_size, maxSize)), data->end(), data->extractBuffer() };
        }

        Filtered filter()
        {
            std::shared_ptr<Data> data{ std::move(m_data) };
            return Filtered{ { data->begin(), data }, { data->end(), data }, data->extractBuffer() };
        }

        Reversed reverse()
        {
            std::shared_ptr<Data> data{ std::move(m_data) };
            return Reversed{ { std::prev(data->end()), data }, { std::prev(data->begin()), data }, data->extractBuffer() };
        }

        template<typename TMapper>
        Mapped<TMapper> map(const TMapper& _mapper = {})
        {
            std::shared_ptr<Data> data{ std::move(m_data) };
            return Mapped<TMapper>{ { data->begin(), data, _mapper }, { data->end(), data, _mapper }, data->extractBuffer() };
        }

        template<typename TOutReference>
        Casted<TOutReference> cast()
        {
            return map(internal::Caster<Reference, TOutReference>{});
        }

        Addressed address()
        {
            return map(internal::Addresser<Reference>{});
        }

        Dereferenced dereference()
        {
            return map(internal::Dereferencer<Reference>{});
        }

        Const immutable()
        {
            return cast<internal::consts::RefOrPtr<Reference>>();
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

        Collected sort()
        {
            Collected collected{ collect() };
            std::shared_ptr<typename Collected::Data> data{ std::move(collected.m_data) };
            internal::Buffer buffer{ data->extractBuffer() };
            std::sort(buffer.begin<Value>(), buffer.end<Value>());
            return Collected{ buffer.begin<const Value>(), buffer.end<const Value>(), std::move(buffer) };
        }

        Distinct distinct()
        {
            Collected sorted{ sort() };
            std::shared_ptr<typename Collected::Data> data{ std::move(sorted.m_data) };
            return Distinct{ { data->begin(), data }, { data->end(), data }, data->extractBuffer() };
        }

        Duplicated duplicated()
        {
            Collected sorted{ sort() };
            std::shared_ptr<typename Collected::Data> data{ std::move(sorted.m_data) };
            return Duplicated{ { data->begin(), data }, { data->end(), data }, data->extractBuffer() };
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
        Reference best(const TCompare& _compare, Reference _else) const
        {
            return empty() ? _else : best(_compare);
        }

        template<typename TCompare>
        Reference best(const TCompare& _compare) const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            return *bestIt(_compare);
        }

        template<typename TCompare>
        Iterator bestIt(const TCompare& _compare) const
        {
            Iterator best{ begin() };
            Iterator it{ begin() };
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

        Reference min(Reference _else) const
        {
            return empty() ? _else : min();
        }

        Reference max(Reference _else) const
        {
            return empty() ? _else : max();
        }

        Reference min() const
        {
            return best(std::less<Value>{});
        }

        Reference max() const
        {
            return best(std::greater<Value>{});
        }

        template<typename TSum = Value>
        TSum sum() const
        {
            return reduce([](Reference _value, TSum _accumulator) {
                return static_cast<TSum>(_value) + _accumulator;
            }, TSum{});
        }

        template<typename TSum = Value>
        TSum avg(TSum _else) const
        {
            return empty() ? _else : avg();
        }

        template<typename TSum = Value>
        TSum avg() const
        {
            if (empty())
            {
                throw std::logic_error{ "empty" };
            }
            return sum<TSum>() / static_cast<TSum>(size());
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
            Iterator it{ begin() };
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
            Iterator inIt{ begin() };
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