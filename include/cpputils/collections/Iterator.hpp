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
		pointer operator->() const;
		reference operator[](difference_type _offset) const;

		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator+=(difference_type _offset);

		Iterator& operator--();
		Iterator operator--(int);
		Iterator& operator-=(difference_type _offset);

		Iterator operator+(difference_type _other) const;
		Iterator operator-(difference_type _other) const;

		difference_type operator-(const Iterator& _other) const;

	};

}

#define CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION
#include <cpputils-IMPL/collections/Iterator.tpp>
#undef CPPUTILS_COLLECTIONS_ITERATOR_IMPLEMENTATION

#endif