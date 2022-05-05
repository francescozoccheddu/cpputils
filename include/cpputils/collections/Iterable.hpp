#ifndef CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED

#include <cpputils/collections/Iterator.hpp>
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

	namespace algorithms
	{

		template <std::forward_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate>
		bool first(TIterator&& _begin, const TIterator& _end, TIterator& _result, TPredicate&& _predicate);

		template <std::forward_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate>
		std::size_t single(TIterator&& _begin, const TIterator& _end, TIterator& _result, TPredicate&& _predicate);

		template <std::forward_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate>
		std::size_t count(TIterator&& _begin, const TIterator& _end, TPredicate&& _predicate);

		template <std::forward_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate>
		bool any(TIterator&& _begin, const TIterator& _end, TPredicate&& _predicate);

		template <std::forward_iterator TIterator, std::predicate<const types::DereferenceResult<TIterator>&> TPredicate>
		bool all(TIterator&& _begin, const TIterator& _end, TPredicate&& _predicate);

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

		static constexpr bool truePredicate(const TDereferenceResult&) { return true; }
		static constexpr bool truePredicateConst(const TDereferenceConstResult&) { return true; }

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

		TDereferenceResult first() requires concepts::HasBegin<TIterable>;
		TDereferenceConstResult cfirst() const requires concepts::HasCBegin<TIterable>;
		TDereferenceConstResult first() const requires concepts::HasBegin<const TIterable>;

		TDereferenceResult last() requires concepts::HasRBegin<TIterable>;
		TDereferenceConstResult clast() const requires concepts::HasCRBegin<TIterable>;
		TDereferenceConstResult last() const requires concepts::HasRBegin<const TIterable>;

		TDereferenceResult single() requires concepts::HasBegin<TIterable>;
		TDereferenceConstResult csingle() const requires concepts::HasCBegin<TIterable>;
		TDereferenceConstResult single() const requires concepts::HasBegin<const TIterable>;

		template<std::constructible_from<TDereferenceResult> TElse>
		TDereferenceResult first(TElse _else) requires concepts::HasBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse>
		TDereferenceConstResult cfirst(TElse _else) const requires concepts::HasCBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse>
		TDereferenceConstResult first(TElse _else) const requires concepts::HasBegin<const TIterable>;

		template<std::constructible_from<TDereferenceResult> TElse>
		TDereferenceResult last(TElse _else) requires concepts::HasRBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse>
		TDereferenceConstResult clast(TElse _else) const requires concepts::HasCRBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse>
		TDereferenceConstResult last(TElse _else) const requires concepts::HasRBegin<const TIterable>;

		template<std::constructible_from<TDereferenceResult> TElse>
		TDereferenceResult single(TElse _else, bool _throwIfNoMatch=false, bool _throwIfMultipleMatches=false) requires concepts::HasBegin<TIterable>;
		
		template<std::constructible_from<TDereferenceConstResult> TElse>
		TDereferenceConstResult csingle(TElse _else, bool _throwIfNoMatch = false, bool _throwIfMultipleMatches = false) const requires concepts::HasCBegin<TIterable>;
		
		template<std::constructible_from<TDereferenceConstResult> TElse>
		TDereferenceConstResult single(TElse _else, bool _throwIfNoMatch = false, bool _throwIfMultipleMatches = false) const requires concepts::HasBegin<const TIterable>;

		std::size_t count() requires concepts::HasBegin<TIterable>;
		std::size_t ccount() const requires concepts::HasCBegin<TIterable>;
		std::size_t count() const requires concepts::HasCBegin<TIterable>;

		bool any() requires concepts::HasBegin<TIterable>;
		bool cany() const requires concepts::HasCBegin<TIterable>;
		bool any() const requires concepts::HasBegin<const TIterable>;

		bool all() requires concepts::HasBegin<TIterable>;
		bool call() const requires concepts::HasCBegin<TIterable>;
		bool all() const requires concepts::HasBegin<const TIterable>;

		template<std::predicate<const TDereferenceResult&> TPredicate>
		TDereferenceResult first(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult cfirst(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult first(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>;

		template<std::predicate<const TDereferenceResult&> TPredicate>
		TDereferenceResult last(TPredicate&& _predicate) requires concepts::HasRBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult clast(TPredicate&& _predicate) const requires concepts::HasCRBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult last(TPredicate&& _predicate) const requires concepts::HasRBegin<const TIterable>;

		template<std::predicate<const TDereferenceResult&> TPredicate>
		TDereferenceResult single(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult csingle(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult single(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>;

		template<std::constructible_from<TDereferenceResult> TElse, std::predicate<const TDereferenceResult&> TPredicate>
		TDereferenceResult first(TElse _else, TPredicate&& _predicate) requires concepts::HasBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse, std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult cfirst(TElse _else, TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse, std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult first(TElse _else, TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>;

		template<std::constructible_from<TDereferenceResult> TElse, std::predicate<const TDereferenceResult&> TPredicate>
		TDereferenceResult last(TElse _else, TPredicate&& _predicate) requires concepts::HasRBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse, std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult clast(TElse _else, TPredicate&& _predicate) const requires concepts::HasCRBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse, std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult last(TElse _else, TPredicate&& _predicate) const requires concepts::HasRBegin<const TIterable>;

		template<std::constructible_from<TDereferenceResult> TElse, std::predicate<const TDereferenceResult&> TPredicate>
		TDereferenceResult single(TElse _else, TPredicate&& _predicate, bool _throwIfNoMatch = false, bool _throwIfMultipleMatches = false) requires concepts::HasBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse, std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult csingle(TElse _else, TPredicate&& _predicate, bool _throwIfNoMatch = false, bool _throwIfMultipleMatches = false) const requires concepts::HasCBegin<TIterable>;

		template<std::constructible_from<TDereferenceConstResult> TElse, std::predicate<const TDereferenceConstResult&> TPredicate>
		TDereferenceConstResult single(TElse _else, TPredicate&& _predicate, bool _throwIfNoMatch = false, bool _throwIfMultipleMatches = false) const requires concepts::HasBegin<const TIterable>;

		template<std::predicate<const TDereferenceResult&> TPredicate>
		std::size_t count(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		std::size_t ccount(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		std::size_t count(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::predicate<const TDereferenceResult&> TPredicate>
		bool any(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		bool cany(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		bool any(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>;

		template<std::predicate<const TDereferenceResult&> TPredicate>
		bool all(TPredicate&& _predicate) requires concepts::HasBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		bool call(TPredicate&& _predicate) const requires concepts::HasCBegin<TIterable>;

		template<std::predicate<const TDereferenceConstResult&> TPredicate>
		bool all(TPredicate&& _predicate) const requires concepts::HasBegin<const TIterable>;

	};

}

#define CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterable.tpp>
#undef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION

#endif