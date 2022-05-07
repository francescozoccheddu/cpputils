#ifndef CPPUTILS_COLLECTIONS_ALGORITHMS_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/algorithms.hpp>
#include <functional>
#include <stdexcept>

namespace cpputils::collections::algorithms
{

	// base

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	TIterator bestIt(TIterator _begin, const TIterator& _end, TComparer _isBetter, TFilter _filter)
	{
		TIterator it{ _begin };
		TIterator best = _end;
		while (it != _end)
		{
			if (_filter(*it))
			{
				if (best == _end || _isBetter(*it, *best))
				{
					best = it;
				}
			}
			++it;
		}
		return best;
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	TIterator minIt(TIterator _begin, const TIterator& _end, TComparer _isLessThan, TFilter _filter)
	{
		return bestIt(_begin, _end, _isLessThan, _filter);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	TIterator maxIt(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan, TFilter _filter)
	{
		return bestIt(_begin, _end, _isGreaterThan, _filter);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator firstIt(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		TIterator it{ _begin };
		while (it != _end)
		{
			if (_filter(*it))
			{
				break;
			}
			++it;
		}
		return it;
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator singleIt(TIterator _begin, const TIterator& _end, bool& _multipleMatches, TFilter _filter)
	{
		TIterator it{ _begin };
		_multipleMatches = false;
		TIterator single = _end;
		while (it != _end)
		{
			if (_filter(*it))
			{
				if (single != _end)
				{
					_multipleMatches = true;
					return _end;
				}
				single = it;
			}
			++it;
		}
		return single;
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator singleIt(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		bool multipleMatches;
		return singleIt(_begin, _end, multipleMatches, _filter);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	std::size_t count(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		TIterator it{ _begin };
		std::size_t count{ 0 };
		while (it != _end)
		{
			count += _filter(*it);
			++it;
		}
		return count;
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	bool any(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return firstIt(_begin, _end, _filter) != _end;
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	bool all(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return firstIt(_begin, _end, std::not_fn(_filter)) == _end;
	}

	// without filter

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	TIterator bestIt(TIterator _begin, const TIterator& _end, TComparer _isBetter)
	{
		return bestIt(_begin, _end, _isBetter, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	TIterator minIt(TIterator _begin, const TIterator& _end, TComparer _isLessThan)
	{
		return minIt(_begin, _end, _isLessThan, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	TIterator maxIt(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan)
	{
		return maxIt(_begin, _end, _isGreaterThan, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	TIterator firstIt(TIterator _begin, const TIterator& _end)
	{
		return firstIt(_begin, _end, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	TIterator singleIt(TIterator _begin, const TIterator& _end, bool& _multipleMatches)
	{
		return singleIt(_begin, _end, _multipleMatches, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	TIterator singleIt(TIterator _begin, const TIterator& _end)
	{
		return singleIt(_begin, _end, defaults::iteratorTruePredicate<TIterator>);
	}

	// without filter and comparer

	template <std::forward_iterator TIterator>
	TIterator minIt(TIterator _begin, const TIterator& _end)
	{
		return minIt(_begin, _end, defaults::iteratorLessThan<TIterator>);
	}

	template <std::forward_iterator TIterator>
	TIterator maxIt(TIterator _begin, const TIterator& _end)
	{
		return maxIt(_begin, _end, defaults::iteratorGreaterThan<TIterator>);
	}

	// without comparer

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator minIt(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return minIt(_begin, _end, defaults::iteratorLessThan<TIterator>, _filter);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	TIterator maxIt(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return maxIt(_begin, _end, defaults::iteratorGreaterThan<TIterator>, _filter);
	}

	// throwing

	namespace internal
	{
		
		template <std::forward_iterator TIterator>
		types::DereferenceResult<TIterator> throwIfNoMatch(TIterator _result, TIterator _end)
		{
			return _result == _end ? throw std::logic_error{ "no match" } : *_result;
		}

	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TComparer _isBetter, TFilter _filter)
	{
		return internal::throwIfNoMatch(bestIt(_begin, _end, _isBetter, _filter), _end);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TComparer _isLessThan, TFilter _filter)
	{
		return internal::throwIfNoMatch(minIt(_begin, _end, _isLessThan, _filter), _end);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan, TFilter _filter)
	{
		return internal::throwIfNoMatch(maxIt(_begin, _end, _isGreaterThan, _filter), _end);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return internal::throwIfNoMatch(firstIt(_begin, _end, _filter), _end);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, bool& _multipleMatches, TFilter _filter)
	{
		return internal::throwIfNoMatch(singleIt(_begin, _end, _multipleMatches, _filter), _end);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return internal::throwIfNoMatch(singleIt(_begin, _end, _filter), _end);
	}

	// throwing and without filter

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TComparer _isBetter)
	{
		return best(_begin, _end, _isBetter, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TComparer _isLessThan)
	{
		return min(_begin, _end, _isLessThan, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TComparer _isGreaterThan)
	{
		return max(_begin, _end, _isGreaterThan, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end)
	{
		return first(_begin, _end, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, bool& _multipleMatches)
	{
		return single(_begin, _end, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end)
	{
		return single(_begin, _end, defaults::iteratorTruePredicate<TIterator>);
	}

	// throwing and without filter and comparer

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end)
	{
		return min(_begin, _end, defaults::iteratorLessThan<TIterator>, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end)
	{
		return max(_begin, _end, defaults::iteratorGreaterThan<TIterator>, defaults::iteratorTruePredicate<TIterator>);
	}

	// throwing and without comparer

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return min(_begin, _end, defaults::iteratorLessThan<TIterator>, _filter);
	}

	template <std::forward_iterator TIterator, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TFilter _filter)
	{
		return min(_begin, _end, defaults::iteratorLessThan<TIterator>, _filter);
	}

	// with default value

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isBetter, TFilter _filter)
	{
		TIterator result = bestIt(_begin, _end, _isBetter, _filter);
		return result != _end ? *result : _else;
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isLessThan, TFilter _filter)
	{
		TIterator result = minIt(_begin, _end, _isLessThan, _filter);
		return result != _end ? *result : _else;
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isGreaterThan, TFilter _filter)
	{
		TIterator result = maxIt(_begin, _end, _isGreaterThan, _filter);
		return result != _end ? *result : _else;
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter)
	{
		TIterator result = firstIt(_begin, _end, _filter);
		return result != _end ? *result : _else;
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else, bool& _multipleMatches, TFilter _filter)
	{
		TIterator result = singleIt(_begin, _end, _multipleMatches, _filter);
		return result != _end ? *result : _else;
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter)
	{
		TIterator result = singleIt(_begin, _end, _filter);
		return result != _end ? *result : _else;
	}

	// with default value and without filter

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> best(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isBetter)
	{
		return best(_begin, _end, _else, _isBetter, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isLessThan)
	{
		return min(_begin, _end, _else, _isLessThan, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorComparer<TIterator> TComparer>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else, TComparer _isGreaterThan)
	{
		return max(_begin, _end, _else, _isGreaterThan, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> first(TIterator _begin, const TIterator& _end, TElse _else)
	{
		return first(_begin, _end, _else, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else, bool& _multipleMatches)
	{
		return single(_begin, _end, _else, _multipleMatches, defaults::iteratorTruePredicate<TIterator>);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> single(TIterator _begin, const TIterator& _end, TElse _else)
	{
		return single(_begin, _end, _else, defaults::iteratorTruePredicate<TIterator>);
	}

	// with default value and without filter and comparer

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else)
	{
		return min(_begin, _end, _else, defaults::iteratorLessThan<TIterator>);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else)
	{
		return max(_begin, _end, _else, defaults::iteratorGreaterThan<TIterator>);
	}

	// with default value and without comparer

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> min(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter)
	{
		return min(_begin, _end, _else, defaults::iteratorLessThan<TIterator>, _filter);
	}

	template <std::forward_iterator TIterator, std::convertible_to<types::DereferenceResult<TIterator>> TElse, concepts::IteratorFilter<TIterator> TFilter>
	types::DereferenceResult<TIterator> max(TIterator _begin, const TIterator& _end, TElse _else, TFilter _filter)
	{
		return max(_begin, _end, _else, defaults::iteratorGreaterThan<TIterator>, _filter);
	}

}
