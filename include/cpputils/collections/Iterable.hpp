#ifndef CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <type_traits>
#include <iterator>
#include <functional>

#define CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE \
	template<\
		typename TIterable, \
		typename TDereferenceResult, \
		TDereferenceResult(*TDereference)(const internal::TIterableIterator<TIterable>&), \
		typename TDereferenceConstResult, \
		TDereferenceConstResult(*TDereferenceConst)(const typename TIterable::const_iterator&), \
		typename TCategory, \
		typename TDifferenceType, \
		typename TConstCategory, \
		typename TConstDifferenceType \
	>

#define CPPUTILS_COLLECTIONS_ITERABLE_ARGS <TIterable, TDereferenceResult, TDereference, TDereferenceConstResult, TDereferenceConst, TCategory, TDifferenceType, TConstCategory, TConstDifferenceType>

#define CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT requires internal::IsValidIterable<TIterable, TCategory, TConstCategory>

#define CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT

#define CPPUTILS_COLLECTIONS_ITERABLE Iterable CPPUTILS_COLLECTIONS_ITERABLE_ARGS

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterable>
		using TIterableIterator = std::conditional_t<std::is_const_v<TIterable>, typename TIterable::const_iterator, typename TIterable::iterator>;

		template<typename TIterable, typename TCategory, typename TConstCategory> concept IsValidIterable
			= internal::IsValidIterator<TIterableIterator<TIterable>, TCategory>
			&& internal::IsValidIterator<typename TIterable::const_iterator, TConstCategory>;

	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE class Iterable;

	namespace internal
	{
		template<typename TIterableBase>
		class IterableBase
		{

		private:

			CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE friend class collections::Iterable;

			TIterableBase* m_iterable;

			IterableBase(TIterableBase& _iterator);

		public:

			bool operator==(const IterableBase& _other) const = default;
			bool operator!=(const IterableBase& _other) const = default;

		};

	}
	template<
		typename TIterable,
		typename TDereferenceResult = typename internal::TIterableIterator<TIterable>::value_type&,
		TDereferenceResult(*TDereference)(const internal::TIterableIterator<TIterable>&) = [](const internal::TIterableIterator<TIterable>& _iterator) -> TDereferenceResult { return (TDereferenceResult)(*_iterator); },
		typename TDereferenceConstResult = typename TIterable::const_iterator::value_type&,
		TDereferenceConstResult(*TDereferenceConst)(const typename TIterable::const_iterator&) = [](const TIterable::const_iterator& _iterator) -> TDereferenceConstResult { return (TDereferenceConstResult)(*_iterator); },
		typename TCategory = typename internal::TIterableIterator<TIterable>::iterator_category,
		typename TDifferenceType = typename internal::TIterableIterator<TIterable>::difference_type,
		typename TConstCategory = typename TIterable::const_iterator::iterator_category,
		typename TConstDifferenceType = typename TIterable::const_iterator::difference_type
	>
		CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT
		class Iterable : public internal::IterableBase<TIterable>
	{

	private:

		using internal::IterableBase<TIterable>::m_iterable;

	public:

		using iterator = Iterator<internal::TIterableIterator<TIterable>, TDereferenceResult, TDereference, TCategory, TDifferenceType>;
		using const_iterator = Iterator<typename TIterable::const_iterator, TDereferenceConstResult, TDereferenceConst, TConstCategory, TConstDifferenceType>;

		Iterable(TIterable& _iterator);

		iterator begin();
		const_iterator cbegin() const;
		const_iterator begin() const;

		iterator end();
		const_iterator cend() const;
		const_iterator end() const;

		iterator rbegin() requires std::bidirectional_iterator<typename internal::TIterableIterator<TIterable>>;
		const_iterator crbegin() const requires std::bidirectional_iterator<typename TIterable::const_iterator>;
		const_iterator rbegin() const requires std::bidirectional_iterator<typename TIterable::const_iterator>;

		iterator rend() requires std::bidirectional_iterator<typename internal::TIterableIterator<TIterable>>;
		const_iterator crend() const requires std::bidirectional_iterator<typename TIterable::const_iterator>;
		const_iterator rend() const requires std::bidirectional_iterator<typename TIterable::const_iterator>;

	};

}

#define CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterable.tpp>
#undef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION

#undef CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERABLE_ARGS
#undef CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT
#undef CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERABLE

#endif