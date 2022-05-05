#ifndef CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterator.hpp>

#include <iterator>
#include <utility>
#include <memory>

#define CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE \
template<\
	std::input_or_output_iterator TIterator,\
	typename TDereferenceResult,\
	TDereferenceResult(*TConverter)(types::DereferenceResult<const TIterator>)\
>

#define CPPUTILS_COLLECTIONS_ITERATOR \
Iterator<TIterator, TDereferenceResult, TConverter>

namespace cpputils::collections
{

	namespace types
	{

		template<typename TFrom, typename TTo>
		inline constexpr TTo cast(TFrom _from)
		{
			return (TTo)(_from);
		}

	}

	namespace internal
	{

		template<std::input_or_output_iterator TIterator>
		IteratorBase<TIterator>::IteratorBase(const TIterator& _iterator)
			: m_iterator{ _iterator }
		{}

		template<std::input_or_output_iterator TIterator>
		IteratorBase<TIterator>::IteratorBase(TIterator&& _iterator)
			: m_iterator{ std::move(_iterator) }
		{}

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
		CPPUTILS_COLLECTIONS_ITERATOR::operator->() const requires std::is_reference_v<TDereferenceResult>
	{
		return std::addressof(**this);
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::reference
		CPPUTILS_COLLECTIONS_ITERATOR::operator[](difference_type _offset) const requires std::random_access_iterator<TIterator>
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
		CPPUTILS_COLLECTIONS_ITERATOR::operator+=(difference_type _offset) requires std::random_access_iterator<TIterator>
	{
		iterator() += _offset;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR&
		CPPUTILS_COLLECTIONS_ITERATOR::operator--() requires std::bidirectional_iterator<TIterator>
	{
		--iterator();
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator--(int) requires std::bidirectional_iterator<TIterator>
	{
		Iterator clone{ *this };
		iterator()--;
		return clone;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR&
		CPPUTILS_COLLECTIONS_ITERATOR::operator-=(difference_type _offset) requires std::random_access_iterator<TIterator>
	{
		iterator() -= _offset;
		return *this;
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator+(difference_type _other) const requires std::random_access_iterator<TIterator>
	{
		return Iterator{ iterator() + _other };
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR
		CPPUTILS_COLLECTIONS_ITERATOR::operator-(difference_type _other) const requires std::random_access_iterator<TIterator>
	{
		return Iterator{ iterator() + _other };
	}

	CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERATOR::difference_type
		CPPUTILS_COLLECTIONS_ITERATOR::operator-(const Iterator& _other) const requires std::random_access_iterator<TIterator>
	{
		return iterator() - _other.iterator();
	}

}

#undef CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERATOR