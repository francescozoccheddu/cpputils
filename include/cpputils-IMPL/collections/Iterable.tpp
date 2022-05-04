#ifndef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterable.hpp>

#include <memory>

#define CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE \
template<\
	typename TIterable,\
	typename TDereferenceResult,\
	TDereferenceResult(*TDereference)(const internal::IterableIterator<TIterable>&),\
	typename TDereferenceConstResult,\
	TDereferenceConstResult(*TDereferenceConst)(const internal::IterableConstIterator<TIterable>&),\
	typename TCategory,\
	typename TDifferenceType,\
	typename TConstCategory,\
	typename TConstDifferenceType\
>

#define CPPUTILS_COLLECTIONS_ITERABLE \
Iterable<TIterable, TDereferenceResult, TDereference, TDereferenceConstResult, TDereferenceConst, TCategory, TDifferenceType, TConstCategory, TConstDifferenceType>

namespace cpputils::collections
{

	template<typename TIterable>
	internal::IterableBase<TIterable>::IterableBase(TIterable& _iterable)
		: m_iterable{ std::addressof(_iterable) }
	{}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::Iterable(TIterable& _iterable)
		: internal::IterableBase<TIterable>{ _iterable }
	{}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TIterable&
		CPPUTILS_COLLECTIONS_ITERABLE::iterable() const
	{
		return *internal::IterableBase<TIterable>::m_iterable;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator
		CPPUTILS_COLLECTIONS_ITERABLE::begin()
	{
		return iterator{ iterable().begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::cbegin() const
	{
		return const_iterator{ iterable().cbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::begin() const
	{
		return const_iterator{ iterable().begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator
		CPPUTILS_COLLECTIONS_ITERABLE::end()
	{
		return iterator{ iterable().end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::cend() const
	{
		return const_iterator{ iterable().cend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::end() const
	{
		return const_iterator{ iterable().end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rbegin()
	{
		return iterator{ iterable().rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::crbegin() const
	{
		return const_iterator{ iterable().crbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rbegin() const
	{
		return const_iterator{ iterable().rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rend()
	{
		return iterator{ iterable().rend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::crend() const
	{
		return const_iterator{ iterable().crend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rend() const
	{
		return const_iterator{ iterable().rend() };
	}

}

#undef CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERABLE