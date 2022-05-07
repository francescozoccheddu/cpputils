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

		template <typename TIterable, typename = void>
		struct BeginResultTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable> requires concepts::HasBegin<TIterable>
		struct BeginResultTypeStruct<TIterable, void> final : public mixins::StaticClass { using Type = types::BeginResult<TIterable>; };

		template <typename TIterable, typename = void>
		struct CBeginResultTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable> requires concepts::HasCBegin<TIterable>
		struct CBeginResultTypeStruct<TIterable, void> final : public mixins::StaticClass { using Type = types::CBeginResult<TIterable>; };

		template <typename TIterable, typename = void>
		struct RBeginResultTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable> requires concepts::HasRBegin<TIterable>
		struct RBeginResultTypeStruct<TIterable, void> final : public mixins::StaticClass { using Type = types::RBeginResult<TIterable>; };

		template <typename TIterable, typename = void>
		struct CRBeginResultTypeStruct final : public mixins::StaticClass { using Type = void; };

		template <typename TIterable> requires concepts::HasCRBegin<TIterable>
		struct CRBeginResultTypeStruct<TIterable, void> final : public mixins::StaticClass { using Type = types::CRBeginResult<TIterable>; };

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

		template <typename TIterable, typename... TIterables>
		class ZipIterable final
		{

		private:

			std::tuple<TIterable, TIterables&...> m_iterables;

		public:

			using iterator = ZipIterator<typename BeginResultTypeStruct<TIterable>::Type, typename BeginResultTypeStruct<TIterables>::Type...>;
			using const_iterator = ZipIterator<typename CBeginResultTypeStruct<const TIterable>::Type, typename CBeginResultTypeStruct<const TIterables>::Type...>;
			using reverse_iterator = ZipIterator<typename RBeginResultTypeStruct<TIterable>::Type, typename RBeginResultTypeStruct<TIterables>::Type...>;
			using const_reverse_iterator = ZipIterator<typename CRBeginResultTypeStruct<const TIterable>::Type, typename CRBeginResultTypeStruct<const TIterables>::Type...>;

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