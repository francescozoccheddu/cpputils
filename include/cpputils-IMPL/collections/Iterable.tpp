#ifndef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterable.hpp>

#include <memory>

namespace cpputils::collections
{

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::Iterable(TIterable& _iterable) 
		: m_iterable{ std::addressof(_iterable) }
	{}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator CPPUTILS_COLLECTIONS_ITERABLE::begin()
	{
		return iterator{ m_iterable->begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::cbegin() const
	{
		return const_iterator{ m_iterable->cbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::begin() const
	{
		return const_iterator{ m_iterable->begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator CPPUTILS_COLLECTIONS_ITERABLE::end()
	{
		return iterator{ m_iterable->end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::cend() const
	{
		return const_iterator{ m_iterable->cend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::end() const
	{
		return const_iterator{ m_iterable->end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator CPPUTILS_COLLECTIONS_ITERABLE::rbegin() requires std::bidirectional_iterator<typename TIterable::iterator>
	{
		return iterator{ m_iterable->rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::crbegin() const requires std::bidirectional_iterator<typename TIterable::const_iterator>
	{
		return const_iterator{ m_iterable->crbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::rbegin() const requires std::bidirectional_iterator<typename TIterable::const_iterator>
	{
		return const_iterator{ m_iterable->rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator CPPUTILS_COLLECTIONS_ITERABLE::rend() requires std::bidirectional_iterator<typename TIterable::iterator>
	{
		return iterator{ m_iterable->rend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::crend() const requires std::bidirectional_iterator<typename TIterable::const_iterator>
	{
		return const_iterator{ m_iterable->crend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE 
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator CPPUTILS_COLLECTIONS_ITERABLE::rend() const requires std::bidirectional_iterator<typename TIterable::const_iterator>
	{
		return const_iterator{ m_iterable->rend() };
	}

}

