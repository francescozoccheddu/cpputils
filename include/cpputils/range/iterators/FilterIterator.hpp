#pragma once

#include <cpputils/range/iterators/internal/Iterator.hpp>
#include <iterator>
#include <memory>
#include <optional>

namespace cpputils::range::iterators
{

    template<typename TIterator, typename TPredicate>
    class FilterIterator final: public internal::Iterator<TIterator, std::iter_reference_t<TIterator>, std::forward_iterator_tag>
    {

    private:

        using Base = internal::Iterator<TIterator, std::iter_reference_t<TIterator>, std::forward_iterator_tag>;

        mutable TIterator m_it;

        TPredicate m_predicate;

        void skip()
        {
            while (m_it != this->end() && !m_predicate(m_it, this->begin(), this->end()))
            {
                ++m_it;
            }
        }

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        FilterIterator(const std::shared_ptr<range::internal::Data<TIterator>>& _data, const TIterator& _it, const TPredicate& _predicate = {})
            : Base{ _data }, m_it{ _it }, m_predicate{ _predicate }
        {
            skip();
        }

        const TPredicate& predicate() const
        {
            return m_predicate;
        }

        reference operator*() const
        {
            return *m_it;
        }

        pointer operator->() const
        {
            return std::addressof(*(*this));
        }

        reference operator[](difference_type _offset) const
        {
            return *(std::next(*this, _offset));
        }

        FilterIterator& operator++()
        {
            std::advance(m_it, 1);
            skip();
            return *this;
        }

        FilterIterator operator++(int)
        {
            FilterIterator clone{ *this };
            ++(*this);
            return clone;
        }

        bool operator==(const FilterIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        auto operator<=>(const FilterIterator& _other) const
        {
            return m_it <=> _other.m_it;
        }

    };

}