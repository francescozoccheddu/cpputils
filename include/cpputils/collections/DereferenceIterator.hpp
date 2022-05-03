#ifndef CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCEITERATOR_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <type_traits>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TIterator, typename TView, typename TCategory> concept IsValidUnsafeDereferenceIterator
			= std::is_class_v<TIterator>
			&& std::is_pointer_v<typename TIterator::value_type>
			&& (std::is_const_v<TView> || (!std::is_const_v<std::remove_pointer_t<typename TIterator::value_type>>))
			&& IsValidIterator<TIterator, TCategory>;

		template<typename TIterator, typename TView, typename TCategory> concept IsValidDereferenceIterator
			= IsValidUnsafeDereferenceIterator<TIterator, TView, TCategory>
			&& (std::is_convertible_v<typename TIterator::value_type, TView*> || std::is_base_of_v<std::remove_pointer_t<typename TIterator::value_type>, TView>);

		template<
			typename TIterator,
			typename TView = std::remove_pointer_t<typename TIterator::value_type>,
			typename TCategory = TIterator::iterator_category,
			typename TDifferenceType = TIterator::difference_type
		>
			requires IsValidUnsafeDereferenceIterator<TIterator, TView, TCategory>
		using UnsafeDereferenceIterator = collections::Iterator <
			TIterator,
			TView&,
			[](const TIterator& _it) -> TView& { return *reinterpret_cast<TView*>(*_it); },
			TCategory,
			TDifferenceType
		> ;

	}

	template<
		typename TIterator,
		typename TView = std::remove_pointer_t<typename TIterator::value_type>,
		typename TCategory = TIterator::iterator_category,
		typename TDifferenceType = TIterator::difference_type
	>
		requires internal::IsValidDereferenceIterator<TIterator, TView, TCategory>
	using DereferenceIterator = internal::UnsafeDereferenceIterator<TIterator, TView, TCategory, TDifferenceType>;

}

#endif