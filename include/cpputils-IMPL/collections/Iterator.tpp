#ifndef CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterator.hpp>

#include <utility>
#include <memory>

#define CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE \
template<\
	typename TIterator,\
	typename TDereferenceResult,\
	TDereferenceResult(*TConverter)(types::DereferenceResult<TIterator>)\
>

#define CPPUTILS_COLLECTIONS_ITERATOR \
Iterator<TIterator, TDereferenceResult, TConverter>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterator>
		IteratorBase<TIterator>::IteratorBase(const TIterator& _iterator)
			: m_iterator{ _iterator }
		{}

		template<typename TIterator>
		IteratorBase<TIterator>::IteratorBase(TIterator&& _iterator)
			: m_iterator{ std::move(_iterator) }
		{}

		template<typename TFrom, typename TTo>
		inline constexpr TTo naiveCast(TFrom& _from)
		{
			return (TTo)(_from);
		}

	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::Iterator(const TIterator& _iterator)
		: internal::IteratorBase<TIterator>{ _iterator }
	{}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::Iterator(TIterator&& _iterator)
		: internal::IteratorBase<TIterator>{ std::move(_iterator) }
	{}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		TIterator&
		CPPUTILS_COLLECTIONS_ITERATOR::iterator()
	{
		return internal::IteratorBase<TIterator>::m_iterator;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		const TIterator&
		CPPUTILS_COLLECTIONS_ITERATOR::iterator() const
	{
		return internal::IteratorBase<TIterator>::m_iterator;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::reference
		CPPUTILS_COLLECTIONS_ITERATOR::operator*() const
	{
		return TConverter(*iterator());
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::pointer
		CPPUTILS_COLLECTIONS_ITERATOR::operator->() const
	{
		return std::addressof(**this);
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::reference
		CPPUTILS_COLLECTIONS_ITERATOR::operator[](difference_type _offset) const
	{
		return TConverter(*(iterator() + _offset));
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR&
		CPPUTILS_COLLECTIONS_ITERATOR::operator++()
	{
		++iterator();
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator++(int)
	{
		Iterator clone{ *this };
		iterator()++;
		return clone;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR&
		CPPUTILS_COLLECTIONS_ITERATOR::operator+=(difference_type _offset)
	{
		iterator() += _offset;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR&
		CPPUTILS_COLLECTIONS_ITERATOR::operator--()
	{
		--iterator();
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator--(int)
	{
		Iterator clone{ *this };
		iterator()--;
		return clone;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR&
		CPPUTILS_COLLECTIONS_ITERATOR::operator-=(difference_type _offset)
	{
		iterator() -= _offset;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator+(difference_type _other) const
	{
		return Iterator{ iterator() + _other };
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator-(difference_type _other) const
	{
		return Iterator{ iterator() + _other };
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::difference_type
		CPPUTILS_COLLECTIONS_ITERATOR::operator-(const Iterator& _other) const
	{
		return iterator() - _other.iterator();
	}

}

#undef CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERATOR