#ifndef CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERABLE_INCLUDED

#include <cpputils/collections/types.hpp>
#include <cpputils/collections/Iterator.hpp>
#include <type_traits>
#include <iterator>
#include <functional>
#include <cstddef>

namespace cpputils::collections
{

	template<
		typename TIterable,
		typename TDereferenceResult,
		typename TDereferenceConstResult,
		TDereferenceResult(*)(types::DereferenceResult<types::Iterator<TIterable>>),
		TDereferenceConstResult(*)(types::DereferenceResult<types::ConstIterator<TIterable>>)
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
				typename TDereferenceConstResult,
				TDereferenceResult(*)(types::DereferenceResult<types::Iterator<TIterableIterable>>),
				TDereferenceConstResult(*)(types::DereferenceResult<types::ConstIterator<TIterableIterable>>)
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
		typename TDereferenceResult = typename types::Iterator<TIterable>::value_type&,
		typename TDereferenceConstResult = typename types::ConstIterator<TIterable>::value_type&,
		TDereferenceResult(*TConvert)(types::DereferenceResult<types::Iterator<TIterable>>) = types::cast<types::DereferenceResult<types::Iterator<TIterable>>, TDereferenceResult>,
		TDereferenceConstResult(*TConvertConst)(types::DereferenceResult<types::ConstIterator<TIterable>>) = types::cast<types::DereferenceResult<types::ConstIterator<TIterable>>, TDereferenceConstResult>
	>
		class Iterable : public internal::IterableBase<TIterable>
	{

	public:

		using Predicate = std::function<bool(const TDereferenceResult&)>;
		using PredicateConst = std::function<bool(const TDereferenceConstResult&)>;

		using iterator = Iterator<types::Iterator<TIterable>, TDereferenceResult, TConvert>;
		using const_iterator = Iterator<types::ConstIterator<TIterable>, TDereferenceConstResult, TConvertConst>;
		using reverse_iterator = Iterator<typename types::ReverseIterator<TIterable>, TDereferenceResult, TConvert>;
		using const_reverse_iterator = Iterator<typename types::ConstReverseIterator<TIterable>, TDereferenceConstResult, TConvertConst>;

	private:

		bool tryFirst(iterator& _result, const Predicate& _predicate);
		bool tryCFirst(const_iterator& _result, const PredicateConst& _predicate) const;
		bool tryLast(reverse_iterator& _result, const Predicate& _predicate);
		bool tryCLast(const_reverse_iterator& _result, const PredicateConst& _predicate) const;
		std::size_t trySingle(iterator& _result, const Predicate& _predicate);
		std::size_t tryCSingle(const_iterator& _result, const PredicateConst& _predicate) const;

	protected:

		TIterable& iterable() const;

	public:

		static const Predicate truePredicate;
		static const PredicateConst truePredicateConst;

		Iterable(TIterable& _iterator);

		iterator begin();
		const_iterator cbegin() const;
		const_iterator begin() const;

		iterator end();
		const_iterator cend() const;
		const_iterator end() const;

		reverse_iterator rbegin();
		const_reverse_iterator crbegin() const;
		const_reverse_iterator rbegin() const;

		reverse_iterator rend();
		const_reverse_iterator crend() const;
		const_reverse_iterator rend() const;

		auto size() const;
		bool empty() const;

		TDereferenceResult operator[](iterator::difference_type _index);
		TDereferenceConstResult operator[](const_iterator::difference_type _index) const;

		TDereferenceResult first(const Predicate& _predicate = truePredicate);
		TDereferenceConstResult cfirst(const PredicateConst& _predicate = truePredicateConst) const;
		TDereferenceConstResult first(const PredicateConst& _predicate = truePredicateConst) const;

		TDereferenceResult last(const Predicate& _predicate = truePredicate);
		TDereferenceConstResult clast(const PredicateConst& _predicate = truePredicateConst) const;
		TDereferenceConstResult last(const PredicateConst& _predicate = truePredicateConst) const;

		TDereferenceResult single(const Predicate& _predicate = truePredicate);
		TDereferenceConstResult csingle(const PredicateConst& _predicate = truePredicateConst) const;
		TDereferenceConstResult single(const PredicateConst& _predicate = truePredicateConst) const;

		TDereferenceResult first(TDereferenceResult&& _else, const Predicate& _predicate = truePredicate);
		TDereferenceConstResult cfirst(TDereferenceConstResult&& _else, const PredicateConst& _predicate = truePredicateConst) const;
		TDereferenceConstResult first(TDereferenceConstResult&& _else, const PredicateConst& _predicate = truePredicateConst) const;

		TDereferenceResult last(TDereferenceResult&& _else, const Predicate& _predicate = truePredicate);
		TDereferenceConstResult clast(TDereferenceConstResult&& _else, const PredicateConst& _predicate = truePredicateConst) const;
		TDereferenceConstResult last(TDereferenceConstResult&& _else, const PredicateConst& _predicate = truePredicateConst) const;

		TDereferenceResult single(TDereferenceResult&& _else, const Predicate& _predicate = truePredicate);
		TDereferenceConstResult csingle(TDereferenceConstResult&& _else, const PredicateConst& _predicate = truePredicateConst) const;
		TDereferenceConstResult single(TDereferenceConstResult&& _else, const PredicateConst& _predicate = truePredicateConst) const;

		std::size_t count(const Predicate& _predicate);
		std::size_t count(const PredicateConst& _predicate) const;

		bool any(const Predicate& _predicate);
		bool any(const PredicateConst& _predicate) const;

		bool all(const Predicate& _predicate);
		bool all(const PredicateConst& _predicate) const;

	};

}

#define CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterable.tpp>
#undef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION

#endif