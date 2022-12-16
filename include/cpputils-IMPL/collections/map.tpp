#ifndef CPPUTILS_COLLECTIONS_MAP_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/map.hpp>
#include <iterator>

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TInputIterator, typename TOutputIterator, typename TMapper>
		TInputIterator map(const TInputIterator& _inBegin, const TInputIterator& _inEnd, const TOutputIterator& _outBegin, const TOutputIterator& _outEnd, const TMapper& _mapper)
		{
			auto inIt{ _inBegin }, outIt{ _outBegin };
			while (inIt != _inEnd && outIt != _outEnd)
			{
				*inIt = _mapper(*outIt);
				++inIt;
				++outIt;
			}
			return inIt;
		}

		template<typename TInputIterator, typename TOutputIterator, typename TMapper>
		void map(const TInputIterator& _inBegin, const TInputIterator& _inEnd, const TOutputIterator& _outBegin, const TOutputIterator& _outEnd, const TMapper& _mapper, const MappedFromIterator<TInputIterator, TMapper>& _defaultValue)
		{
			auto inIt{ map(_inBegin, _inEnd, _outBegin, _outEnd, _mapper) };
			while (inIt != _inEnd)
			{
				*inIt = _defaultValue;
				++inIt;
			}
		}

	}

	template<typename TIterable, typename TMapper>
	std::vector<internal::MappedFromIterable<TIterable, TMapper>> map(TIterable& _iterable, const TMapper& _mapper)
	{
		std::vector<internal::MappedFromIterable<TIterable, TMapper>> out(static_cast<std::size_t>(std::size(_iterable)));
		internal::map(out.begin(), out.end(), std::begin(_iterable), std::end(_iterable), _mapper);
		return out;
	}

	template<typename TIterable, typename TMapper>
	std::vector<internal::MappedFromIterable<TIterable, TMapper>> map(const TIterable& _iterable, const TMapper& _mapper)
	{
		std::vector<internal::MappedFromIterable<TIterable, TMapper>> out(static_cast<std::size_t>(std::size(_iterable)));
		internal::map(out.begin(), out.end(), std::begin(_iterable), std::end(_iterable), _mapper);
		return out;
	}

	template<std::size_t TSize, typename TIterable, typename TMapper>
	std::array<internal::MappedFromIterable<TIterable, TMapper>, TSize> fmap(TIterable& _iterable, const TMapper& _mapper, const internal::MappedFromIterable<TIterable, TMapper>& _defaultValue)
	{
		std::array<internal::MappedFromIterable<TIterable, TMapper>, TSize> out;
		internal::map(out.begin(), out.end(), std::begin(_iterable), std::end(_iterable), _mapper, _defaultValue);
		return out;
	}

	template<std::size_t TSize, typename TIterable, typename TMapper>
	std::array<internal::MappedFromIterable<TIterable, TMapper>, TSize> fmap(const TIterable& _iterable, const TMapper& _mapper, const internal::MappedFromIterable<TIterable, TMapper>& _defaultValue)
	{
		std::array<internal::MappedFromIterable<TIterable, TMapper>, TSize> out;
		internal::map(out.begin(), out.end(), std::begin(_iterable), std::end(_iterable), _mapper, _defaultValue);
		return out;
	}

	template<typename TIterable, typename TMapper>
	std::array<internal::MappedFromIterable<TIterable, TMapper>, internal::arraySize<TIterable>> fmap(TIterable& _iterable, const TMapper& _mapper)
	{
		return fmap<internal::arraySize<TIterable>>(_iterable, _mapper);
	}

	template<typename TIterable, typename TMapper>
	std::array<internal::MappedFromIterable<TIterable, TMapper>, internal::arraySize<TIterable>> fmap(const TIterable& _iterable, const TMapper& _mapper)
	{
		return fmap<internal::arraySize<TIterable>>(_iterable, _mapper);
	}

}
