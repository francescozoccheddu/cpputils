#pragma once 

#include <cpputils/concepts.hpp>
#include <iterator>
#include <type_traits>
#include <concepts>
#include <cstddef>
#include <utility>
#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>
#include <list>
#include <array>
#include <unordered_set>
#include <algorithm>
#include <cpputils/collections/FixedVector.hpp>

namespace cpputils::range
{

    constexpr std::size_t noCompTimeSize = std::numeric_limits<std::size_t>::max();

    struct EmptyStruct final {};

    template<std::forward_iterator TIterator, std::size_t TCompTimeSize = noCompTimeSize> requires cpputils::concepts::SimpleClass<TIterator>
    class Range final
    {

    public:

        static constexpr bool hasCompTimeSize = TCompTimeSize != noCompTimeSize;
        static constexpr std::optional<std::size_t> compTimeSize = hasCompTimeSize ? std::optional<std::size_t>{TCompTimeSize} : std::optional<std::size_t>{ std::nullopt };

        using Iterator = TIterator;
        using Value = std::iter_value_t<Iterator>;
        using Reference = std::iter_reference_t<Iterator>;

    private:


        Iterator m_begin, m_end;
        mutable std::conditional_t<hasCompTimeSize, EmptyStruct, std::optional<std::size_t>> m_size;

        inline void hintSize(std::size_t _size) const noexcept
        {
            if constexpr (!hasCompTimeSize)
            {
                m_size = _size;
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
                    m_size = std::distance(m_begin, m_end);
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

        Reference operator[](std::size_t _offset) const
        {
            return *std::next(m_begin, _offset);
        }

        Reference single() const
        {
            if (!isSingle())
            {
                throw std::logic_error{ "not single" };
            }
            return first();
        }

        std::vector<Value> toVector() const
        {
            std::vector<Value> out;
            if constexpr (hasCompTimeSize)
            {
                out.reserve(size());
            }
            else if (m_size)
            {
                out.reserve(size());
            }
            std::copy(out.begin(), out.end(), std::back_inserter(out));
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
            if constexpr (hasCompTimeSize)
            {
                out.reserve(size());
            }
            else if (m_size)
            {
                out.reserve(size());
            }
            std::copy(out.begin(), out.end(), std::back_inserter(out));
            hintSize(out.size());
            return out;
        }

        template<std::output_iterator<Value> TOutIterator>
        void assign(const TOutIterator& _begin) const
        {
            TOutIterator it{ _begin };
            std::size_t i{};
            for (auto& value : *this)
            {
                *(it++) = value;
                i++;
            }
            hintSize(i);
        }

        template<std::output_iterator<Value> TOutIterator>
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

        template<std::output_iterator<Value> TOutIterator>
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