#ifndef CPPUTILS_COLLECTIONS_ITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERATOR_INCLUDED

#include <type_traits>
#include <iterator>
#include <functional>

#define CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE \
	template< \
		typename TIterator, \
		typename TDereferenceResult, \
		TDereferenceResult (*TDereference)(const TIterator&), \
		typename TCategory, \
		typename TDifferenceType \
	>

#define CPPUTILS_COLLECTIONS_ITERATOR_ARGS <TIterator, TDereferenceResult, TDereference, TCategory, TDifferenceType>

#define CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINT requires internal::IsValidIterator<TIterator, TCategory>

#define CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINT

#define CPPUTILS_COLLECTIONS_ITERATOR Iterator CPPUTILS_COLLECTIONS_ITERATOR_ARGS

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterator, typename TCategory> concept IsValidIterator
			= std::input_or_output_iterator<TIterator>
			&& (std::is_base_of_v<std::input_iterator_tag, TCategory> || std::is_base_of_v<std::output_iterator_tag, TCategory>);

	}

	CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE class Iterator;

	namespace internal
	{
		template<typename TIterator>
		class IteratorBase
		{

		private:

			CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE friend class collections::Iterator;

			TIterator m_iterator;

			IteratorBase(const TIterator& _iterator);
			IteratorBase(TIterator&& _iterator);

		public:

			auto operator<=>(const IteratorBase& _other) const = default;

		};

	}

	template<
		typename TIterator,
		typename TDereferenceResult = typename TIterator::reference,
		TDereferenceResult(*TDereference)(const TIterator&) = [](const TIterator& _iterator) -> TDereferenceResult { return (TDereferenceResult)(*_iterator); },
		typename TCategory = typename TIterator::iterator_category,
		typename TDifferenceType = typename TIterator::difference_type
	>
		CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINT
		class Iterator final : public internal::IteratorBase<TIterator>
	{

	private:

		using internal::IteratorBase<TIterator>::m_iterator;

	public:

		using value_type = std::remove_reference_t<TDereferenceResult>;
		using reference = TDereferenceResult;
		using pointer = value_type*;
		using difference_type = TDifferenceType;
		using iterator_category = TCategory;

		Iterator(const TIterator& _iterator);
		Iterator(TIterator&& _iterator);

		reference operator*() const;
		pointer operator->() const requires std::is_reference_v<reference>;
		reference operator[](difference_type _offset) const requires std::random_access_iterator<TIterator>;

		Iterator& operator++() requires std::forward_iterator<TIterator>;
		Iterator operator++(int) const requires std::forward_iterator<TIterator>;
		Iterator& operator+=(difference_type _offset) requires std::random_access_iterator<TIterator>;

		Iterator& operator--() requires std::bidirectional_iterator<TIterator>;
		Iterator operator--(int) const requires std::bidirectional_iterator<TIterator>;
		Iterator& operator-=(difference_type _offset) requires std::random_access_iterator<TIterator>;

		Iterator operator+(difference_type _other) const requires std::random_access_iterator<TIterator>;
		Iterator operator-(difference_type _other) const requires std::random_access_iterator<TIterator>;

		difference_type operator-(const Iterator& _other) const requires std::random_access_iterator<TIterator>;

	};

}

#define CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterator.tpp>
#undef CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION

#undef CPPUTILS_COLLECTIONS_ITERATOR_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERATOR_ARGS
#undef CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINT
#undef CPPUTILS_COLLECTIONS_ITERATOR_CONSTRAINED_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERATOR

#endif