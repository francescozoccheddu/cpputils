#pragma once

#include <iterator>
#include <tuple>

namespace cpputils::iterators
{

    template <typename TIterator, typename ... TIterators>
    class ZipIterator final
    {

    private:

        std::tuple<TIterator, TIterators...> m_it;

    public:

        using value_type = std::tuple<std::iter_reference_t<TIterator>, std::iter_reference_t<TIterators>...>;
        using reference = value_type;
        using pointer = value_type;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = std::iterator_traits<TIterator>::iterator_category;

        ZipIterator()
        {}

        ZipIterator(const TIterator& _it, const TIterators &... _its)
            : m_it{ _it, _its ... }
        {}

        reference operator*() const
        {
            return std::apply([](const auto & ... _it) {
                return value_type{ *_it ... };
            }, m_it);
        }

        pointer operator->() const
        {
            if constexpr (requires {
                std::apply([](const auto & ... _it) {
                    return value_type{ *_it.operator->() ... };
                }, m_it);
            })
            {
                return std::apply([](const auto & ... _it) {
                    return value_type{ *_it.operator->() ... };
                }, m_it);
            }
            return *(*this);
        }

        reference operator[](difference_type _offset) const
        {
            return std::apply([_offset](const auto & ... _it) {
                return value_type{ _it[_offset] ... };
            }, m_it);
        }

        ZipIterator& operator++()
        {
            std::apply([](auto & ... _it) {
                (++_it, ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator++(int)
        {
            ZipIterator clone{ *this };
            std::apply([](auto & ... _it) {
                (_it++, ...);
            }, m_it);
            return clone;
        }

        ZipIterator& operator+=(difference_type _offset)
        {
            std::apply([_offset](auto & ... _it) {
                ((_it += _offset), ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator+(difference_type _offset) const
        {
            return std::apply([_offset](const auto & ... _it) {
                return ZipIterator((_it + _offset) ...);
            }, m_it);
        }

        friend ZipIterator operator+(difference_type _offset, const ZipIterator& _iterator)
        {
            return _iterator + _offset;
        }

        ZipIterator& operator--()
        {
            std::apply([](auto & ... _it) {
                (--_it, ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator--(int)
        {
            ZipIterator clone{ *this };
            std::apply([](auto & ... _it) {
                (_it--, ...);
            }, m_it);
            return clone;
        }

        ZipIterator& operator-=(difference_type _offset)
        {
            std::apply([_offset](auto & ... _it) {
                ((_it -= _offset), ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator-(difference_type _offset) const
        {
            return std::apply([_offset](const auto & ... _it) {
                return ZipIterator((_it - _offset) ...);
            }, m_it);
        }

        friend ZipIterator operator-(difference_type _offset, const ZipIterator& _iterator)
        {
            return _iterator - _offset;
        }

        bool operator==(const ZipIterator& _other) const = default;

        auto operator<=>(const ZipIterator& _other) const = default;

        difference_type operator-(const ZipIterator& _other) const
        {
            return std::get<0>(m_it) - std::get<0>(_other.m_it);
        }

    };

}