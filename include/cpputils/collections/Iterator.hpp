#ifndef CPPUTILS_COLLECTIONS_ITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERATOR_INCLUDED

#include <cpputils/mixins/StaticClass.hpp>
#include <type_traits>
#include <iterator>
#include <utility>

namespace cpputils::collections
{

	namespace types
	{

		template <typename TFrom, typename TTo>
		inline constexpr TTo cast(TFrom _from);

		namespace internal
		{

			template <typename TIterator, typename = void>
			struct CategoryStruct final : public mixins::StaticClass { using Type = std::random_access_iterator_tag; };

			template <typename TIterator>
			struct CategoryStruct<TIterator, std::void_t<typename TIterator::iterator_category>> final : public mixins::StaticClass { using Type = typename TIterator::iterator_category; };

		}

		template <typename TIterator>
		using DereferenceResult = decltype(*std::declval<TIterator&>());

		template <typename TIterator>
		using Category = typename internal::CategoryStruct<TIterator>::Type;

	}

	template <
		std::input_or_output_iterator TIterator,
		typename TDereferenceResult,
		TDereferenceResult(*)(types::DereferenceResult<const TIterator>)
	>
		class Iterator;

	namespace internal
	{

		template <std::input_or_output_iterator TIterator>
		class IteratorBase
		{

		private:

			template <
				std::input_or_output_iterator TIteratorIterator,
				typename TDereferenceResult,
				TDereferenceResult(*)(types::DereferenceResult<const TIteratorIterator>)
			>
				friend class collections::Iterator;

			TIterator m_iterator;

			IteratorBase() = default;
			IteratorBase(const TIterator& _iterator);
			IteratorBase(TIterator&& _iterator);

		public:

			auto operator<=>(const IteratorBase& _other) const = default;

		};

	}

	template <
		std::input_or_output_iterator TIterator,
		typename TDereferenceResult = types::DereferenceResult<const TIterator>,
		TDereferenceResult(*TConvert)(types::DereferenceResult<const TIterator>) = types::cast<types::DereferenceResult<const TIterator>, TDereferenceResult>
	>
		class Iterator : public internal::IteratorBase<TIterator>
	{

	protected:

		TIterator& iterator();
		const TIterator& iterator() const;

	public:

		using value_type = std::remove_reference_t<TDereferenceResult>;
		using reference = TDereferenceResult;
		using pointer = value_type*;
		using difference_type = std::iter_difference_t<TIterator>;
		using iterator_category = types::Category<TIterator>;

		Iterator() = default;
		Iterator(const TIterator& _iterator);
		Iterator(TIterator&& _iterator);

		reference operator*() const;
		pointer operator->() const requires std::is_reference_v<TDereferenceResult>;
		reference operator[](difference_type _offset) const requires std::random_access_iterator<TIterator>;

		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator+=(difference_type _offset) requires std::random_access_iterator<TIterator>;

		Iterator& operator--() requires std::bidirectional_iterator<TIterator>;
		Iterator operator--(int) requires std::bidirectional_iterator<TIterator>;
		Iterator& operator-=(difference_type _offset) requires std::random_access_iterator<TIterator>;

		Iterator operator+(difference_type _other) const requires std::random_access_iterator<TIterator>;
		Iterator operator-(difference_type _other) const requires std::random_access_iterator<TIterator>;

		difference_type operator-(const Iterator& _other) const requires std::random_access_iterator<TIterator>;

	};

}

#define CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterator.tpp>
#undef CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION

#endif