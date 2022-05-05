#ifndef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterable.hpp>

#include <memory>
#include <utility>
#include <stdexcept>
#include <iterator>

#define CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE \
template <\
	typename TIterable,\
	typename TDereferenceResult,\
	typename TDereferenceConstResult,\
	TDereferenceResult(*TConvert)(types::DereferenceResult<types::BeginResult<TIterable>>),\
	TDereferenceConstResult(*TConvertConst)(types::DereferenceResult<types::BeginResult<const TIterable>>)\
>

#define CPPUTILS_COLLECTIONS_ITERABLE \
Iterable<TIterable, TDereferenceResult, TDereferenceConstResult, TConvert, TConvertConst>

namespace cpputils::collections
{

	namespace algorithms
	{

		template <std::input_or_output_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate >
		bool first(TIterator&& _begin, const TIterator& _end, TIterator& _result, TPredicate&& _predicate)
		{
			TIterator it{ _begin };
			_result = _end;
			while (it != _end)
			{
				if (_predicate(*it))
				{
					_result = it;
					return true;
				}
				++it;
			}
			return false;
		}

		template <std::input_or_output_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate >
		std::size_t single(TIterator&& _begin, const TIterator& _end, TIterator& _result, TPredicate&& _predicate)
		{
			TIterator it{ _begin };
			_result = _end;
			bool found{ false };
			while (it != _end)
			{
				if (_predicate(*it))
				{
					if (found)
					{
						return 2;
					}
					_result = it;
					found = true;
				}
				++it;
			}
			if (found)
			{
				return 1;
			}
			return 0;
		}

		template <std::input_or_output_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate >
		std::size_t count(TIterator&& _begin, const TIterator& _end, TPredicate&& _predicate)
		{
			TIterator it{ _begin };
			std::size_t count{ 0 };
			while (it != _end)
			{
				count += _predicate(*it);
				++it;
			}
			return count;
		}

		template <std::input_or_output_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate >
		bool any(TIterator&& _begin, const TIterator& _end, TPredicate&& _predicate)
		{
			TIterator it{ _begin };
			while (it != _end)
			{
				if (_predicate(*it))
				{
					return true;
				}
				++it;
			}
			return false;
		}

		template <std::input_or_output_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate >
		bool all(TIterator&& _begin, const TIterator& _end, TPredicate&& _predicate)
		{
			TIterator it{ _begin };
			while (it != _end)
			{
				if (!_predicate(*it))
				{
					return false;
				}
				++it;
			}
			return true;
		}

	}

	namespace internal
	{

		template <typename TIterable>
		internal::IterableBase<TIterable>::IterableBase(TIterable& _iterable)
			: m_iterable{ std::addressof(_iterable) }
		{}

	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::Iterable(TIterable& _iterable)
		: internal::IterableBase<TIterable>{ _iterable }
	{}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TIterable&
		CPPUTILS_COLLECTIONS_ITERABLE::iterable()
	{
		return *internal::IterableBase<TIterable>::m_iterable;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		const TIterable&
		CPPUTILS_COLLECTIONS_ITERABLE::iterable() const
	{
		return *internal::IterableBase<TIterable>::m_iterable;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::begin() requires concepts::HasBegin<TIterable>
	{
		return Iterator<decltype(iterable().begin()), TDereferenceResult, TConvert>{ iterable().begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::cbegin() const requires concepts::HasCBegin<TIterable>
	{
		return Iterator<decltype(iterable().cbegin()), TDereferenceConstResult, TConvertConst>{ iterable().cbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::begin() const requires concepts::HasBegin<const TIterable>
	{
		return Iterator<decltype(iterable().begin()), TDereferenceConstResult, TConvertConst>{ iterable().begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::end() requires concepts::HasBegin<TIterable>
	{
		return Iterator<decltype(iterable().end()), TDereferenceResult, TConvert>{ iterable().end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::cend() const requires concepts::HasCBegin<TIterable>
	{
		return Iterator<decltype(iterable().cend()), TDereferenceConstResult, TConvertConst>{ iterable().cend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::end() const requires concepts::HasBegin<const TIterable>
	{
		return Iterator<decltype(iterable().end()), TDereferenceConstResult, TConvertConst>{ iterable().end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::rbegin() requires concepts::HasRBegin<TIterable>
	{
		return Iterator<decltype(iterable().rbegin()), TDereferenceResult, TConvert>{ iterable().rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::crbegin() const requires concepts::HasCRBegin<TIterable>
	{
		return Iterator<decltype(iterable().crbegin()), TDereferenceConstResult, TConvertConst>{ iterable().crbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::rbegin() const requires concepts::HasRBegin<const TIterable>
	{
		return Iterator<decltype(iterable().rbegin()), TDereferenceConstResult, TConvertConst>{ iterable().rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::rend() requires concepts::HasRBegin<TIterable>
	{
		return Iterator<decltype(iterable().rend()), TDereferenceResult, TConvert>{ iterable().rend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::crend() const requires concepts::HasCRBegin<TIterable>
	{
		return Iterator<decltype(iterable().crend()), TDereferenceConstResult, TConvertConst>{ iterable().crend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::rend() const requires concepts::HasRBegin<const TIterable>
	{
		return Iterator<decltype(iterable().rend()), TDereferenceConstResult, TConvertConst>{ iterable().rend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::size() const requires concepts::HasSize<const TIterable>
	{
		return std::size(iterable());
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::empty() const requires concepts::HasEmpty<const TIterable>
	{
		return std::empty(iterable());
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::operator[](iterator::difference_type _index) requires concepts::HasBegin<TIterable>&& std::random_access_iterator<types::BeginResult<TIterable>>
	{
		return *(begin() + _index);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::operator[](const_iterator::difference_type _index) const requires concepts::HasBegin<const TIterable>&& std::random_access_iterator<types::BeginResult<const TIterable>>
	{
		return *(begin() + _index);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first() requires concepts::HasBegin<TIterable>
	{
		return first(truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst() const requires concepts::HasCBegin<TIterable>
	{
		return cfirst(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first() const requires concepts::HasBegin<const TIterable>
	{
		return first(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last() requires concepts::HasRBegin<TIterable>
	{
		return last(truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast() const requires concepts::HasCRBegin<TIterable>
	{
		return clast(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last() const requires concepts::HasRBegin<const TIterable>
	{
		return last(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single() requires concepts::HasBegin<TIterable>
	{
		return single(truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle() const requires concepts::HasCBegin<TIterable>
	{
		return csingle(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single() const requires concepts::HasBegin<const TIterable>
	{
		return single(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TDereferenceResult _else) requires concepts::HasBegin<TIterable>
	{
		return first(_else, truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TDereferenceConstResult _else) const requires concepts::HasCBegin<TIterable>
	{
		return cfirst(_else, truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TDereferenceConstResult _else) const requires concepts::HasBegin<const TIterable>
	{
		return first(_else, truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TDereferenceResult _else) requires concepts::HasRBegin<TIterable>
	{
		return last(_else, truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TDereferenceConstResult _else) const requires concepts::HasCRBegin<TIterable>
	{
		return clast(_else, truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TDereferenceConstResult _else) const requires concepts::HasRBegin<const TIterable>
	{
		return last(_else, truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TDereferenceResult _else, bool _throwIfNoMatch, bool _throwIfMultipleMatches) requires concepts::HasBegin<TIterable>
	{
		return single(_else, truePredicate, _throwIfNoMatch, _throwIfMultipleMatches);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TDereferenceConstResult _else, bool _throwIfNoMatch, bool _throwIfMultipleMatches) const requires concepts::HasCBegin<TIterable>
	{
		return csingle(_else, truePredicateConst, _throwIfNoMatch, _throwIfMultipleMatches);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TDereferenceConstResult _else, bool _throwIfNoMatch, bool _throwIfMultipleMatches) const requires concepts::HasBegin<const TIterable>
	{
		return single(_else, truePredicateConst, _throwIfNoMatch, _throwIfMultipleMatches);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count() requires concepts::HasBegin<TIterable>
	{
		return count(truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::ccount() const requires concepts::HasCBegin<TIterable>
	{
		return ccount(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count() const requires concepts::HasCBegin<TIterable>
	{
		return count(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::any() requires concepts::HasBegin<TIterable>
	{
		return any(truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::cany() const requires concepts::HasCBegin<TIterable>
	{
		return cany(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::any() const requires concepts::HasBegin<const TIterable>
	{
		return any(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::all() requires concepts::HasBegin<TIterable>
	{
		return all(truePredicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::call() const requires concepts::HasCBegin<TIterable>
	{
		return call(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::all() const requires concepts::HasBegin<const TIterable>
	{
		return all(truePredicateConst);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>
	{
		auto it{ end() };
		return algorithms::first(begin(), end(), it, _predicate) ? std::forward<TDereferenceResult>(*it) : throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		auto it{ cend() };
		return algorithms::first(cbegin(), cend(), it, _predicate) ? std::forward<TDereferenceConstResult>(*it) : throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>
	{
		auto it{ end() };
		return algorithms::first(begin(), end(), it, _predicate) ? std::forward<TDereferenceConstResult>(*it) : throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TPredicate&& _predicate) requires concepts::HasRBegin<TIterable>
	{
		auto it{ rend() };
		return algorithms::first(rbegin(), rend(), it, _predicate) ? std::forward<TDereferenceResult>(*it) : throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TPredicate&& _predicate) const requires concepts::HasCRBegin<TIterable>
	{
		auto it{ crend() };
		return algorithms::first(crbegin(), crend(), it, _predicate) ? std::forward<TDereferenceConstResult>(*it) : throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TPredicate&& _predicate) const requires concepts::HasRBegin<const TIterable>
	{
		auto it{ rend() };
		return algorithms::first(rbegin(), rend(), it, _predicate) ? std::forward<TDereferenceConstResult>(*it) : throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>
	{
		auto it{ end() };
		switch (algorithms::single(begin(), end(), it, std::forward<TPredicate>(_predicate)))
		{
			case 0:
				throw std::logic_error{ "no match" };
			case 1:
				return std::forward<TDereferenceResult>(*it);
			default:
				throw std::logic_error{ "multiple matches" };
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		auto it{ cend() };
		switch (algorithms::single(cbegin(), cend(), it, std::forward<TPredicate>(_predicate)))
		{
			case 0:
				throw std::logic_error{ "no match" };
			case 1:
				return std::forward<TDereferenceConstResult>(*it);
			default:
				throw std::logic_error{ "multiple matches" };
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>
	{
		auto it{ end() };
		switch (algorithms::single(begin(), end(), it, std::forward<TPredicate>(_predicate)))
		{
			case 0:
				throw std::logic_error{ "no match" };
			case 1:
				return std::forward<TDereferenceConstResult>(*it);
			default:
				throw std::logic_error{ "multiple matches" };
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TDereferenceResult _else, TPredicate&& _predicate) requires concepts::HasBegin<TIterable>
	{
		auto it{ end() };
		return algorithms::first(begin(), end(), it, _predicate) ? std::forward<TDereferenceResult>(*it) : std::forward<TDereferenceResult>(_else);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TDereferenceConstResult _else, TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		auto it{ cend() };
		return algorithms::first(cbegin(), cend(), it, _predicate) ? std::forward<TDereferenceResult>(*it) : std::forward<TDereferenceResult>(_else);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TDereferenceConstResult _else, TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>
	{
		auto it{ end() };
		return algorithms::first(begin(), end(), it, _predicate) ? std::forward<TDereferenceResult>(*it) : std::forward<TDereferenceResult>(_else);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TDereferenceResult _else, TPredicate&& _predicate) requires concepts::HasRBegin<TIterable>
	{
		auto it{ end() };
		return algorithms::first(rbegin(), rend(), it, _predicate) ? std::forward<TDereferenceResult>(*it) : std::forward<TDereferenceResult>(_else);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TDereferenceConstResult _else, TPredicate&& _predicate) const requires concepts::HasCRBegin<TIterable>
	{
		auto it{ end() };
		return algorithms::first(crbegin(), crend(), it, _predicate) ? std::forward<TDereferenceConstResult>(*it) : std::forward<TDereferenceConstResult>(_else);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TDereferenceConstResult _else, TPredicate&& _predicate) const requires concepts::HasRBegin<const TIterable>
	{
		auto it{ end() };
		return algorithms::first(rbegin(), rend(), it, _predicate) ? std::forward<TDereferenceConstResult>(*it) : std::forward<TDereferenceConstResult>(_else);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TDereferenceResult _else, TPredicate&& _predicate, bool _throwIfNoMatch, bool _throwIfMultipleMatches) requires concepts::HasBegin<TIterable>
	{
		auto it{ end() };
		switch (algorithms::single(begin(), end(), it, std::forward<TPredicate>(_predicate)))
		{
			case 0:
				return _throwIfNoMatch ? throw std::logic_error{ "no match" } : std::forward<TDereferenceResult>(_else);
			case 1:
				return std::forward<TDereferenceResult>(*it);
			default:
				return _throwIfMultipleMatches ? throw std::logic_error{ "multiple matches" } : std::forward<TDereferenceResult>(_else);
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TDereferenceConstResult _else, TPredicate&& _predicate, bool _throwIfNoMatch, bool _throwIfMultipleMatches) const requires concepts::HasCBegin<TIterable>
	{
		auto it{ cend() };
		switch (algorithms::single(cbegin(), cend(), it, std::forward<TPredicate>(_predicate)))
		{
			case 0:
				return _throwIfNoMatch ? throw std::logic_error{ "no match" } : std::forward<TDereferenceConstResult>(_else);
			case 1:
				return std::forward<TDereferenceConstResult>(*it);
			default:
				return _throwIfMultipleMatches ? throw std::logic_error{ "multiple matches" } : std::forward<TDereferenceConstResult>(_else);
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TDereferenceConstResult _else, TPredicate&& _predicate, bool _throwIfNoMatch, bool _throwIfMultipleMatches) const requires concepts::HasBegin<const TIterable>
	{
		auto it{ end() };
		switch (algorithms::single(begin(), end(), it, std::forward<TPredicate>(_predicate)))
		{
			case 0:
				return _throwIfNoMatch ? throw std::logic_error{ "no match" } : std::forward<TDereferenceConstResult>(_else);
			case 1:
				return std::forward<TDereferenceConstResult>(*it);
			default:
				return _throwIfMultipleMatches ? throw std::logic_error{ "multiple matches" } : std::forward<TDereferenceConstResult>(_else);
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>
	{
		return algorithms::count(begin(), end(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	std::size_t CPPUTILS_COLLECTIONS_ITERABLE::ccount(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		return algorithms::count(cbegin(), cend(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		return algorithms::count(begin(), end(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	bool CPPUTILS_COLLECTIONS_ITERABLE::any(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>
	{
		return algorithms::any(begin(), end(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	bool CPPUTILS_COLLECTIONS_ITERABLE::cany(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		return algorithms::any(cbegin(), cend(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	bool CPPUTILS_COLLECTIONS_ITERABLE::any(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>
	{
		return algorithms::any(begin(), end(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceResult&> TPredicate>
	bool CPPUTILS_COLLECTIONS_ITERABLE::all(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>
	{
		return algorithms::all(begin(), end(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	bool CPPUTILS_COLLECTIONS_ITERABLE::call(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>
	{
		return algorithms::all(begin(), end(), std::forward<TPredicate>(_predicate));
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template<std::predicate<const TDereferenceConstResult&> TPredicate>
	bool CPPUTILS_COLLECTIONS_ITERABLE::all(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>
	{
		return algorithms::all(begin(), end(), std::forward<TPredicate>(_predicate));
	}

}

#undef CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERABLE