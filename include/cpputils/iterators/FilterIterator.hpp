#pragma once

#include <iterator>
#include <concepts>
#include <type_traits>

namespace cpputils::iterators
{

    template<std::input_iterator TIterator, std::predicate<const std::iter_reference_t<TIterator>> TPredicate>
    class FilterIterator final
    {

    private:

        TIterator m_it, m_begin, m_end;

        TPredicate m_predicate;

        void skip()
        {
            while (m_it != m_end && !m_predicate(*m_it))
            {
                ++m_it;
            }
        }

        using UnderlyingCategory = typename std::iterator_traits<TIterator>::iterator_category;

    public:

        using value_type = std::iter_value_t<TIterator>;
        using reference = std::iter_reference_t<TIterator>;
        using pointer = std::remove_reference_t<reference>*;
        using difference_type = std::iter_difference_t<TIterator>;
        using iterator_category = std::conditional_t<
            std::derived_from<UnderlyingCategory, std::forward_iterator_tag>,
            std::forward_iterator_tag,
            UnderlyingCategory
        >;

        FilterIterator(const TPredicate& _predicate = {})
            : m_predicate{ _predicate }
        {}

        FilterIterator(const TIterator& _it, const TIterator& _end, const TPredicate& _predicate = {})
            : m_it{ _it }, m_end{ _end }, m_predicate{ _predicate }
        {
            skip();
        }

        FilterIterator(const TIterator& _end, const TPredicate& _predicate = {})
            : m_it{ _end }, m_end{ _end }, m_predicate{ _predicate }
        {}

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
            if constexpr (requires{ m_it.operator->(); })
            {
                return m_it.operator->();
            }
            return std::addressof(*m_it);
        }

        FilterIterator& operator++()
        {
            ++m_it;
            skip();
            return *this;
        }

        FilterIterator operator++(int)
        {
            FilterIterator clone{ *this };
            ++clone.m_it;
            clone.skip();
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