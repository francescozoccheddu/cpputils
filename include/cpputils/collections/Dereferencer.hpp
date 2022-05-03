#ifndef CPPUTILS_COLLECTIONS_DEREFERENCER_INCLUDED
#define CPPUTILS_COLLECTIONS_DEREFERENCER_INCLUDED

#include <cpputils/mixins/StaticClass.hpp>
#include <cpputils/collections/Iterable.hpp>
#include <cpputils/collections/Iterator.hpp>
#include <type_traits>

#define CPPUTILS_COLLECTIONS_DEREFERENCER_TEMPLATE template<typename TClass, typename TView>

#define CPPUTILS_COLLECTIONS_DEREFERENCER_ARGS <TClass, TView>

#define CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINT requires internal::IsValidDereferencer CPPUTILS_COLLECTIONS_DEREFERENCER_ARGS

#define CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINED_TEMPLATE CPPUTILS_COLLECTIONS_DEREFERENCER_TEMPLATE CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINT

#define CPPUTILS_COLLECTIONS_DEREFERENCER Iterable CPPUTILS_COLLECTIONS_DEREFERENCER_ARGS

namespace cpputils::collections
{

	namespace internal
	{
		CPPUTILS_COLLECTIONS_DEREFERENCER_ARGS concept IsValidDereferencer
			= std::is_class_v<TClass> && std::is_class_v<TClass>
			&& (std::is_convertible_v<TClass*, TView*> || std::is_base_of_v<TClass, TView>);

	}

	template<typename TClass, typename TView = TClass> CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINT
	class Dereferencer final : private mixins::StaticClass
	{

	public:

		static TView& dereference(TClass* _pointer);
		static const TView& dereferenceConst(const TClass* _pointer);

		template<typename TIterator, typename TCategory = typename TIterator::iterator_category, typename TDifferenceType = typename TIterator::difference_type> requires internal::IsValidIterator<TIterator, TCategory>
		using Iterator = collections::Iterator<
			TIterator,
			TView&,
			[](const typename TIterator::iterator& _it) -> TView& { return dereference(*_it); },
			TCategory,
			TDifferenceType
		>;

		template<typename TIterator, typename TCategory = typename TIterator::iterator_category, typename TDifferenceType = typename TIterator::difference_type> requires internal::IsValidIterator<TIterator, TCategory>
		using ConstIterator = collections::Iterator<
			TIterator,
			const TView&,
			[](const typename TIterator::const_iterator& _it) -> const TView& { return dereferenceConst(*_it); },
			TCategory,
			TDifferenceType
		>;

		template<typename TIterable, typename TCategory = typename TIterable::iterator::iterator_category, typename TDifferenceType = typename TIterable::iterator::difference_type> requires internal::IsValidIterable<TIterable, TCategory>
		using Iterable = collections::Iterable<
			TIterable,
			TView&,
			[](const typename TIterable::iterator& _it) -> TView& { return dereference(*_it); },
			const TView&,
			[](const typename TIterable::const_iterator& _it) -> const TView& { return dereferenceConst(*_it); },
			TCategory,
			TDifferenceType
		>;

	};

}

#define CPPUTILS_COLLECTIONS_DEREFERENCER_IMPLEMENTATION
#include <cpputils-IMPL/collections/Dereferencer.tpp>
#undef CPPUTILS_COLLECTIONS_DEREFERENCER_IMPLEMENTATION

#undef CPPUTILS_COLLECTIONS_DEREFERENCER_TEMPLATE
#undef CPPUTILS_COLLECTIONS_DEREFERENCER_ARGS
#undef CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINT
#undef CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINED_TEMPLATE
#undef CPPUTILS_COLLECTIONS_DEREFERENCER

#endif