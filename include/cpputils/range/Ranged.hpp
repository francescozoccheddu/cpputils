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
        ALIAS(Iterator) begin() CONST { return range().begin();}\
        ALIAS(Iterator) end() CONST { return range().end();}\
        std::size_t size() CONST { return range().size();}\
        bool empty() CONST { return range().empty();}\
        bool isSingle() CONST { return range().isSingle();}\
        ALIAS(Reference) operator[](std::size_t _offset) CONST { return range()[_offset];}\
        ALIAS(Reference) first() CONST { return range().first();}\
        ALIAS(Reference) last() CONST { return range().last();}\
        ALIAS(Reference) single() CONST { return range().single();}\
        ALIAS(Reference) first(ALIAS(Reference) _else) CONST { return range().first(_else);}\
        ALIAS(Reference) last(ALIAS(Reference) _else) CONST { return range().last(_else);}\
        ALIAS(Reference) single(ALIAS(Reference) _else) CONST { return range().single(_else);}\
        auto toVector() CONST { return range().toVector();}\
        template<std::size_t TSize>\
        auto toArray(const ALIAS(Value)& _defaultValue = {}) CONST { return range().template toArray<TSize>(_defaultValue);}\
        auto toArray() CONST requires ALIAS(URange)::hasCompTimeSize { return range().toArray();}\
        template<std::size_t TCapacity>\
        auto toFixedVector() CONST { return range().template toFixedVector<TCapacity>(); }\
        auto toFixedVector() CONST requires ALIAS(URange)::hasCompTimeSize { return range().toFixedVector(); }\
        auto toList() CONST { return range().toList(); }\
        auto toUnorderedSet() CONST { return range().toUnorderedSet();}\
        template<typename TOutIterator>\
        void assign(const TOutIterator& _begin) CONST { return range().template assign(_begin);}\
        template<typename TOutIterator>\
        TOutIterator assign(const TOutIterator& _begin, const TOutIterator& _end) CONST { return range().template assign<TOutIterator>(_begin, _end);}\
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
        auto zip(TIterable& _iterable, TIterables& ..._iterables) CONST { return range().template zip<TIterable, TIterables...>(_iterable, _iterables...); }\
        template<typename TIterable, typename ... TIterables>\
        auto zip(const TIterable& _iterable, const TIterables& ..._iterables) CONST { return range().template zip<TIterable, TIterables...>(_iterable, _iterables...); }\
        template<typename TIterable> \
        auto join(TIterable& _iterable) CONST { return range().template join<TIterable>(_iterable); }\
        template<typename TIterable> \
        auto join(const TIterable& _iterable) CONST { return range().template join<TIterable>(_iterable); }\
        auto fill(std::size_t _size, const ALIAS(Value)& _value = {}) CONST { return range().fill(_size, _value); }\
        auto resize(std::size_t _size, const ALIAS(Value)& _value = {}) CONST { return range().resize(_size, _value); }\
        template<std::size_t TSize>\
        auto resize(const ALIAS(Value)& _value = {}) CONST { return range().template resize<TSize>(_value); }\
        auto enumerate() CONST { return range().enumerate(); }\
        auto enumerateLazy() CONST requires (!ALIAS(URange)::hasCompTimeSize) { return range().enumerateLazy(); }\
        template<typename TAccumulator, typename TReduce>\
        TAccumulator reduce(const TReduce& _reduce, const TAccumulator& _start) CONST { return range().template reduce<TAccumulator, TReduce>(_reduce, _start); }\
        template<typename TCompare>\
        ALIAS(Reference) best(const TCompare& _compare) CONST { return range().template best<TCompare>(_compare); }\
        template<typename TCompare>\
        ALIAS(Reference) best(const TCompare& _compare, ALIAS(Reference) _else) CONST { return range().template best<TCompare>(_compare, _else); }\
        template<typename TCompare>\
        ALIAS(Iterator) bestIt(const TCompare& _compare) CONST { return range().template bestIt<TCompare>(_compare); }\
        ALIAS(Reference) min() CONST { return range().min(); }\
        ALIAS(Reference) max() CONST { return range().max(); }\
        ALIAS(Reference) min(ALIAS(Reference) _else) CONST { return range().min(_else); }\
        ALIAS(Reference) max(ALIAS(Reference) _else) CONST { return range().max(_else); }\
        template<typename TSum = ALIAS(Value)>\
        TSum sum() CONST { return range().template sum<TSum>(); }\
        template<typename TSum = ALIAS(Value)>\
        TSum avg(TSum _else) CONST { return range().template avg<TSum>(_else); }\
        template<typename TSum = ALIAS(Value)>\
        TSum avg() CONST { return range().template avg<TSum>(); }\
        bool isSet() CONST { return range().isSet(); }\


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
#define CONST
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