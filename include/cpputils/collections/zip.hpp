/*
	Inspired by https://committhis.github.io/2020/10/14/zip-iterator.html
	Thanks CommitThis!
	Go check out their page https://committhis.github.io/
*/

#ifndef CPPUTILS_COLLECTIONS_ZIP_INCLUDED
#define CPPUTILS_COLLECTIONS_ZIP_INCLUDED

#include <cpputils/mixins/StaticClass.hpp>
#include <cpputils/collections/Iterator.hpp>
#include <cpputils/collections/Iterable.hpp>
#include <tuple>
#include <iterator>

namespace cpputils::collections
{

	namespace internal
	{

		template <std::input_or_output_iterator TIterator, std::input_or_output_iterator... TIterators>
		class ZipIterator final
		{

		private:

			std::tuple<TIterator, TIterators...> m_iterators;

		public:

			using iterator_category = types::Category<TIterator>;
			using difference_type = std::iter_difference_t<TIterator>;
			using value_type = std::tuple<types::DereferenceResult<TIterator>, types::DereferenceResult<TIterators>...>;
			using reference = value_type&;
			using pointer = value_type*;

			ZipIterator(TIterator&& _iterator, TIterators &&... _iterators);

			value_type operator*() const;
			value_type operator[](difference_type _offset) const requires std::random_access_iterator<TIterator>;

			ZipIterator& operator++();
			ZipIterator operator++(int);
			ZipIterator& operator+=(difference_type _offset) requires std::random_access_iterator<TIterator>;

			ZipIterator& operator--() requires std::bidirectional_iterator<TIterator>;
			ZipIterator operator--(int) requires std::bidirectional_iterator<TIterator>;
			ZipIterator& operator-=(difference_type _offset) requires std::random_access_iterator<TIterator>;

			ZipIterator operator+(difference_type _other) const requires std::random_access_iterator<TIterator>;
			ZipIterator operator-(difference_type _other) const requires std::random_access_iterator<TIterator>;

			difference_type operator-(const ZipIterator& _other) const requires std::random_access_iterator<TIterator>;

			friend auto operator<=> (const ZipIterator& _a, const ZipIterator& _b) = default;

		};

		template <typename TIterable, typename TIterables, typename = void>
		struct BeginZipIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename... TIterables> requires concepts::HasBegin<TIterable>
		struct BeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...>, void> final : public mixins::StaticClass { using Type = ZipIterator<types::BeginResult<TIterable>, types::BeginResult<TIterables>...>; };

		template <typename TIterable, typename TIterables, typename = void>
		struct CBeginZipIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename... TIterables> requires concepts::HasCBegin<TIterable>
		struct CBeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...>, void> final : public mixins::StaticClass { using Type = ZipIterator<types::CBeginResult<TIterable>, types::BeginResult<TIterables>...>; };

		template <typename TIterable, typename TIterables, typename = void>
		struct RBeginZipIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename... TIterables> requires concepts::HasRBegin<TIterable>
		struct RBeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...>, void> final : public mixins::StaticClass { using Type = ZipIterator<types::RBeginResult<TIterable>, types::BeginResult<TIterables>...>; };

		template <typename TIterable, typename TIterables, typename = void>
		struct CRBeginZipIteratorTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable, typename... TIterables> requires concepts::HasCRBegin<TIterable>
		struct CRBeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...>, void> final : public mixins::StaticClass { using Type = ZipIterator<types::CRBeginResult<TIterable>, types::BeginResult<TIterables>...>; };

		template <typename TIterable, typename... TIterables>
		class ZipIterable final
		{

		private:

			std::tuple<TIterable&, TIterables&...> m_iterables;

		public:

			using iterator = typename BeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...> >::Type;
			using const_iterator = typename CBeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...> >::Type;
			using reverse_iterator = typename RBeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...> >::Type;
			using const_reverse_iterator = typename CRBeginZipIteratorTypeStruct<TIterable, std::tuple<TIterables...>>::Type;

			ZipIterable(TIterable& _iterable, TIterables&... _iterables);

			auto begin();
			auto begin() const;
			auto cbegin() const;
			auto end();
			auto end() const;
			auto cend() const;

			auto rbegin();
			auto rbegin() const;
			auto crbegin() const;
			auto rend();
			auto rend() const;
			auto crend() const;

		};

	}

	template <typename TIterable, typename... TIterables>
	internal::ZipIterable<TIterable, TIterables...> zip(TIterable& _iterable, TIterables&... _iterables);

}

#define CPPUTILS_COLLECTIONS_ZIP_IMPLEMENTATION
#include <cpputils-IMPL/collections/zip.tpp>
#undef CPPUTILS_COLLECTIONS_ZIP_IMPLEMENTATION

#endif