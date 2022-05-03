#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERABLE_INCLUDED

#include <cpputils/collections/DereferenceIterator.hpp>
#include <cpputils/collections/Iterable.hpp>
#include <type_traits>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterable, typename TView, bool TPassConst, typename TCategory, typename TConstCategory> concept IsValidDereferenceIterable
			= std::is_class_v<TIterable>
			&& IsValidDereferenceIterator<internal::TIterableIterator<TIterable>, TView, TCategory>
			&& IsValidDereferenceIterator<typename TIterable::const_iterator, std::conditional_t<TPassConst, const TView, TView>, TConstCategory>;

	}

	template<
		typename TIterable,
		typename TView = std::remove_pointer_t<typename internal::TIterableIterator<TIterable>::value_type>,
		bool TPassConst = true,
		typename TCategory = typename TIterable::iterator::iterator_category,
		typename TDifferenceType = typename TIterable::iterator::difference_type,
		typename TConstCategory = typename TIterable::const_iterator::iterator_category,
		typename TConstDifferenceType = typename TIterable::const_iterator::difference_type
	>
		requires internal::IsValidDereferenceIterable<TIterable, TView, TPassConst, TCategory, TConstCategory>
	using DereferenceIterable = collections::Iterable <
		TIterable,
		TView&,
		[](const internal::TIterableIterator<TIterable>& _it) -> TView& { return *reinterpret_cast<TView*>(*_it); },
		std::conditional_t<TPassConst, const TView, TView>&,
		[](const typename TIterable::const_iterator& _it) -> std::conditional_t<TPassConst, const TView, TView>& { return *reinterpret_cast<std::conditional_t<TPassConst, const TView, TView>*>(*_it); },
		TCategory,
		TDifferenceType,
		TConstCategory,
		TConstDifferenceType
	> ;

}

#endif