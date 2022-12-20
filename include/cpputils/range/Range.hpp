#pragma once 

#include <iterator>
#include <type_traits>
#include <cstddef>
#include <utility>
#include <optional>
#include <stdexcept>
#include <vector>
#include <list>
#include <array>
#include <unordered_set>
#include <algorithm>
#include <cpputils/collections/FixedVector.hpp>
#include <cpputils/iterators/FilterIterator.hpp>
#include <cpputils/iterators/MapIterator.hpp>
#include <cpputils/iterators/ZipIterator.hpp>
#include <cpputils/iterators/JoinIterator.hpp>
#include <cpputils/iterators/LinkedIndexIterator.hpp>
#include <cpputils/iterators/IndexIterator.hpp>
#include <cpputils/iterators/ReverseIterator.hpp>
#include <cpputils/range/RangeSizer.hpp>

namespace cpputils::range
{

    namespace internal
    {

        template<typename TType>
        using ConstPtr = std::conditional_t<std::is_pointer_v<TType>, std::add_pointer_t<std::add_const_t<std::remove_pointer_t<TType>>>, TType>;

        template<typename TType>
        using ConstLRef = std::conditional_t<std::is_lvalue_reference_v<TType>, std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<TType>>>, TType>;

        template<typename TType>
        using ConstRRef = std::conditional_t<std::is_rvalue_reference_v<TType>, std::add_rvalue_reference_t<std::add_const_t<std::remove_reference_t<TType>>>, TType>;

        template<typename TType>
        using ConstRef = std::conditional_t<std::is_lvalue_reference_v<TType>, ConstLRef<TType>, ConstRRef<TType>>;

        template<typename TType>
        using ConstRefOrPtr = std::conditional_t<std::is_pointer_v<TType>, ConstPtr<TType>, ConstRef<TType>>;

        struct EmptyStruct final {};

    }

    template<typename TIterator, std::size_t TCompTimeSize = noCompTimeSize>
    class Range final
    {

    public:

        static constexpr bool hasCompTimeSize = TCompTimeSize != noCompTimeSize;
        static constexpr std::size_t compTimeSize = TCompTimeSize;

        using Iterator = TIterator;
        using Value = std::iter_value_t<Iterator>;
        using Reference = std::iter_reference_t<Iterator>;

    private:


        Iterator m_begin, m_end;
        mutable std::conditional_t<hasCompTimeSize, internal::EmptyStruct, std::optional<std::size_t>> m_size;

        inline void hintSize(std::size_t _size) const noexcept
        {
            if constexpr (!hasCompTimeSize)
            {
                m_size = _size;
            }
        }

        inline std::optional<std::size_t> sizeHint() const noexcept
        {
            if constexpr (hasCompTimeSize)
            {
                return compTimeSize;
            }
            else
            {
                return m_size;
            }
        }

        bool hasSize() const noexcept
        {
            if constexpr (hasCompTimeSize)
            {
                return true;
            }
            else
            {
                return m_size.has_value();
            }
        }

        template<typename TNewIterator = Iterator>
        Range<TNewIterator, noCompTimeSize> makeNewWithSize(const TNewIterator& _begin, const TNewIterator& _end, std::optional<std::size_t> _size = std::nullopt) const
        {
            return makeNew<TNewIterator, noCompTimeSize>(_begin, _end, _size);
        }

        template<typename TNewIterator = Iterator, std::size_t TNewCompTimeSize = TCompTimeSize>
        Range<TNewIterator, TNewCompTimeSize> makeNew(const TNewIterator& _begin, const TNewIterator& _end) const
        {
            if constexpr (TNewCompTimeSize != noCompTimeSize)
            {
                return makeNew<TNewIterator, TNewCompTimeSize>(_begin, _end, std::nullopt);
            }
            else
            {
                return makeNew<TNewIterator, TNewCompTimeSize>(_begin, _end, m_size);
            }
        }

        template<typename TNewIterator = Iterator, std::size_t TNewCompTimeSize = TCompTimeSize>
        Range<TNewIterator, TNewCompTimeSize> makeNew(const TNewIterator& _begin, const TNewIterator& _end, std::optional<std::size_t> _sizeHint) const
        {
            if constexpr (TNewCompTimeSize != noCompTimeSize)
            {
                return Range<TNewIterator, TNewCompTimeSize>(_begin, _end);
            }
            else
            {
                return Range<TNewIterator, TNewCompTimeSize>(_begin, _end, _sizeHint);
            }
        }

    public:

        Range(const Iterator& _begin, const Iterator& _end)
            : m_begin{ _begin }, m_end{ _end }, m_size{}
        {}

        Range(const Iterator& _begin, const Iterator& _end, std::optional<std::size_t> _size) requires (!hasCompTimeSize)
            : m_begin{ _begin }, m_end{ _end }, m_size{ _size }
        {}

        Iterator begin() const noexcept
        {
            return m_begin;
        }

        Iterator end() const noexcept
        {
            return m_end;
        }

        std::size_t size() const
        {
            if constexpr (hasCompTimeSize)
            {
                return TCompTimeSize;
            }
            else
            {
                if (!m_size)
                {
                    m_size = static_cast<std::size_t>(std::distance(m_begin, m_end));
                }
                return *m_size;
            }
        }

        bool empty() const
        {
            if constexpr (hasCompTimeSize)
            {
                return TCompTimeSize == 0;
            }
            else
            {
                if (!m_size)
                {
                    if (m_begin == m_end)
                    {
                        m_size = 0;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return m_size == 0;
                }
            }
        }

        bool isSingle() const
        {
            if constexpr (hasCompTimeSize)
            {
                return TCompTimeSize == 1;
            }
            else
            {
                if (!m_size)
                {
                    if (m_begin == m_end)
                    {
                        m_size = 0;
                        return false;
                    }
                    else
                    {
                        if (std::next(m_begin) == m_end)
                        {
                            m_size = 1;
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    return m_size == 1;
                }
            }
        }

        Reference operator[](std::size_t _offset) const
        {
            return *std::next(m_begin, static_cast<std::iter_difference_t<Iterator>>(_offset));
        }

        Reference first() const
        {
            return *m_begin;
        }

        Reference last() const
        {
            if constexpr (requires { *std::prev(m_end); })
            {
                return *std::prev(m_end);
            }
            else
            {
                return (*this)[size() - 1];
            }
        }

        Reference single() const
        {
            if (!isSingle())
            {
                throw std::logic_error{ "not single" };
            }
            return first();
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
            return isSingle() ? first() : _else;
        }

        std::vector<Value> toVector() const
        {
            std::vector<Value> out;
            if (hasSize())
            {
                out.reserve(size());
            }
            std::copy(m_begin, m_end, std::back_inserter(out));
            hintSize(out.size());
            return out;
        }

        std::array<Value, TCompTimeSize> toArray() const requires hasCompTimeSize
        {
            std::array<Value, TCompTimeSize> out;
            Iterator it{ m_begin };
            std::size_t i{};
            while (i < TCompTimeSize)
            {
                out[i++] = *(it++);
            }
            return out;
        }

        template<std::size_t TSize>
        std::array<Value, TSize> toArray(const Value& _defaultValue = {}) const
        {
            std::array<Value, TSize> out;
            std::size_t i{};
            Iterator it{ m_begin };
            while (i < TSize && it != m_end)
            {
                out[i++] = *(it++);
            }
            hintSize(i);
            while (i < TSize)
            {
                out[i++] = _defaultValue;
            }
            return out;
        }

        collections::FixedVector<Value, TCompTimeSize> toFixedVector() const requires hasCompTimeSize
        {
            collections::FixedVector<Value, TCompTimeSize> out;
            Iterator it{ m_begin };
            while (out.size() < TCompTimeSize)
            {
                out.addLast(*(it++));
            }
            return out;
        }

        template<std::size_t TCapacity>
        collections::FixedVector<Value, TCapacity> toFixedVector() const
        {
            collections::FixedVector<Value, TCapacity> out;
            Iterator it{ m_begin };
            while (out.size() < TCapacity && it != m_end)
            {
                out.addLast(*(it++));
            }
            hintSize(out.size());
            return out;
        }

        std::list<Value> toList() const
        {
            std::list<Value> out{ m_begin, m_end };
            hintSize(out.size());
            return out;
        }

        std::unordered_set<Value> toUnorderedSet() const
        {
            std::unordered_set<Value> out;
            if (hasSize())
            {
                out.reserve(size());
            }
            std::copy(m_begin, m_end, std::back_inserter(out));
            hintSize(out.size());
            return out;
        }

        template<typename TOutIterator>
        void assign(const TOutIterator& _begin) const
        {
            TOutIterator it{ _begin };
            std::size_t i{};
            for (auto&& value : *this)
            {
                *(it++) = value;
                i++;
            }
            hintSize(i);
        }

        template<typename TOutIterator>
        TOutIterator assign(const TOutIterator& _begin, const TOutIterator& _end) const
        {
            TOutIterator outIt{ _begin };
            Iterator inIt{ m_begin };
            std::size_t i{};
            while (inIt != m_end && outIt != _end)
            {
                *(outIt++) = *(inIt++);
            }
            hintSize(i);
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

        Iterator maxNextIt(std::size_t& _size) const
        {
            if (std::random_access_iterator<Iterator> && hasSize())
            {
                return std::next(m_begin, static_cast<std::iter_difference_t<Iterator>>(std::min(size(), _size)));
            }
            else
            {
                Iterator it{ m_begin };
                std::size_t i{};
                while (it != m_end && i < _size)
                {
                    ++it;
                    ++i;
                }
                if (i != _size)
                {
                    hintSize(i);
                    _size = i;
                }
                return it;
            }
        }

        auto take(std::size_t _size) const
        {
            const Iterator newEnd{ maxNextIt(_size) };
            return makeNewWithSize(m_begin, newEnd, _size);
        }

        auto skip(std::size_t _size) const
        {
            const Iterator newBegin{ maxNextIt(_size) };
            return makeNewWithSize(newBegin, m_end, _size);
        }

        template<std::size_t TSize>
        auto take() const requires (hasCompTimeSize && (TCompTimeSize >= TSize))
        {
            return makeNew<Iterator, TSize>(m_begin, m_begin + static_cast<std::iter_difference_t<Iterator>>(TSize));
        }

        template<std::size_t TSize>
        auto skip() const requires (hasCompTimeSize && (TCompTimeSize >= TSize))
        {
            return makeNew<Iterator, (TCompTimeSize - TSize)>(m_begin + static_cast<std::iter_difference_t<Iterator>>(TSize), m_end);
        }

        template<typename TPredicate>
        auto filter(const TPredicate& _predicate = {}) const
        {
            return makeNewWithSize(iterators::FilterIterator{ m_begin, m_end, _predicate }, iterators::FilterIterator{ m_end, _predicate });
        }

        auto reverse() const
        {
            return makeNew(iterators::ReverseIterator{ std::prev(m_end) }, iterators::ReverseIterator{ std::prev(m_begin) });
        }

        template<typename TMapper>
        auto map(const TMapper& _mapper = {}) const
        {
            return makeNew(iterators::MapIterator{ m_begin, _mapper }, iterators::MapIterator{ m_end, _mapper });
        }

        template<typename TOutReference>
        auto cast() const
        {
            return map([](auto&& _x) -> TOutReference { return static_cast<TOutReference>(_x); });
        }

        auto address() const
        {
            return map([](auto&& _x) { return std::addressof(_x); });
        }

        auto dereference() const
        {
            return map([](auto&& _x) -> auto&& { return *_x; });
        }

        auto immutable() const
        {
            return cast<internal::ConstRefOrPtr<Reference>>();
        }

        auto index() const
        {
            return makeNew(iterators::IndexIterator<std::size_t>{}, iterators::IndexIterator<std::size_t>{ size() }, size());
        }

        auto indexLazy() const requires (!hasCompTimeSize)
        {
            return makeNew(iterators::LinkedIndexIterator<Iterator, std::size_t>{m_begin}, iterators::LinkedIndexIterator<Iterator, std::size_t>{ m_end });
        }

        template<typename TIterable, typename ... TIterables>
        auto zip(TIterable& _iterable, TIterables& ..._iterables) const
        {
            return makeNew(iterators::ZipIterator{ m_begin, std::begin(_iterable), std::begin(_iterables)... }, iterators::ZipIterator{ m_end, std::end(_iterable), std::end(_iterables)... });
        }

        template<typename TIterable, typename ... TIterables>
        auto zip(const TIterable& _iterable, const TIterables& ..._iterables) const
        {
            return makeNew(iterators::ZipIterator{ m_begin, std::begin(_iterable), std::begin(_iterables)... }, iterators::ZipIterator{ m_end, std::end(_iterable), std::end(_iterables)... });
        }

        template<typename TIterable> requires (!(hasCompTimeSize && (internal::compTimeSize<TIterable> != noCompTimeSize)))
            auto join(TIterable& _iterable) const
        {
            auto secondBegin{ std::begin(_iterable) };
            return makeNewWithSize(
                iterators::JoinIterator{ m_begin, m_end, secondBegin, iterators::joinFirstTag },
                iterators::JoinIterator{ std::end(_iterable), m_end, secondBegin, iterators::joinSecondTag },
                internal::sumSizeHints(sizeHint(), RangeSizer<TIterable>{_iterable}.sizeHint())
            );
        }

        template<typename TIterable> requires (!(hasCompTimeSize && (internal::compTimeSize<TIterable> != noCompTimeSize)))
            auto join(const TIterable& _iterable) const
        {
            auto secondBegin{ std::begin(_iterable) };
            return makeNewWithSize(
                iterators::JoinIterator{ m_begin, m_end, secondBegin, iterators::joinFirstTag },
                iterators::JoinIterator{ std::end(_iterable), m_end, secondBegin, iterators::joinSecondTag },
                internal::sumSizeHints(sizeHint(), RangeSizer<TIterable>{_iterable}.sizeHint())
            );
        }

        template<typename TIterable> requires (hasCompTimeSize && (internal::compTimeSize<TIterable> != noCompTimeSize))
            auto join(TIterable& _iterable) const
        {
            auto secondBegin{ std::begin(_iterable) };
            return makeNew <iterators::JoinIterator<Iterator, decltype(secondBegin)>, internal::compTimeSize<TIterable> +compTimeSize>(
                iterators::JoinIterator{ m_begin, m_end, secondBegin, iterators::joinFirstTag },
                iterators::JoinIterator{ std::end(_iterable), m_end, secondBegin, iterators::joinSecondTag }
            );
        }

        template<typename TIterable> requires (hasCompTimeSize && (internal::compTimeSize<TIterable> != noCompTimeSize))
            auto join(const TIterable& _iterable) const
        {
            auto secondBegin{ std::begin(_iterable) };
            return makeNew <iterators::JoinIterator<Iterator, decltype(secondBegin)>, internal::compTimeSize<TIterable> +compTimeSize>(
                iterators::JoinIterator{ m_begin, m_end, secondBegin, iterators::joinFirstTag },
                iterators::JoinIterator{ std::end(_iterable), m_end, secondBegin, iterators::joinSecondTag }
            );
        }

        auto fill(std::size_t _size, const Value& _value = {})
        {
            const std::size_t count{ _size > size() ? _size - size() : 0 };
            return join(Range<iterators::IndexIterator<std::size_t>>{ { 0 }, { count }, count }.map([_value](std::size_t) {return _value;}));
        }

        auto resize(std::size_t _size, const Value& _value = {})
        {
            const std::size_t takeCount{ _size < size() ? _size : size() };
            const std::size_t joinCount{ _size > size() ? _size - size() : 0 };
            return take(takeCount).join(Range<iterators::IndexIterator<std::size_t>>{ { 0 }, { joinCount }}.map([_value](std::size_t) {return _value;}));
        }

        template<std::size_t TSize>
        auto resize(const Value& _value = {})
        {
            const auto range{ resize(TSize, _value) };
            return Range<typename decltype(range)::Iterator, TSize>(range.begin(), range.end());
        }

        auto enumerate() const
        {
            return zip(index());
        }

        auto enumerateLazy() const requires (!hasCompTimeSize)
        {
            return zip(indexLazy());
        }

        template<typename TAccumulator, typename TReduce>
        TAccumulator reduce(const TReduce& _reduce, const TAccumulator& _start) const
        {
            TAccumulator accumulator{ _start };
            std::size_t i{};
            for (auto&& value : *this)
            {
                accumulator = _reduce(value, accumulator);
                ++i;
            }
            hintSize(i);
            return accumulator;
        }

        template<typename TCompare>
        Reference best(const TCompare& _compare) const
        {
            return *bestIt(_compare);
        }

        template<typename TCompare>
        Reference best(const TCompare& _compare, Reference _else) const
        {
            return empty() ? _else : best(_compare);
        }

        template<typename TCompare>
        Iterator bestIt(const TCompare& _compare) const
        {
            Iterator best{ m_begin };
            Iterator it{ m_begin };
            std::size_t i{};
            while (it != m_end)
            {
                if (_compare(*it, *best))
                {
                    best = it;
                }
                it++;
                i++;
            }
            hintSize(i);
            return best;
        }

        Reference min() const
        {
            return best(std::less<Value>{});
        }

        Reference max() const
        {
            return best(std::greater<Value>{});
        }

        Reference min(Reference _else) const
        {
            return empty() ? _else : min();
        }

        Reference max(Reference _else) const
        {
            return empty() ? _else : max();
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
            TSum sum{};
            std::size_t i{};
            for (const Value& x : *this)
            {
                sum += x;
                i++;
            }
            hintSize(i);
            return sum / static_cast<TSum>(i);
        }

        bool isSet() const
        {
            if constexpr (hasCompTimeSize)
            {
                auto data{ toArray() };
                std::sort(data.begin(), data.end());
                return std::adjacent_find(data.begin(), data.end()) == data.end();
            }
            else
            {
                auto data{ toVector() };
                std::sort(data.begin(), data.end());
                return std::adjacent_find(data.begin(), data.end()) == data.end();
            }
        }

    };

}