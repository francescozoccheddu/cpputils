#ifndef CPPUTILS_COLLECTIONS_ALGORITHMS_INCLUDED
#define CPPUTILS_COLLECTIONS_ALGORITHMS_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <iterator>
#include <cstddef>

namespace cpputils::collections::algorithms
{

	namespace concepts
	{

		template <typename TFilter, typename TValue>
		concept Filter = std::predicate<TFilter, const TValue&>;

		template <typename TComparer, typename TValue>
		concept Comparer = std::predicate<TComparer, const TValue&, const TValue&>;

		template <typename TFilter, typename TIterator>
		concept IteratorFilter = Filter<TFilter, types::DereferenceResult<TIterator>>;

		template <typename TComparer, typename TIterator>
		concept IteratorComparer = Comparer<TComparer, types::DereferenceResult<TIterator>>;

	}

	namespace defaults
	{

		template <typename TValue>
		constexpr bool truePredicate(const TValue& _value)
		{
			return true;
		}

		template <typename TValue>
		constexpr bool lessThan(const TValue& _a, const TValue& _b)
		{
			return _a < _b;
		}

		template <typename TValue>
		constexpr bool greaterThan(const TValue& _a, const TValue& _b)
		{
			return _a > _b;
		}

		template <typename TIterator>
		constexpr auto iteratorTruePredicate = truePredicate<types::DereferenceResult<TIterator>>;

		template <typename TIterator>
		constexpr auto iteratorLessThan = lessThan<types::DereferenceResult<TIterator>>;

		template <typename TIterator>
		constexpr auto iteratorGreaterThan = greaterThan<types::DereferenceResult<TIterator>>;

	}

	// base

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	TIterator bestIt(TIterator _begin, const TIterator& _end, TComparer _isBetter, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	TIterator minIt(TIterator _begin, const TIterator& _end, TComparer _isLessThan, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	TIterator maxIt(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator firstIt(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator singleIt(TIterator _begin, const TIterator& _end, bool& _multipleMatches, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator singleIt(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	std::size_t count(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	bool any(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	bool all(TIterator _begin, const TIterator& _end, TFilter _filter);

	// without filter

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	TIterator bestIt(TIterator _begin, const TIterator& _end, TComparer _isBetter);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	TIterator minIt(TIterator _begin, const TIterator& _end, TComparer _isLessThan);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	TIterator maxIt(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan);

	template <std::forward_iterator TIterator>
	TIterator firstIt(TIterator _begin, const TIterator& _end);

	template <std::forward_iterator TIterator>
	TIterator singleIt(TIterator _begin, const TIterator& _end, bool& _multipleMatches);

	template <std::forward_iterator TIterator>
	TIterator singleIt(TIterator _begin, const TIterator& _end);

	// without filter and comparer

	template <std::forward_iterator TIterator>
	TIterator minIt(TIterator _begin, const TIterator& _end);

	template <std::forward_iterator TIterator>
	TIterator maxIt(TIterator _begin, const TIterator& _end);

	// without comparer

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator minIt(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator maxIt(TIterator _begin, const TIterator& _end, TFilter _filter);

	// throwing

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TComparer _isBetter, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TComparer _isLessThan, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, bool& _multipleMatches, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TFilter _filter);

	// throwing and without filter

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TComparer _isBetter);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TComparer _isLessThan);

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan);

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end);

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, bool& _multipleMatches);

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end);

	// throwing and without filter and comparer

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end);

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end);

	// throwing and without comparer

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TFilter _filter);

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TFilter _filter);

	// with default value

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isBetter, TFilter _filter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isLessThan, TFilter _filter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isGreaterThan, TFilter _filter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else, bool& _multipleMatches, TFilter _filter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter);

	// with default value and without filter

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isBetter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isLessThan);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isGreaterThan);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end, TElse _else);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else, bool& _multipleMatches);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else);

	// with default value and without filter and comparer

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else);

	// with default value and without comparer

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter);

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter);

}

#define CPPUTILS_COLLECTIONS_ALGORITHMS_IMPLEMENTATION
#include <cpputils-IMPL/collections/algorithms.tpp>
#undef CPPUTILS_COLLECTIONS_ALGORITHMS_IMPLEMENTATION

#endif