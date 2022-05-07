/*
	Inspired by https://committhis.github.io/2020/10/14/zip-iterator.html
	Thanks CommitThis!
	Go check out their page https://committhis.github.io/
*/

#ifndef CPPUTILS_COLLECTIONS_ZIP_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#define CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE template <std::input_or_output_iterator TIterator, std::input_or_output_iterator... TIterators>
#define CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR ZipIterator<TIterator, TIterators...>
#define CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE template <typename TIterable, typename... TIterables>
#define CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE ZipIterable<TIterable, TIterables...>

#include <cpputils/collections/zip.hpp>
#include <utility>

namespace cpputils::collections
{

	namespace internal
	{

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::ZipIterator(TIterator&& _iterator, TIterators&&... _iterators)
			: m_iterators{ std::forward<TIterator>(_iterator), std::forward<TIterators>(_iterators) ... }
		{}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::value_type
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator*() const
		{
			return std::apply([](auto & ... _iterators) {
				return value_type{ *_iterators... };
				}, m_iterators);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::value_type
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator[](difference_type _index) const requires std::random_access_iterator<TIterator>
		{
			return std::apply([&_index](auto & ... _iterators) {
				return value_type{ *(_iterators + _index)... };
				}, m_iterators);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR&
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator++()
		{
			std::apply([](auto & ... _iterators) {
				((++_iterators), ...);
				}, m_iterators);
			return *this;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator++(int)
		{
			ZipIterator clone{ *this };
			std::apply([](auto & ... _iterators) {
				((_iterators++), ...);
				}, clone.m_iterators);
			return clone;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR&
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator+=(difference_type _offset) requires std::random_access_iterator<TIterator>
		{
			std::apply([&_offset](auto & ... _iterators) {
				((_iterators += _offset), ...);
				}, m_iterators);
			return *this;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR&
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator--() requires std::bidirectional_iterator<TIterator>
		{
			std::apply([](auto & ... _iterators) {
				((--_iterators), ...);
				}, m_iterators);
			return *this;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator--(int) requires std::bidirectional_iterator<TIterator>
		{
			ZipIterator clone{ *this };
			std::apply([](auto & ... _iterators) {
				((_iterators--), ...);
				}, clone.m_iterators);
			return clone;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR&
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator-=(difference_type _offset) requires std::random_access_iterator<TIterator>
		{
			std::apply([&_offset](auto & ... _iterators) {
				((_iterators -= _offset), ...);
				}, m_iterators);
			return *this;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator+(difference_type _offset) const requires std::random_access_iterator<TIterator>
		{
			std::apply([&_offset](auto & ... _iterators) {
				((_iterators + _offset), ...);
				}, m_iterators);
			return *this;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator-(difference_type _offset) const requires std::random_access_iterator<TIterator>
		{
			std::apply([&_offset](auto & ... _iterators) {
				((_iterators - _offset), ...);
				}, m_iterators);
			return *this;
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::difference_type
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR::operator-(const ZipIterator& _other) const requires std::random_access_iterator<TIterator>
		{
			return m_iterators[0] - _other.m_iterators[0];
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::ZipIterable(TIterable& _iterable, TIterables&... _iterables)
			: m_iterables{ _iterable, _iterables... }
		{}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::begin()
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::begin(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::begin() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::begin(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::cbegin() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::cbegin(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::end()
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::end(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::end() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::end(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::cend() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::cend(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::rbegin()
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::rbegin(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::rbegin() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::rbegin(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::crbegin() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::crbegin(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::rend()
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::rend(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::rend() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::rend(_iterables)... };
				}, m_iterables);
		}

		CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
			auto CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE::crend() const
		{
			return std::apply([](auto & ... _iterables) {
				return ZipIterator{ std::crend(_iterables)... };
				}, m_iterables);
		}

	}

	CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
		internal::CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE zip(TIterable& _iterable, TIterables&... _iterables)
	{
		return internal::CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE{ _iterable, _iterables... };
	}

}

#undef CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ZIP_ZIPITERATOR
#undef CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ZIP_ZIPITERABLE