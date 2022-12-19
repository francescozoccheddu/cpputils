#pragma once

#include <cpputils/range/Range.hpp>
#include <type_traits>

#define CPPUTILS_RANGE_RANGED_BODY\
    public:\
        using ALIAS(URange) = Range<ITERATOR, TCompTimeSize>;\
        using ALIAS(Iterator) = typename ALIAS(URange)::Iterator;\
        using ALIAS(Value) = typename ALIAS(URange)::Value;\
        using ALIAS(Reference) = typename ALIAS(URange)::Reference;\
    protected:\
        virtual ALIAS(URange) range() CONST = 0;\
    public:\
        auto begin() CONST { return range().begin();}\
        auto end() CONST { return range().end();}\
        auto size() CONST { return range().size();}\
        auto empty() CONST { return range().empty();}\
        auto isSingle() CONST { return range().isSingle();}\
        auto operator[](std::size_t _offset) CONST { return range()[_offset];}\
        auto first() CONST { return range().first();}\
        auto last() CONST { return range().last();}\
        auto single() CONST { return range().single();}\
        auto first(ALIAS(Reference) _else) CONST { return range().first(_else);}\
        auto last(ALIAS(Reference) _else) CONST { return range().last(_else);}\
        auto single(ALIAS(Reference) _else) CONST { return range().single(_else);}\
        auto toVector() CONST { return range().toVector();}\
        template<std::size_t TSize>\
        auto toArray(const ALIAS(Value)& _defaultValue = {}) CONST { return range().template toArray<TSize>(_defaultValue);}\
        auto toArray() CONST requires hasCompTimeSize { return range().toArray();}\
        template<std::size_t TCapacity>\
        auto toFixedVector() CONST { return range().template toFixedVector<TCapacity>(); }\
        auto toFixedVector() CONST requires hasCompTimeSize { return range().toFixedVector(); }\
        auto toList() CONST { return range().toList(); }\
        auto toUnorderedSet() CONST { return range().toUnorderedSet();}\
        template<typename TOutIterator>\
        auto assign(const TOutIterator& _begin) CONST { return range().template assign(_begin);}\
        template<typename TOutIterator>\
        auto assign(const TOutIterator& _begin, const TOutIterator& _end) CONST { return range().template assign<TOutIterator>(_begin, _end);}\
        template<typename TOutIterator>\
        void assign(const TOutIterator& _begin, const TOutIterator& _end, const ALIAS(Value)& _defaultValue) CONST { return range().template assign<TOutIterator>(_begin, _end, _defaultValue); }\
        auto take(std::size_t _size) CONST { return range().take(_size);}\
        auto skip(std::size_t _size) CONST { return range().skip(_size);}\
        template<std::size_t TSize>\
        auto take() CONST requires (ALIAS(URange)::hasCompTimeSize && (TCompTimeSize >= TSize)) { return range().template take<TSize>();}\
        template<std::size_t TSize>\
        auto skip() CONST requires (ALIAS(URange)::hasCompTimeSize && (TCompTimeSize >= TSize)) { return range().template skip<TSize>();}\
        template<typename TPredicate>\
        auto filter(const TPredicate& _predicate = {}) CONST { return range().template filter<TPredicate>(_predicate); }\
        auto reverse() CONST { return range().reverse(); }\
        template<typename TMapper>\
        auto map(const TMapper& _mapper = {}) CONST { return range().template map<TMapper>(_mapper);}\
        template<typename TOutReference>\
        auto cast() CONST { return range().template cast<TOutReference>();}\
        auto address() CONST { return range().address();}\
        auto dereference() CONST { return range().dereference();}\
        auto immutable() CONST { return range().immutable();}\
        auto index() CONST { return range().index(); }\
        auto indexLazy() CONST requires (!ALIAS(URange)::hasCompTimeSize) { return range().indexLazy(); }\
        template<typename TIterable, typename ... TIterables>\
        auto zip(TIterable& _iterable, TIterables& ..._iterables) CONST { return range().zip(_iterable, _iterables...); }\
        template<typename TIterable, typename ... TIterables>\
        auto zip(const TIterable& _iterable, const TIterables& ..._iterables) CONST { return range().zip(_iterable, _iterables...); }\
        auto enumerate() CONST { return range().enumerate(); }\
        auto enumerateLazy() CONST requires (!ALIAS(URange)::hasCompTimeSize) { return range().enumerateLazy(); }\
        template<typename TAccumulator, typename TReduce>\
        auto reduce(const TReduce& _reduce, const TAccumulator& _start) CONST { return range().template reduce<TAccumulator, TReduce>(_reduce, _start); }\
        template<typename TCompare>\
        auto best(const TCompare& _compare) CONST { return range().template best<TCompare>(_compare); }\
        template<typename TCompare>\
        auto best(const TCompare& _compare, ALIAS(Reference) _else) CONST { return range().template best<TCompare>(_compare, _else); }\
        template<typename TCompare>\
        auto bestIt(const TCompare& _compare) CONST { return range().template bestIt<TCompare>(_compare); }\
        auto min() CONST { return range().min(); }\
        auto max() CONST { return range().max(); }\
        auto min(ALIAS(Reference) _else) CONST { return range().min(_else); }\
        auto max(ALIAS(Reference) _else) CONST { return range().max(_else); }\
        template<typename TSum = ALIAS(Value)>\
        auto sum() CONST { return range().template sum<TSum>(); }\
        template<typename TSum = ALIAS(Value)>\
        auto avg(TSum _else) CONST { return range().template avg<TSum>(_else); }\
        template<typename TSum = ALIAS(Value)>\
        auto avg() CONST { return range().template avg<TSum>(); }\

namespace cpputils::range
{
    template<typename TConstIterator, typename TNonConstIterator, std::size_t TCompTimeSize = noCompTimeSize>
    class ConstAndNonConstRanged
    {

#define ITERATOR TConstIterator
#define CONST const
#define ALIAS(type) Const##type
        CPPUTILS_RANGE_RANGED_BODY
#undef ITERATOR
#undef CONST
#undef ALIAS

#define ITERATOR TNonConstIterator
#define CONST
#define ALIAS(type) NonConst##type
            CPPUTILS_RANGE_RANGED_BODY
#undef ITERATOR
#undef CONST
#undef ALIAS

    };

    template<typename TIterator, std::size_t TCompTimeSize = noCompTimeSize>
    class ConstRanged
    {

#define ITERATOR TIterator
#define CONST const
#define ALIAS(type) type
        CPPUTILS_RANGE_RANGED_BODY
#undef ITERATOR
#undef CONST
#undef ALIAS

    };

    template<typename TIterator, std::size_t TCompTimeSize = noCompTimeSize>
    class NonConstRanged
    {

#define ITERATOR TIterator
#define CONST const
#define ALIAS(type) type
        CPPUTILS_RANGE_RANGED_BODY
#undef ITERATOR
#undef CONST
#undef ALIAS

    };

    template<typename TConstIterator, typename TNonConstIterator = void, std::size_t TCompTimeSize = noCompTimeSize>
    class Ranged: public std::conditional_t<std::is_void_v<TNonConstIterator>, ConstRanged<TConstIterator, TCompTimeSize>, ConstAndNonConstRanged<TConstIterator, TNonConstIterator, TCompTimeSize>>
    {};

}