#pragma once

#include <cpputils/range/Range.hpp>

#define CPPUTILS_RANGE_RANGED_BODY \
    public:\
        using ALIAS(URange) = Range<ITERATOR>;\
        using ALIAS(Iterator) = typename ALIAS(URange)::Iterator;\
        using ALIAS(Value) = typename ALIAS(URange)::Value;\
        using ALIAS(Reference) = typename ALIAS(URange)::Reference;\
        using ALIAS(Offset) = typename ALIAS(URange)::Offset;\
        using ALIAS(Data) = typename ALIAS(URange)::Data;\
        using ALIAS(Collected) = typename ALIAS(URange)::Collected;\
        template<typename TPredicate>\
        using ALIAS(ItFiltered) = typename ALIAS(URange)::template ItFiltered<TPredicate>;\
        template<typename TPredicate>\
        using ALIAS(ValueFiltered) = typename ALIAS(URange)::template ValueFiltered<TPredicate>;\
        using ALIAS(Distinct) = typename ALIAS(URange)::Distinct;\
        using ALIAS(Duplicated) = typename ALIAS(URange)::Duplicated;\
        template<typename TMapper>\
        using ALIAS(Mapped) = typename ALIAS(URange)::template Mapped<TMapper>;\
        template<typename TOutReference>\
        using ALIAS(Casted) = typename ALIAS(URange)::template Casted<TOutReference>;\
        using ALIAS(Const) = typename ALIAS(URange)::Const;\
        using ALIAS(Addressed) = typename ALIAS(URange)::Addressed;\
        using ALIAS(Dereferenced) = typename ALIAS(URange)::Dereferenced;\
        using ALIAS(Reversed) = typename ALIAS(URange)::Reversed;\
        template<typename TIndex>\
        using ALIAS(Index) = typename ALIAS(URange)::template Index<TIndex>;\
    protected:\
        virtual ALIAS(URange) range() CONST = 0;\
    public:\
        ALIAS(Iterator) begin() CONST { return range().begin();} \
        ALIAS(Iterator) end() CONST { return range().end();} \
        ALIAS(Reference) operator[](const ALIAS(Offset)& _offset) CONST { return range()[_offset];} \
        ALIAS(Reference) first(ALIAS(Reference) _else) CONST { return range().first(_else);} \
        ALIAS(Reference) last(ALIAS(Reference) _else) CONST { return range().last(_else);} \
        ALIAS(Reference) single(ALIAS(Reference) _else) CONST { return range().single(_else);} \
        ALIAS(Reference) first() CONST { return range().first();} \
        ALIAS(Reference) last() CONST { return range().last();} \
        ALIAS(Reference) single() CONST { return range().single();} \
        bool isSingle() CONST { return range().isSingle();} \
        ALIAS(Offset) size() CONST { return range().size();} \
        bool empty() CONST { return range().empty();} \
        template<typename TIndex = ALIAS(Offset)>\
        ALIAS(Index)<TIndex> index() CONST { return range().template index<TIndex>();} \
        ALIAS(URange) take(ALIAS(Offset) _size) CONST { return range().take(_size);} \
        ALIAS(URange) skip(ALIAS(Offset) _size) CONST { return range().skip(_size);} \
        template<typename TPredicate> \
        ALIAS(ItFiltered)<TPredicate> filterIterator(const TPredicate& _predicate = {}) CONST { return range().template filterIterator<TPredicate>(_predicate); } \
        template<typename TPredicate> \
        ALIAS(ValueFiltered)<TPredicate> filter(const TPredicate& _predicate = {}) CONST { return range().template filter<TPredicate>(_predicate); } \
        ALIAS(Reversed) reverse() CONST { return range().reverse(); } \
        template<typename TMapper>\
        ALIAS(Mapped)<TMapper> map(const TMapper& _mapper = {}) CONST { return range().template map<TMapper>(_mapper);} \
        template<typename TOutReference>\
        ALIAS(Casted)<TOutReference> cast() CONST { return range().template cast<TOutReference>();} \
        ALIAS(Addressed) address() CONST { return range().address();} \
        ALIAS(Dereferenced) dereference() CONST { return range().dereference();} \
        ALIAS(Const) immutable() CONST { return range().immutable();} \
        ALIAS(Collected) collect() CONST { return range().collect();} \
        ALIAS(Collected) clone() CONST { return range().clone();} \
        ALIAS(Collected) sort() CONST { return range().sort();} \
        ALIAS(Distinct) distinct() CONST { return range().distinct();} \
        ALIAS(Duplicated) duplicated() CONST { return range().duplicated();} \
        template<typename TAccumulator, typename TReduce>\
        TAccumulator reduce(const TReduce& _reduce, const TAccumulator& _start) CONST { return range().template reduce<TAccumulator, TReduce>(_reduce, _start);} \
        template<typename TCompare>\
        ALIAS(Reference) best(const TCompare& _compare, ALIAS(Reference) _else) CONST { return range().template best<TCompare>(_compare, _else);} \
        template<typename TCompare>\
        ALIAS(Reference) best(const TCompare& _compare) CONST { return range().template best<TCompare>(_compare);} \
        template<typename TCompare>\
        ALIAS(Iterator) bestIt(const TCompare& _compare) CONST { return range().template bestIt<TCompare>(_compare);} \
        ALIAS(Reference) min(ALIAS(Reference) _else) CONST { return range().min(_else);} \
        ALIAS(Reference) max(ALIAS(Reference) _else) CONST { return range().max(_else);} \
        ALIAS(Reference) min() CONST { return range().min();} \
        ALIAS(Reference) max() CONST { return range().max();} \
        template<typename TSum = ALIAS(Value)>\
        TSum sum() CONST { return range().template sum<TSum>();} \
        template<typename TSum = ALIAS(Value)>\
        TSum avg(TSum _else) CONST { return range().template avg<TSum>(_else);} \
        template<typename TSum = ALIAS(Value)>\
        TSum avg() CONST { return range().template avg<TSum>();} \
        std::vector<ALIAS(Value)> toVector() CONST { return range().toVector();} \
        template<std::size_t TSize>\
        std::array<ALIAS(Value), TSize> toArray(const ALIAS(Value)& _defaultValue = {}) CONST { return range().template toArray<TSize>(_defaultValue);} \
        template<std::size_t TCapacity> \
        collections::FixedVector<ALIAS(Value), TCapacity> toFixedVector() CONST { return range().template toFixedVector<TCapacity>(); } \
        std::list<ALIAS(Value)> toList() CONST { return range().toList(); } \
        std::unordered_set<ALIAS(Value)> toUnorderedSet() CONST { return range().toUnorderedSet();} \
        template<typename TOutIterator>\
        void assign(const TOutIterator& _begin) CONST { return range().template assign<TOutIterator>(_begin);} \
        template<typename TOutIterator>\
        TOutIterator assign(const TOutIterator& _begin, const TOutIterator& _end) CONST { return range().template assign<TOutIterator>(_begin, _end);} \
        template<typename TOutIterator>\
        void assign(const TOutIterator& _begin, const TOutIterator& _end, const ALIAS(Value)& _defaultValue) CONST { return range().template assign<TOutIterator>(_begin, _end, _defaultValue);\
    }

namespace cpputils::range
{

    template<typename TConstIterator, typename TNonConstIterator>
    class Ranged
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

    template<typename TIterator>
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

    template<typename TIterator>
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

#undef CPPUTILS_RANGE_RANGED_BODY

}