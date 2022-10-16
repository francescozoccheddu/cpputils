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
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::operator[](typename iterator::difference_type _index) requires concepts::HasBegin<TIterable>&& std::random_access_iterator<types::BeginResult<TIterable>>
	{
		return *(begin() + _index);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::operator[](typename const_iterator::difference_type _index) const requires concepts::HasBegin<const TIterable>&& std::random_access_iterator<types::BeginResult<const TIterable>>
	{
		return *(begin() + _index);
	}

	// base

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::bestIt(TComparer _isBetter, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::bestIt(begin(), end(), _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::minIt(TComparer _isLessThan, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::minIt(begin(), end(), _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt(TComparer _isGreaterThan, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::maxIt(begin(), end(), _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::firstIt(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::firstIt(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::lastIt(TFilter _filter) requires concepts::HasRBegin<TIterable> { return algorithms::firstIt(rbegin(), rend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt(bool& _multipleMatches, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::singleIt(begin(), end(), _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::singleIt(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::count(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	bool CPPUTILS_COLLECTIONS_ITERABLE::any(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::any(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	bool CPPUTILS_COLLECTIONS_ITERABLE::all(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::all(begin(), end(), _filter); }

	// without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::bestIt(TComparer _isBetter) requires concepts::HasBegin<TIterable> { return algorithms::bestIt(begin(), end(), _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::minIt(TComparer _isLessThan) requires concepts::HasBegin<TIterable> { return algorithms::minIt(begin(), end(), _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt(TComparer _isGreaterThan) requires concepts::HasBegin<TIterable> { return algorithms::maxIt(begin(), end(), _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::firstIt() requires concepts::HasBegin<TIterable> { return algorithms::firstIt(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::lastIt() requires concepts::HasRBegin<TIterable> { return algorithms::firstIt(rbegin(), rend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt(bool& _multipleMatches) requires concepts::HasBegin<TIterable> { return algorithms::singleIt(begin(), end(), _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt() requires concepts::HasBegin<TIterable> { return algorithms::singleIt(begin(), end()); }

	// without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::minIt() requires concepts::HasBegin<TIterable> { return algorithms::minIt(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt() requires concepts::HasBegin<TIterable> { return algorithms::maxIt(begin(), end()); }

	// without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::minIt(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::minIt(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::maxIt(begin(), end(), _filter); }

	// throwing

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::best(TComparer _isBetter, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::best(begin(), end(), _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TComparer _isLessThan, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TComparer _isGreaterThan, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::first(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TFilter _filter) requires concepts::HasRBegin<TIterable> { return algorithms::first(rbegin(), rend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(bool& _multipleMatches, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _filter); }

	// throwing and without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::best(TComparer _isBetter) requires concepts::HasBegin<TIterable> { return algorithms::best(begin(), end(), _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TComparer _isLessThan) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TComparer _isGreaterThan) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first() requires concepts::HasBegin<TIterable> { return algorithms::first(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last() requires concepts::HasRBegin<TIterable> { return algorithms::first(rbegin(), rend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(bool& _multipleMatches) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single() requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end()); }

	// throwing and without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min() requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max() requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end()); }

	// throwing and without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _filter); }

	// with default value

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::best(TElse _else, TComparer _isBetter, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::best(begin(), end(), _else, _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else, TComparer _isLessThan, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _else, _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else, TComparer _isGreaterThan, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _else, _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::first(begin(), end(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TElse _else, TFilter _filter) requires concepts::HasRBegin<TIterable> { return algorithms::first(rbegin(), rend(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else, bool& _multipleMatches, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _else, _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _else, _filter); }

	// with default value and without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::best(TElse _else, TComparer _isBetter) requires concepts::HasBegin<TIterable> { return algorithms::best(begin(), end(), _else, _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else, TComparer _isLessThan) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _else, _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else, TComparer _isGreaterThan) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _else, _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TElse _else) requires concepts::HasBegin<TIterable> { return algorithms::first(begin(), end(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TElse _else) requires concepts::HasRBegin<TIterable> { return algorithms::first(rbegin(), rend(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else, bool& _multipleMatches) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _else, _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else) requires concepts::HasBegin<TIterable> { return algorithms::single(begin(), end(), _else); }

	// with default value and without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _else); }

	// with default value and without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::min(begin(), end(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
	TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable> { return algorithms::max(begin(), end(), _else, _filter); }

	// base

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::bestIt(TComparer _isBetter, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::bestIt(begin(), end(), _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::minIt(TComparer _isLessThan, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::minIt(begin(), end(), _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::maxIt(begin(), end(), _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::firstIt(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::firstIt(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::lastIt(TFilter _filter) const requires concepts::HasRBegin<const TIterable> { return algorithms::firstIt(rbegin(), rend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt(bool& _multipleMatches, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::singleIt(begin(), end(), _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::singleIt(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::count(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	bool CPPUTILS_COLLECTIONS_ITERABLE::any(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::any(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	bool CPPUTILS_COLLECTIONS_ITERABLE::all(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::all(begin(), end(), _filter); }

	// without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::bestIt(TComparer _isBetter) const requires concepts::HasBegin<const TIterable> { return algorithms::bestIt(begin(), end(), _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::minIt(TComparer _isLessThan) const requires concepts::HasBegin<const TIterable> { return algorithms::minIt(begin(), end(), _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt(TComparer _isGreaterThan) const requires concepts::HasBegin<const TIterable> { return algorithms::maxIt(begin(), end(), _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::firstIt() const requires concepts::HasBegin<const TIterable> { return algorithms::firstIt(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::lastIt() const requires concepts::HasRBegin<const TIterable> { return algorithms::firstIt(rbegin(), rend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt(bool& _multipleMatches) const requires concepts::HasBegin<const TIterable> { return algorithms::singleIt(begin(), end(), _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::singleIt() const requires concepts::HasBegin<const TIterable> { return algorithms::singleIt(begin(), end()); }

	// without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::minIt() const requires concepts::HasBegin<const TIterable> { return algorithms::minIt(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt() const requires concepts::HasBegin<const TIterable> { return algorithms::maxIt(begin(), end()); }

	// without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::minIt(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::minIt(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::maxIt(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::maxIt(begin(), end(), _filter); }

	// throwing

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::best(TComparer _isBetter, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::best(begin(), end(), _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TComparer _isLessThan, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::first(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TFilter _filter) const requires concepts::HasRBegin<const TIterable> { return algorithms::first(rbegin(), rend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(bool& _multipleMatches, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _filter); }

	// throwing and without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::best(TComparer _isBetter) const requires concepts::HasBegin<const TIterable> { return algorithms::best(begin(), end(), _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TComparer _isLessThan) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TComparer _isGreaterThan) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first() const requires concepts::HasBegin<const TIterable> { return algorithms::first(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last() const requires concepts::HasRBegin<const TIterable> { return algorithms::first(rbegin(), rend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(bool& _multipleMatches) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single() const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end()); }

	// throwing and without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min() const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max() const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end()); }

	// throwing and without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _filter); }

	// with default value

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::best(TElse _else, TComparer _isBetter, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::best(begin(), end(), _else, _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else, TComparer _isLessThan, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _else, _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else, TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _else, _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::first(begin(), end(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TElse _else, TFilter _filter) const requires concepts::HasRBegin<const TIterable> { return algorithms::first(rbegin(), rend(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else, bool& _multipleMatches, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _else, _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _else, _filter); }

	// with default value and without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::best(TElse _else, TComparer _isBetter) const requires concepts::HasBegin<const TIterable> { return algorithms::best(begin(), end(), _else, _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else, TComparer _isLessThan) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _else, _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else, TComparer _isGreaterThan) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _else, _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TElse _else) const requires concepts::HasBegin<const TIterable> { return algorithms::first(begin(), end(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TElse _else) const requires concepts::HasRBegin<const TIterable> { return algorithms::first(rbegin(), rend(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else, bool& _multipleMatches) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _else, _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TElse _else) const requires concepts::HasBegin<const TIterable> { return algorithms::single(begin(), end(), _else); }

	// with default value and without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _else); }

	// with default value and without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::min(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::min(begin(), end(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::max(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable> { return algorithms::max(begin(), end(), _else, _filter); }

	// base

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cbestIt(TComparer _isBetter, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::bestIt(cbegin(), cend(), _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cminIt(TComparer _isLessThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::minIt(cbegin(), cend(), _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cmaxIt(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::maxIt(cbegin(), cend(), _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cfirstIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::firstIt(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::clastIt(TFilter _filter) const requires concepts::HasCRBegin<const TIterable> { return algorithms::firstIt(crbegin(), crend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::csingleIt(bool& _multipleMatches, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::singleIt(cbegin(), cend(), _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::csingleIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::singleIt(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	std::size_t CPPUTILS_COLLECTIONS_ITERABLE::ccount(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::count(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	bool CPPUTILS_COLLECTIONS_ITERABLE::cany(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::any(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	bool CPPUTILS_COLLECTIONS_ITERABLE::call(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::all(cbegin(), cend(), _filter); }

	// without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cbestIt(TComparer _isBetter) const requires concepts::HasCBegin<const TIterable> { return algorithms::bestIt(cbegin(), cend(), _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cminIt(TComparer _isLessThan) const requires concepts::HasCBegin<const TIterable> { return algorithms::minIt(cbegin(), cend(), _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cmaxIt(TComparer _isGreaterThan) const requires concepts::HasCBegin<const TIterable> { return algorithms::maxIt(cbegin(), cend(), _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::cfirstIt() const requires concepts::HasCBegin<const TIterable> { return algorithms::firstIt(cbegin(), cend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::clastIt() const requires concepts::HasCRBegin<const TIterable> { return algorithms::firstIt(crbegin(), crend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::csingleIt(bool& _multipleMatches) const requires concepts::HasCBegin<const TIterable> { return algorithms::singleIt(cbegin(), cend(), _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::csingleIt() const requires concepts::HasCBegin<const TIterable> { return algorithms::singleIt(cbegin(), cend()); }

	// without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::cminIt() const requires concepts::HasCBegin<const TIterable> { return algorithms::minIt(cbegin(), cend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		auto CPPUTILS_COLLECTIONS_ITERABLE::cmaxIt() const requires concepts::HasCBegin<const TIterable> { return algorithms::maxIt(cbegin(), cend()); }

	// without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cminIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::minIt(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	auto CPPUTILS_COLLECTIONS_ITERABLE::cmaxIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::maxIt(cbegin(), cend(), _filter); }

	// throwing

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cbest(TComparer _isBetter, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::best(cbegin(), cend(), _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TComparer _isLessThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::first(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TFilter _filter) const requires concepts::HasCRBegin<const TIterable> { return algorithms::first(crbegin(), crend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(bool& _multipleMatches, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _filter); }

	// throwing and without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cbest(TComparer _isBetter) const requires concepts::HasCBegin<const TIterable> { return algorithms::best(cbegin(), cend(), _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TComparer _isLessThan) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TComparer _isGreaterThan) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst() const requires concepts::HasCBegin<const TIterable> { return algorithms::first(cbegin(), cend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast() const requires concepts::HasCRBegin<const TIterable> { return algorithms::first(crbegin(), crend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(bool& _multipleMatches) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle() const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend()); }

	// throwing and without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin() const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend()); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax() const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend()); }

	// throwing and without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _filter); }

	// with default value

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cbest(TElse _else, TComparer _isBetter, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::best(cbegin(), cend(), _else, _isBetter, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TElse _else, TComparer _isLessThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _else, _isLessThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TElse _else, TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _else, _isGreaterThan, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::first(cbegin(), cend(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TElse _else, TFilter _filter) const requires concepts::HasCRBegin<const TIterable> { return algorithms::first(crbegin(), crend(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TElse _else, bool& _multipleMatches, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _else, _multipleMatches, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _else, _filter); }

	// with default value and without filter

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cbest(TElse _else, TComparer _isBetter) const requires concepts::HasCBegin<const TIterable> { return algorithms::best(cbegin(), cend(), _else, _isBetter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TElse _else, TComparer _isLessThan) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _else, _isLessThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TElse _else, TComparer _isGreaterThan) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _else, _isGreaterThan); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TElse _else) const requires concepts::HasCBegin<const TIterable> { return algorithms::first(cbegin(), cend(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TElse _else) const requires concepts::HasCRBegin<const TIterable> { return algorithms::first(crbegin(), crend(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TElse _else, bool& _multipleMatches) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _else, _multipleMatches); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TElse _else) const requires concepts::HasCBegin<const TIterable> { return algorithms::single(cbegin(), cend(), _else); }

	// with default value and without filter and comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TElse _else) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _else); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TElse _else) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _else); }

	// with default value and without comparer

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmin(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::min(cbegin(), cend(), _else, _filter); }

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
	TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cmax(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable> { return algorithms::max(cbegin(), cend(), _else, _filter); }

}

#undef CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERABLE