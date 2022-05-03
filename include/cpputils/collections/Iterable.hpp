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
		TDereferenceResult(*TDereference)(const TIterable::iterator&), \
		typename TDereferenceConstResult, \
		TDereferenceConstResult(*TDereferenceConst)(const TIterable::const_iterator&), \
		typename TCategory, \
		typename TDifferenceType \
	>

#define CPPUTILS_COLLECTIONS_ITERABLE_ARGS <TIterable, TDereferenceResult, TDereference, TDereferenceConstResult, TDereferenceConst, TCategory, TDifferenceType>

#define CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT requires internal::IsValidIterable<TIterable, TCategory>

#define CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT

#define CPPUTILS_COLLECTIONS_ITERABLE Iterable CPPUTILS_COLLECTIONS_ITERABLE_ARGS

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterable, typename TCategory> concept IsValidIterable
			= internal::IsValidIterator<typename TIterable::iterator, TCategory>
			&& internal::IsValidIterator<typename TIterable::const_iterator, TCategory>;

	}

	CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE class Iterable;

	namespace internal
	{
		template<typename TIterable>
		class IterableBase
		{

		private:

			CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINED_TEMPLATE friend class collections::Iterable;

			TIterable* m_iterable;

			IterableBase(TIterable& _iterator);

		public:

			bool operator==(const IterableBase& _other) const = default;
			bool operator!=(const IterableBase& _other) const = default;

		};

	}
	template<
		typename TIterable,
		typename TDereferenceResult = std::remove_pointer_t<typename TIterable::iterator::value_type>&,
		TDereferenceResult(*TDereference)(const TIterable::iterator&) = [](const TIterable::iterator& _iterator) -> TDereferenceResult { return (TDereferenceResult)(*_iterator); },
		typename TDereferenceConstResult = std::remove_pointer_t<typename TIterable::const_iterator::value_type>&,
		TDereferenceConstResult(*TDereferenceConst)(const TIterable::const_iterator&) = [](const TIterable::const_iterator& _iterator) -> TDereferenceConstResult { return (TDereferenceConstResult)(*_iterator); },
		typename TCategory = typename TIterable::iterator::iterator_category,
		typename TDifferenceType = typename TIterable::iterator::difference_type
	>
		CPPUTILS_COLLECTIONS_ITERABLE_CONSTRAINT
		class Iterable : public internal::IterableBase<TIterable>
	{

	private:

		using internal::IterableBase<TIterable>::m_iterable;

	public:

		using iterator = Iterator<typename TIterable::iterator, TDereferenceResult, TDereference, TCategory, TDifferenceType>;
		using const_iterator = Iterator<typename TIterable::const_iterator, TDereferenceConstResult, TDereferenceConst, TCategory, TDifferenceType>;

		Iterable(TIterable& _iterator);

		iterator begin();
		const_iterator cbegin() const;
		const_iterator begin() const;

		iterator end();
		const_iterator cend() const;
		const_iterator end() const;

		iterator rbegin() requires std::bidirectional_iterator<typename TIterable::iterator>;
		const_iterator crbegin() const requires std::bidirectional_iterator<typename TIterable::const_iterator>;
		const_iterator rbegin() const requires std::bidirectional_iterator<typename TIterable::const_iterator>;

		iterator rend() requires std::bidirectional_iterator<typename TIterable::iterator>;
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