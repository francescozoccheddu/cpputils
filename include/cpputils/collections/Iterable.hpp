#ifndef CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED

#include <cpputils/collections/Iterator.hpp>
#include <cpputils/collections/algorithms.hpp>
#include <type_traits>
#include <iterator>
#include <cstddef>
#include <concepts>

namespace cpputils::collections
{

	namespace concepts
	{

		template <typename TIterable>
		concept HasBegin = requires (TIterable & _iterable) { std::begin(_iterable); };

		template <typename TIterable>
		concept HasCBegin = requires (TIterable & _iterable) { std::cbegin(_iterable); };

		template <typename TIterable>
		concept HasRBegin = requires (TIterable & _iterable) { std::rbegin(_iterable); };

		template <typename TIterable>
		concept HasCRBegin = requires (TIterable & _iterable) { std::crbegin(_iterable); };

		template <typename TIterable>
		concept HasSize = requires (TIterable & _iterable) { std::size(_iterable); };

		template <typename TIterable>
		concept HasEmpty = requires (TIterable & _iterable) { std::empty(_iterable); };

	}

	namespace types
	{

		template <typename TIterator>
		using BeginResult = decltype(std::begin(std::declval<TIterator&>()));

		template <typename TIterator>
		using CBeginResult = decltype(std::cbegin(std::declval<TIterator&>()));

		template <typename TIterator>
		using RBeginResult = decltype(std::rbegin(std::declval<TIterator&>()));

		template <typename TIterator>
		using CRBeginResult = decltype(std::crbegin(std::declval<TIterator&>()));

		template <typename TIterator>
		using SizeResult = decltype(std::size(std::declval<TIterator&>()));

		template <typename TIterator>
		using EmptyResult = decltype(std::empty(std::declval<TIterator&>()));

	}

	namespace internal
	{

		template <typename TIterable, typename TDereferenceResult, auto TConvert, typename = void>
		struct BeginIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert> requires concepts::HasBegin<TIterable>
		struct BeginIteratorTypeStruct<TIterable, TDereferenceResult, TConvert, void> final : public mixins::StaticClass { using Type = Iterator<types::BeginResult<TIterable>, TDereferenceResult, TConvert>; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert, typename = void>
		struct CBeginIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert> requires concepts::HasCBegin<TIterable>
		struct CBeginIteratorTypeStruct<TIterable, TDereferenceResult, TConvert, void> final : public mixins::StaticClass { using Type = Iterator<types::CBeginResult<TIterable>, TDereferenceResult, TConvert>; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert, typename = void>
		struct RBeginIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert> requires concepts::HasRBegin<TIterable>
		struct RBeginIteratorTypeStruct<TIterable, TDereferenceResult, TConvert, void> final : public mixins::StaticClass { using Type = Iterator<types::RBeginResult<TIterable>, TDereferenceResult, TConvert>; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert, typename = void>
		struct CRBeginIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename TDereferenceResult, auto TConvert> requires concepts::HasCRBegin<TIterable>
		struct CRBeginIteratorTypeStruct<TIterable, TDereferenceResult, TConvert, void> final : public mixins::StaticClass { using Type = Iterator<types::CRBeginResult<TIterable>, TDereferenceResult, TConvert>; };

	}

	template <
		typename TIterable,
		typename TDereferenceResult,
		typename TDereferenceConstResult,
		TDereferenceResult(*)(types::DereferenceResult<types::BeginResult<TIterable>>),
		TDereferenceConstResult(*)(types::DereferenceResult<types::BeginResult<const TIterable>>)
	>
		class Iterable;

	namespace internal
	{
		template <typename TIterable>
		class IterableBase
		{

		private:

			template <
				typename TIterableIterable,
				typename TDereferenceResult,
				typename TDereferenceConstResult,
				TDereferenceResult(*)(types::DereferenceResult<types::BeginResult<TIterableIterable>>),
				TDereferenceConstResult(*)(types::DereferenceResult<types::BeginResult<const TIterableIterable>>)
			>
				friend class collections::Iterable;

			TIterable* m_iterable;

			IterableBase(TIterable& _iterator);

		public:

			bool operator==(const IterableBase& _other) const = default;
			bool operator!=(const IterableBase& _other) const = default;

		};

	}
	template <
		typename TIterable,
		typename TDereferenceResult = std::iter_value_t<types::BeginResult<TIterable>>&,
		typename TDereferenceConstResult = std::iter_value_t<types::BeginResult<const TIterable>>&,
		TDereferenceResult(*TConvert)(types::DereferenceResult<types::BeginResult<TIterable>>) = types::cast<types::DereferenceResult<types::BeginResult<TIterable>>, TDereferenceResult>,
		TDereferenceConstResult(*TConvertConst)(types::DereferenceResult<types::BeginResult<const TIterable>>) = types::cast<types::DereferenceResult<types::BeginResult<const TIterable>>, TDereferenceConstResult>
	>
		class Iterable : public internal::IterableBase<TIterable>
	{

	public:

		using iterator = typename internal::BeginIteratorTypeStruct<TIterable, TDereferenceResult, TConvert>::Type;
		using const_iterator = typename internal::CBeginIteratorTypeStruct<const TIterable, TDereferenceConstResult, TConvertConst>::Type;
		using reverse_iterator = typename internal::RBeginIteratorTypeStruct<TIterable, TDereferenceResult, TConvert>::Type;
		using const_reverse_iterator = typename internal::CRBeginIteratorTypeStruct<const TIterable, TDereferenceConstResult, TConvertConst>::Type;

	protected:

		TIterable& iterable();
		const TIterable& iterable() const;

	public:

		Iterable(TIterable& _iterator);

		auto begin() requires concepts::HasBegin<TIterable>;
		auto cbegin() const requires concepts::HasCBegin<TIterable>;
		auto begin() const requires concepts::HasBegin<const TIterable>;

		auto end() requires concepts::HasBegin<TIterable>;
		auto cend() const requires concepts::HasCBegin<TIterable>;
		auto end() const requires concepts::HasBegin<const TIterable>;

		auto rbegin() requires concepts::HasRBegin<TIterable>;
		auto crbegin() const requires concepts::HasCRBegin<TIterable>;
		auto rbegin() const requires concepts::HasRBegin<const TIterable>;

		auto rend() requires concepts::HasRBegin<TIterable>;
		auto crend() const requires concepts::HasCRBegin<TIterable>;
		auto rend() const requires concepts::HasRBegin<const TIterable>;

		auto size() const requires concepts::HasSize<const TIterable>;
		auto empty() const requires concepts::HasEmpty<const TIterable>;

		TDereferenceResult operator[](iterator::difference_type _index) requires concepts::HasBegin<TIterable>&& std::random_access_iterator<types::BeginResult<TIterable>>;
		TDereferenceConstResult operator[](const_iterator::difference_type _index) const requires concepts::HasBegin<const TIterable>&& std::random_access_iterator<types::BeginResult<const TIterable>>;

		// base

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto bestIt(TComparer _isBetter, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto minIt(TComparer _isLessThan, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto maxIt(TComparer _isGreaterThan, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto firstIt(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto lastIt(TFilter _filter) requires concepts::HasRBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto singleIt(bool& _multipleMatches, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto singleIt(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		std::size_t count(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		bool any(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		bool all(TFilter _filter) requires concepts::HasBegin<TIterable>;

		// without filter

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		auto bestIt(TComparer _isBetter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		auto minIt(TComparer _isLessThan) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		auto maxIt(TComparer _isGreaterThan) requires concepts::HasBegin<TIterable>;

		auto firstIt() requires concepts::HasBegin<TIterable>;

		auto lastIt() requires concepts::HasRBegin<TIterable>;

		auto singleIt(bool& _multipleMatches) requires concepts::HasBegin<TIterable>;

		auto singleIt() requires concepts::HasBegin<TIterable>;

		// without filter and comparer

		auto minIt() requires concepts::HasBegin<TIterable>;

		auto maxIt() requires concepts::HasBegin<TIterable>;

		// without comparer

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto minIt(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		auto maxIt(TFilter _filter) requires concepts::HasBegin<TIterable>;

		// throwing

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult best(TComparer _isBetter, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult min(TComparer _isLessThan, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult max(TComparer _isGreaterThan, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult first(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult last(TFilter _filter) requires concepts::HasRBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult single(bool& _multipleMatches, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult single(TFilter _filter) requires concepts::HasBegin<TIterable>;

		// throwing and without filter

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		TDereferenceResult best(TComparer _isBetter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		TDereferenceResult min(TComparer _isLessThan) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		TDereferenceResult max(TComparer _isGreaterThan) requires concepts::HasBegin<TIterable>;

		TDereferenceResult first() requires concepts::HasBegin<TIterable>;

		TDereferenceResult last() requires concepts::HasRBegin<TIterable>;

		TDereferenceResult single(bool& _multipleMatches) requires concepts::HasBegin<TIterable>;

		TDereferenceResult single() requires concepts::HasBegin<TIterable>;

		// throwing and without filter and comparer

		TDereferenceResult min() requires concepts::HasBegin<TIterable>;

		TDereferenceResult max() requires concepts::HasBegin<TIterable>;

		// throwing and without comparer

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult min(TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult max(TFilter _filter) requires concepts::HasBegin<TIterable>;

		// with default value

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult best(TElse _else, TComparer _isBetter, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult min(TElse _else, TComparer _isLessThan, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult max(TElse _else, TComparer _isGreaterThan, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult first(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult last(TElse _else, TFilter _filter) requires concepts::HasRBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult single(TElse _else, bool& _multipleMatches, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult single(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable>;

		// with default value and without filter

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		TDereferenceResult best(TElse _else, TComparer _isBetter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		TDereferenceResult min(TElse _else, TComparer _isLessThan) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Comparer<TDereferenceResult> TComparer>
		TDereferenceResult max(TElse _else, TComparer _isGreaterThan) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse>
		TDereferenceResult first(TElse _else) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse>
		TDereferenceResult last(TElse _else) requires concepts::HasRBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse>
		TDereferenceResult single(TElse _else, bool& _multipleMatches) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse>
		TDereferenceResult single(TElse _else) requires concepts::HasBegin<TIterable>;

		// with default value and without filter and comparer

		template <std::convertible_to<TDereferenceResult> TElse>
		TDereferenceResult min(TElse _else) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse>
		TDereferenceResult max(TElse _else) requires concepts::HasBegin<TIterable>;

		// with default value and without comparer

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult min(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable>;

		template <std::convertible_to<TDereferenceResult> TElse, algorithms::concepts::Filter<TDereferenceResult> TFilter>
		TDereferenceResult max(TElse _else, TFilter _filter) requires concepts::HasBegin<TIterable>;

		// base

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto bestIt(TComparer _isBetter, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto minIt(TComparer _isLessThan, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto maxIt(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto firstIt(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto lastIt(TFilter _filter) const requires concepts::HasRBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto singleIt(bool& _multipleMatches, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto singleIt(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		std::size_t count(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		bool any(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		bool all(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		// without filter

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		auto bestIt(TComparer _isBetter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		auto minIt(TComparer _isLessThan) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		auto maxIt(TComparer _isGreaterThan) const requires concepts::HasBegin<const TIterable>;

		auto firstIt() const requires concepts::HasBegin<const TIterable>;

		auto lastIt() const requires concepts::HasRBegin<const TIterable>;

		auto singleIt(bool& _multipleMatches) const requires concepts::HasBegin<const TIterable>;

		auto singleIt() const requires concepts::HasBegin<const TIterable>;

		// without filter and comparer

		auto minIt() const requires concepts::HasBegin<const TIterable>;

		auto maxIt() const requires concepts::HasBegin<const TIterable>;

		// without comparer

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto minIt(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto maxIt(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		// throwing

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult best(TComparer _isBetter, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult min(TComparer _isLessThan, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult max(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult first(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult last(TFilter _filter) const requires concepts::HasRBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult single(bool& _multipleMatches, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult single(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		// throwing and without filter

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult best(TComparer _isBetter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult min(TComparer _isLessThan) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult max(TComparer _isGreaterThan) const requires concepts::HasBegin<const TIterable>;

		TDereferenceConstResult first() const requires concepts::HasBegin<const TIterable>;

		TDereferenceConstResult last() const requires concepts::HasRBegin<const TIterable>;

		TDereferenceConstResult single(bool& _multipleMatches) const requires concepts::HasBegin<const TIterable>;

		TDereferenceConstResult single() const requires concepts::HasBegin<const TIterable>;

		// throwing and without filter and comparer

		TDereferenceConstResult min() const requires concepts::HasBegin<const TIterable>;

		TDereferenceConstResult max() const requires concepts::HasBegin<const TIterable>;

		// throwing and without comparer

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult min(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult max(TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		// with default value

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult best(TElse _else, TComparer _isBetter, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult min(TElse _else, TComparer _isLessThan, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult max(TElse _else, TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult first(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult last(TElse _else, TFilter _filter) const requires concepts::HasRBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult single(TElse _else, bool& _multipleMatches, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult single(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		// with default value and without filter

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult best(TElse _else, TComparer _isBetter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult min(TElse _else, TComparer _isLessThan) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult max(TElse _else, TComparer _isGreaterThan) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult first(TElse _else) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult last(TElse _else) const requires concepts::HasRBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult single(TElse _else, bool& _multipleMatches) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult single(TElse _else) const requires concepts::HasBegin<const TIterable>;

		// with default value and without filter and comparer

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult min(TElse _else) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult max(TElse _else) const requires concepts::HasBegin<const TIterable>;

		// with default value and without comparer

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult min(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult max(TElse _else, TFilter _filter) const requires concepts::HasBegin<const TIterable>;

		// base

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto cbestIt(TComparer _isBetter, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto cminIt(TComparer _isLessThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto cmaxIt(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto cfirstIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto clastIt(TFilter _filter) const requires concepts::HasCRBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto csingleIt(bool& _multipleMatches, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto csingleIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		std::size_t ccount(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		bool cany(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		bool call(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		// without filter

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		auto cbestIt(TComparer _isBetter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		auto cminIt(TComparer _isLessThan) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		auto cmaxIt(TComparer _isGreaterThan) const requires concepts::HasCBegin<const TIterable>;

		auto cfirstIt() const requires concepts::HasCBegin<const TIterable>;

		auto clastIt() const requires concepts::HasCRBegin<const TIterable>;

		auto csingleIt(bool& _multipleMatches) const requires concepts::HasCBegin<const TIterable>;

		auto csingleIt() const requires concepts::HasCBegin<const TIterable>;

		// without filter and comparer

		auto cminIt() const requires concepts::HasCBegin<const TIterable>;

		auto cmaxIt() const requires concepts::HasCBegin<const TIterable>;

		// without comparer

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto cminIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		auto cmaxIt(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		// throwing

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cbest(TComparer _isBetter, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmin(TComparer _isLessThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmax(TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cfirst(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult clast(TFilter _filter) const requires concepts::HasCRBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult csingle(bool& _multipleMatches, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult csingle(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		// throwing and without filter

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult cbest(TComparer _isBetter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult cmin(TComparer _isLessThan) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult cmax(TComparer _isGreaterThan) const requires concepts::HasCBegin<const TIterable>;

		TDereferenceConstResult cfirst() const requires concepts::HasCBegin<const TIterable>;

		TDereferenceConstResult clast() const requires concepts::HasCRBegin<const TIterable>;

		TDereferenceConstResult csingle(bool& _multipleMatches) const requires concepts::HasCBegin<const TIterable>;

		TDereferenceConstResult csingle() const requires concepts::HasCBegin<const TIterable>;

		// throwing and without filter and comparer

		TDereferenceConstResult cmin() const requires concepts::HasCBegin<const TIterable>;

		TDereferenceConstResult cmax() const requires concepts::HasCBegin<const TIterable>;

		// throwing and without comparer

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmin(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmax(TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		// with default value

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cbest(TElse _else, TComparer _isBetter, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmin(TElse _else, TComparer _isLessThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmax(TElse _else, TComparer _isGreaterThan, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cfirst(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult clast(TElse _else, TFilter _filter) const requires concepts::HasCRBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult csingle(TElse _else, bool& _multipleMatches, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult csingle(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		// with default value and without filter

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult cbest(TElse _else, TComparer _isBetter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult cmin(TElse _else, TComparer _isLessThan) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Comparer<TDereferenceConstResult> TComparer>
		TDereferenceConstResult cmax(TElse _else, TComparer _isGreaterThan) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult cfirst(TElse _else) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult clast(TElse _else) const requires concepts::HasCRBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult csingle(TElse _else, bool& _multipleMatches) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult csingle(TElse _else) const requires concepts::HasCBegin<const TIterable>;

		// with default value and without filter and comparer

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult cmin(TElse _else) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse>
		TDereferenceConstResult cmax(TElse _else) const requires concepts::HasCBegin<const TIterable>;

		// with default value and without comparer

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmin(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

		template <std::convertible_to<TDereferenceConstResult> TElse, algorithms::concepts::Filter<TDereferenceConstResult> TFilter>
		TDereferenceConstResult cmax(TElse _else, TFilter _filter) const requires concepts::HasCBegin<const TIterable>;

	};

}

#define CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterable.tpp>
#undef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION

#endif