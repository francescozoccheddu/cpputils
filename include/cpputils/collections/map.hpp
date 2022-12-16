#ifndef CPPUTILS_COLLECTIONS_MAP_INCLUDED
#define CPPUTILS_COLLECTIONS_MAP_INCLUDED

#include <cpputils/mixins/StaticClass.hpp>
#include <cpputils/collections/Iterable.hpp>
#include <type_traits>
#include <vector>
#include <array>

namespace cpputils::collections
{

    namespace internal
    {

        class DynamicSize final: public mixins::StaticClass {};

        template<typename TValue, typename TMapper>
        using MappedFromValue = std::invoke_result_t<TMapper, TValue&>;

        template<typename TIterator, typename TMapper>
        using MappedFromIterator = MappedFromValue<types::DereferenceResult<TIterator>, TMapper>;

        template<typename TIterable, typename TMapper>
        using MappedFromIterable = MappedFromIterator<types::BeginResult<TIterable>, TMapper>;

        template<typename TIterable>
        inline constexpr std::size_t arraySize = std::conditional_t<std::is_array_v<TIterable>, std::extent<TIterable>, std::tuple_size<TIterable>>::value;

        template<typename TInputIterator, typename TOutputIterator, typename TMapper>
        TInputIterator map(const TInputIterator& _inBegin, const TInputIterator& _inEnd, const TOutputIterator& _outBegin, const TOutputIterator& _outEnd, const TMapper& _mapper);

        template<typename TInputIterator, typename TOutputIterator, typename TMapper>
        void map(const TInputIterator& _inBegin, const TInputIterator& _inEnd, const TOutputIterator& _outBegin, const TOutputIterator& _outEnd, const TMapper& _mapper, const MappedFromIterator<TInputIterator, TMapper>& _defaultValue);

    }

    template<typename TIterable, typename TMapper>
    std::vector<internal::MappedFromIterable<TIterable, TMapper>> map(TIterable& _iterable, const TMapper& _mapper);

    template<typename TIterable, typename TMapper>
    std::vector<internal::MappedFromIterable<TIterable, TMapper>> map(const TIterable& _iterable, const TMapper& _mapper);

    template<std::size_t TSize, typename TIterable, typename TMapper>
    std::array<internal::MappedFromIterable<TIterable, TMapper>, TSize> fmap(TIterable& _iterable, const TMapper& _mapper, const internal::MappedFromIterable<TIterable, TMapper>& _defaultValue = {});

    template<std::size_t TSize, typename TIterable, typename TMapper>
    std::array<internal::MappedFromIterable<TIterable, TMapper>, TSize> fmap(const TIterable& _iterable, const TMapper& _mapper, const internal::MappedFromIterable<TIterable, TMapper>& _defaultValue = {});

    template<typename TIterable, typename TMapper>
    std::array<internal::MappedFromIterable<TIterable, TMapper>, internal::arraySize<TIterable>> fmap(TIterable& _iterable, const TMapper& _mapper);

    template<typename TIterable, typename TMapper>
    std::array<internal::MappedFromIterable<TIterable, TMapper>, internal::arraySize<TIterable>> fmap(const TIterable& _iterable, const TMapper& _mapper);

}

#define CPPUTILS_COLLECTIONS_MAP_IMPLEMENTATION
#include <cpputils-IMPL/collections/map.tpp>
#undef CPPUTILS_COLLECTIONS_MAP_IMPLEMENTATION

#endif