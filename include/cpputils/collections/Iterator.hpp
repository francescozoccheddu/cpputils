#ifndef CPPUTILS_COLLECTIONS_ITERATOR_INCLUDED
#define CPPUTILS_COLLECTIONS_ITERATOR_INCLUDED

#include <cpputils/collections/types.hpp>
#include <type_traits>
#include <iterator>

namespace cpputils::collections
{

	template<
		typename TIterator,
		typename TDereferenceResult,
		TDereferenceResult(*)(types::DereferenceResult<TIterator>)
	>
		requires std::input_or_output_iterator<TIterator>
	class Iterator;

	namespace internal
	{

		template<typename TIterator>
		class IteratorBase
		{

		private:

			template<
				typename TIteratorIterator,
				typename TDereferenceResult,
				TDereferenceResult(*)(types::DereferenceResult<TIteratorIterator>)
			>
				requires std::input_or_output_iterator<TIteratorIterator>
			friend class collections::Iterator;

			TIterator m_iterator;

			IteratorBase(const TIterator& _iterator);
			IteratorBase(TIterator&& _iterator);

		public:

			auto operator<=>(const IteratorBase& _other) const = default;

		};

	}

	template<
		typename TIterator,
		typename TDereferenceResult = types::DereferenceResult<TIterator>,
		TDereferenceResult(*TConverter)(types::DereferenceResult<TIterator>) = types::cast<types::DereferenceResult<TIterator>, TDereferenceResult>
	>
		requires std::input_or_output_iterator<TIterator>
	class Iterator : public internal::IteratorBase<TIterator>
	{

	protected:

		TIterator& iterator();
		const TIterator& iterator() const;

	public:

		using value_type = std::remove_reference_t<TDereferenceResult>;
		using reference = TDereferenceResult;
		using pointer = value_type*;
		using difference_type = typename TIterator::difference_type;
		using iterator_category = typename TIterator::iterator_category;

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