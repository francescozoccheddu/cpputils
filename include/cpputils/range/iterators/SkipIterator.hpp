#pragma once

#include <cpputils/range/iterators/internal/Iterator.hpp>
#include <iterator>
#include <memory>

namespace cpputils::range::iterators
{

    template<typename TIterator, bool(*TShouldSkip)(const TIterator& _it, const internal::IteratorBase<TIterator>& _this)>
    class SkipIterator: public internal::Iterator<TIterator>
    {

    private:

        using Base = internal::Iterator<TIterator>;

        mutable TIterator m_it;

        void advance() const
        {
            while (m_it != this->end() && TShouldSkip(m_it, *this))
            {
                std::advance(m_it, 1);
            }
        }

        void advanceReverse() const
        {
            while (m_it != this->begin() && TShouldSkip(m_it, *this))
            {
                std::advance(m_it, -1);
            }
        }


    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        SkipIterator(const std::shared_ptr<range::internal::Data<TIterator>>& _data, const TIterator& _it)
            : Base{ _data }, m_it{ _it }
        {
            advance();
        }

        reference operator*() const
        {
            advance();
            return *m_it;
        }

        pointer operator->() const
        {
            advance();
            return m_it.operator->();
        }

        reference operator[](difference_type _offset) const
        {
            advance();
            return *std::next(m_it, _offset);
        }

        SkipIterator& operator++()
        {
            advance();
            if (m_it != this->end())
            {
                std::advance(m_it, 1);
            }
            advance();
            return *this;
        }

        SkipIterator operator++(int)
        {
            SkipIterator clone{ *this };
            ++(*this);
            return clone;
        }

        SkipIterator& operator+=(difference_type _offset)
        {
            advance();
            while (m_it != this->end() && _offset != 0)
            {
                std::advance(m_it, 1);
                advance();
                --_offset;
            }
            return *this;
        }

        SkipIterator operator+(difference_type _offset) const
        {
            SkipIterator clone{ *this };
            clone += _offset;
            return clone;
        }

        SkipIterator& operator--()
        {
            advanceReverse();
            if (m_it != this->begin())
            {
                std::advance(m_it, -1);
            }
            advanceReverse();
            return *this;
        }

        SkipIterator operator--(int)
        {
            SkipIterator clone{ *this };
            --(*this);
            return clone;
        }

        SkipIterator& operator-=(difference_type _offset)
        {
            advanceReverse();
            while (m_it != this->begin() && _offset != 0)
            {
                std::advance(m_it, -1);
                advanceReverse();
                --_offset;
            }
            return *this;
        }

        SkipIterator operator-(difference_type _offset) const
        {
            SkipIterator clone{ *this };
            clone -= _offset;
            return clone;
        }

        bool operator==(const SkipIterator& _other) const
        {
            advance();
            _other.advance();
            return m_it == _other.m_it;
        }

        difference_type operator-(const SkipIterator& _other) const
        {
            difference_type count{};
            TIterator it{ _other.m_it };
            while (it != m_it)
            {
                while (it != m_it && filterShouldSkip(it, this->begin(), this->end()))
                {
                    ++it;
                }
                --count;
            }
            return count;
        }

    };

}