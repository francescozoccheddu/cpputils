#pragma once

#include <cpputils/range/iterators/internal/Iterator.hpp>
#include <iterator>

namespace cpputils::range::iterators
{

    template<typename TIterator>
    class ReverseIterator final: public internal::Iterator<TIterator>
    {

    private:

        using Base = internal::Iterator<TIterator>;

        TIterator m_it;

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        ReverseIterator(const std::shared_ptr<range::internal::Data<TIterator>>& _data, const TIterator& _it)
            : Base{ _data }, m_it{ _it }
        {}

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
            return *std::next(m_it, _offset);
        }

        ReverseIterator& operator++()
        {
            std::advance(m_it, -1);
            return *this;
        }

        ReverseIterator operator++(int)
        {
            ReverseIterator clone{ *this };
            ++(*this);
            return clone;
        }

        ReverseIterator& operator+=(difference_type _offset)
        {
            std::advance(m_it, -_offset);
            return *this;
        }

        ReverseIterator operator+(difference_type _offset) const
        {
            ReverseIterator clone{ *this };
            clone += _offset;
            return clone;
        }

        ReverseIterator& operator--()
        {
            std::advance(m_it, 1);
            return *this;
        }

        ReverseIterator operator--(int)
        {
            ReverseIterator clone{ *this };
            --(*this);
            return clone;
        }

        ReverseIterator& operator-=(difference_type _offset)
        {
            std::advance(m_it, _offset);
            return *this;
        }

        ReverseIterator operator-(difference_type _offset) const
        {
            ReverseIterator clone{ *this };
            clone -= _offset;
            return clone;
        }

        bool operator==(const ReverseIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        difference_type operator-(const ReverseIterator& _other) const
        {
            return std::distance(m_it, _other.m_it);
        }

    };

}