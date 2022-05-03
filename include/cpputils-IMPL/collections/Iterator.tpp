#ifndef CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterator.hpp>

#include <utility>
#include <memory>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterator> requires std::input_or_output_iterator<TIterator>
		IteratorBase<TIterator>::IteratorBase(const TIterator& _iterator)
			: m_iterator{ _iterator }
		{}

		template<typename TIterator> requires std::input_or_output_iterator<TIterator>
		IteratorBase<TIterator>::IteratorBase(TIterator&& _iterator)
			: m_iterator{ std::move(_iterator) }
		{}

	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR::Iterator(const TIterator& _iterator)
		: internal::IteratorBase<TIterator>{ _iterator }
	{}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR::Iterator(TIterator&& _iterator)
		: internal::IteratorBase<TIterator>{ std::move(_iterator) }
	{}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR::reference CPPUTILS_COLLECTIONS_ITERATOR::operator*() const
	{
		return TDereference(m_iterator);
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR::pointer CPPUTILS_COLLECTIONS_ITERATOR::operator->() const requires std::is_reference_v<reference>
	{
		return std::addressof(**this);
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR::reference CPPUTILS_COLLECTIONS_ITERATOR::operator[](difference_type _offset) const requires std::random_access_iterator<TIterator>
	{
		return TDereference(m_iterator + _offset);
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR& CPPUTILS_COLLECTIONS_ITERATOR::operator++() requires std::forward_iterator<TIterator>
	{
		++m_iterator;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR CPPUTILS_COLLECTIONS_ITERATOR::operator++(int) const requires std::forward_iterator<TIterator>
	{
		Iterator clone{ *this };
		clone.m_iterator++;
		return clone;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR& CPPUTILS_COLLECTIONS_ITERATOR::operator+=(difference_type _offset) requires std::random_access_iterator<TIterator>
	{
		m_iterator += _offset;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR& CPPUTILS_COLLECTIONS_ITERATOR::operator--() requires std::bidirectional_iterator<TIterator>
	{
		--m_iterator;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR CPPUTILS_COLLECTIONS_ITERATOR::operator--(int) const requires std::bidirectional_iterator<TIterator>
	{
		Iterator clone{ *this };
		clone.m_iterator--;
		return clone;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR& CPPUTILS_COLLECTIONS_ITERATOR::operator-=(difference_type _offset) requires std::random_access_iterator<TIterator>
	{
		m_iterator -= _offset;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR CPPUTILS_COLLECTIONS_ITERATOR::operator+(difference_type _other) const requires std::random_access_iterator<TIterator>
	{
		return Iterator{ m_iterator + _other };
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR CPPUTILS_COLLECTIONS_ITERATOR::operator-(difference_type _other) const requires std::random_access_iterator<TIterator>
	{
		return Iterator{ m_iterator + _other };
	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
	CPPUTILS_COLLECTIONS_ITERATOR::difference_type CPPUTILS_COLLECTIONS_ITERATOR::operator-(const Iterator& _other) const requires std::random_access_iterator<TIterator>
	{
		return m_iterator - _other.m_iterator;
	}

}

