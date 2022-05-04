#ifndef CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <type_traits>
#include <iterator>
#include <functional>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterable>
		using IterableIterator = std::conditional_t<std::is_const_v<TIterable>, typename TIterable::const_iterator, typename TIterable::iterator>;

		template<typename TIterable>
		using IterableConstIterator = typename TIterable::const_iterator;

	}

	template<
		typename TIterable,
		typename TDereferenceResult,
		TDereferenceResult(*)(const internal::IterableIterator<TIterable>&),
		typename TDereferenceConstResult,
		TDereferenceConstResult(*)(const internal::IterableConstIterator<TIterable>&),
		typename TCategory,
		typename,
		typename TConstCategory,
		typename
	>
		class Iterable;

	namespace internal
	{
		template<typename TIterable>
		class IterableBase
		{

		private:

			template<
				typename TIterableIterable,
				typename TDereferenceResult,
				TDereferenceResult(*)(const internal::IterableIterator<TIterableIterable>&),
				typename TDereferenceConstResult,
				TDereferenceConstResult(*)(const internal::IterableConstIterator<TIterableIterable>&),
				typename TCategory,
				typename,
				typename TConstCategory,
				typename
			>
				friend class collections::Iterable;

			TIterable* m_iterable;

			IterableBase(TIterable& _iterator);

		public:

			bool operator==(const IterableBase& _other) const = default;
			bool operator!=(const IterableBase& _other) const = default;

		};

	}
	template<
		typename TIterable,
		typename TDereferenceResult = typename internal::IterableIterator<TIterable>::value_type&,
		TDereferenceResult(*TDereference)(const internal::IterableIterator<TIterable>&) = internal::iteratorDereferenceCCast<internal::IterableIterator<TIterable>, TDereferenceResult>,
		typename TDereferenceConstResult = typename internal::IterableConstIterator<TIterable>::value_type&,
		TDereferenceConstResult(*TDereferenceConst)(const typename internal::IterableConstIterator<TIterable>&) = internal::iteratorDereferenceCCast<internal::IterableConstIterator<TIterable>, TDereferenceConstResult>,
		typename TCategory = typename internal::IterableIterator<TIterable>::iterator_category,
		typename TDifferenceType = typename internal::IterableIterator<TIterable>::difference_type,
		typename TConstCategory = typename internal::IterableConstIterator<TIterable>::iterator_category,
		typename TConstDifferenceType = typename internal::IterableConstIterator<TIterable>::difference_type
	>
		class Iterable : public internal::IterableBase<TIterable>
	{

	protected:

		TIterable& iterable() const;

	public:

		using iterator = Iterator<internal::IterableIterator<TIterable>, TDereferenceResult, TDereference, TCategory, TDifferenceType>;
		using const_iterator = Iterator<internal::IterableConstIterator<TIterable>, TDereferenceConstResult, TDereferenceConst, TConstCategory, TConstDifferenceType>;

		Iterable(TIterable& _iterator);

		iterator begin();
		const_iterator cbegin() const;
		const_iterator begin() const;

		iterator end();
		const_iterator cend() const;
		const_iterator end() const;

		iterator rbegin();
		const_iterator crbegin() const;
		const_iterator rbegin() const;

		iterator rend();
		const_iterator crend() const;
		const_iterator rend() const;

	};

}

#define CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterable.tpp>
#undef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION

#endif