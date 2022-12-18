#pragma once

#include <cpputils/range/iterators/internal/Iterator.hpp>
#include <iterator>

namespace cpputils::range::iterators
{

    template <typename TIterator, typename ... TIterators>
    class ZipIterator final
    {

    private:

        std::tuple<TIterator, TIterators...> m_it;

    public:

        using value_type = std::tuple<std::iter_reference_t<TIterator>, std::iter_reference_t<TIterators>...>;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = internal::RandomAccessCategory<TIterator>;

        ZipIterator(const TIterator& _it, const TIterators &... _its)
            : m_it{ _it, _its ... }
        {}

        value_type operator*() const
        {
            return std::apply([](const auto & ... _it) {
                return value_type{ *_it ... };
            }, m_it);
        }

        value_type operator[](difference_type _offset) const
        {
            return std::apply([_offset](const auto & ... _it) {
                return value_type{ *std::next(_it, _offset) ... };
            }, m_it);
        }

        ZipIterator& operator++()
        {
            std::apply([](auto & ... _it) {
                (std::advance(_it, 1), ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator++(int)
        {
            ZipIterator clone{ *this };
            std::apply([](auto & ... _it) {
                (std::advance(_it, 1), ...);
            }, m_it);
            return clone;
        }

        ZipIterator& operator+=(difference_type _offset)
        {
            std::apply([_offset](auto & ... _it) {
                (std::advance(_it, _offset), ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator+(difference_type _offset) const
        {
            ZipIterator clone{ *this };
            std::apply([](const auto & ... _it) {
                (std::advance(_it, 1), ...);
            }, clone.m_it);
            return clone;
        }

        ZipIterator& operator--()
        {
            std::apply([](auto & ... _it) {
                (std::advance(_it, -1), ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator--(int)
        {
            ZipIterator clone{ *this };
            std::apply([](auto & ... _it) {
                (std::advance(_it, -1), ...);
            }, m_it);
            return clone;
        }

        ZipIterator& operator-=(difference_type _offset)
        {
            std::apply([_offset](auto & ... _it) {
                (std::advance(_it, -_offset), ...);
            }, m_it);
            return *this;
        }

        ZipIterator operator-(difference_type _offset) const
        {
            ZipIterator clone{ *this };
            std::apply([_offset](const auto & ... _it) {
                (std::advance(_it, -_offset), ...);
            }, clone.m_it);
            return clone;
        }

        bool operator==(const ZipIterator& _other) const
        {
            return std::get<0>(m_it) == std::get<0>(_other.m_it);
        }

        difference_type operator-(const ZipIterator& _other) const
        {
            return std::distance(_other.m_it[0], m_it[0]);
        }

    };

}