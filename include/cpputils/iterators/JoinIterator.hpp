#pragma once

#include <iterator>
#include <variant>
#include <utility>
#include <type_traits>
#include <memory>

namespace cpputils::iterators
{

    constexpr std::in_place_index_t<0> joinFirstTag{ std::in_place_index<0> };
    constexpr std::in_place_index_t<1> joinSecondTag{ std::in_place_index<1> };

    template<typename TFirstIterator, typename TSecondIterator>
    class JoinIterator final
    {

    private:

        std::variant<TFirstIterator, TSecondIterator> m_it;
        TFirstIterator m_firstEnd;
        TSecondIterator m_secondBegin;

        using UnderlyingCategory = typename std::iterator_traits<TFirstIterator>::iterator_category;

        void skip()
        {
            if (!m_it.index() && std::get<0>(m_it) == m_firstEnd)
            {
                m_it.template emplace<1>(m_secondBegin);
            }
        }

        void skipReverse()
        {
            if (m_it.index() && std::get<1>(m_it) == m_secondBegin)
            {
                m_it.template emplace<0>(m_firstEnd);
            }
        }

    public:

        using value_type = std::iter_value_t<TFirstIterator>;
        using reference = std::iter_reference_t<TFirstIterator>;
        using pointer = std::remove_reference_t<reference>*;
        using difference_type = std::iter_difference_t<TFirstIterator>;
        using iterator_category = std::conditional_t<
            std::derived_from<UnderlyingCategory, std::bidirectional_iterator_tag>,
            std::bidirectional_iterator_tag,
            UnderlyingCategory
        >;

        JoinIterator()
            : m_it{ joinSecondTag, {} }
        {
            skip();
        }

        JoinIterator(const TFirstIterator& _iterator, const TFirstIterator& _firstEnd, const TSecondIterator& _secondBegin, std::in_place_index_t<0> _tag = joinFirstTag)
            : m_it{ joinFirstTag, _iterator }, m_firstEnd{ _firstEnd }, m_secondBegin{ _secondBegin }
        {
            skip();
        }

        JoinIterator(const TSecondIterator& _iterator, const TFirstIterator& _firstEnd, const TSecondIterator& _secondBegin, std::in_place_index_t<1> _tag = joinSecondTag)
            : m_it{ joinSecondTag, _iterator }, m_firstEnd{ _firstEnd }, m_secondBegin{ _secondBegin }
        {
            skip();
        }

        reference operator*() const
        {
            if (m_it.index()) return *std::get<1>(m_it);
            else return *std::get<0>(m_it);
        }

        pointer operator->() const
        {
            if constexpr (requires{ std::get<1>(m_it).operator->(); std::get<0>(m_it).operator->(); })
            {
                return m_it.index() ? std::get<1>(m_it).operator->() : std::get<0>(m_it).operator->();
            }
            return std::addressof(*(*this));
        }

        JoinIterator& operator++()
        {
            if (m_it.index()) ++std::get<1>(m_it);
            else ++std::get<0>(m_it);
            skip();
            return *this;
        }

        JoinIterator operator++(int)
        {
            JoinIterator clone{ *this };
            if (m_it.index()) std::get<1>(m_it)++;
            else std::get<0>(m_it)++;
            skip();
            return clone;
        }

        JoinIterator& operator--()
        {
            skipReverse();
            if (m_it.index()) --std::get<1>(m_it);
            else --std::get<0>(m_it);
            return *this;
        }

        JoinIterator operator--(int)
        {
            JoinIterator clone{ *this };
            skipReverse();
            if (m_it.index()) std::get<1>(m_it)--;
            else std::get<0>(m_it)--;
            return clone;
        }

        bool operator==(const JoinIterator& _other) const
        {
            return m_it == _other.m_it;
        }

    };

}