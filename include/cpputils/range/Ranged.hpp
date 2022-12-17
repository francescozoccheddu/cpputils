#pragma once

#include <cpputils/range/Range.hpp>

namespace cpputils::range
{

    template<typename TIterator>
    class Ranged
    {

    public:

        using URange = Range<TIterator>;
        using Iterator = typename URange::Iterator;
        using Value = typename URange::Value;
        using Reference = typename URange::Reference;
        using Offset = typename URange::Offset;
        using Data = typename URange::Data;
        using Collected = typename URange::Collected;
        using Filtered = typename URange::Filtered;
        using Distinct = typename URange::Distinct;
        using Duplicated = typename URange::Duplicated;
        template<typename TMapper>
        using Mapped = typename URange::template Mapped<TMapper>;
        template<typename TOutReference>
        using Casted = typename URange::template Casted<TOutReference>;
        using Const = typename URange::Const;
        using Addressed = typename URange::Addressed;
        using Dereferenced = typename URange::Dereferenced;
        using Reversed = typename URange::Reversed;
        template<typename TIndex>
        using Index = typename URange::template Index<TIndex>;

    protected:

        virtual URange range() const = 0;

    public:

        Iterator begin() const
        {
            return range().begin();
        }

        Iterator end() const
        {
            return range().end();
        }

        Reference operator[](const Offset& _offset) const
        {
            return range()[_offset];
        }

        Reference first(Reference _else) const
        {
            return range().first(_else);
        }

        Reference last(Reference _else) const
        {
            return range().last(_else);
        }

        Reference single(Reference _else) const
        {
            return range().single(_else);
        }

        Reference first() const
        {
            return range().first();
        }

        Reference last() const
        {
            return range().last();
        }

        Reference single() const
        {
            return range().single();
        }

        Offset size() const
        {
            return range().size();
        }

        bool empty() const
        {
            return range().empty();
        }

        template<typename TIndex = Offset>
        Index<TIndex> index() const
        {
            return range().template index<TIndex>();
        }

        URange take(Offset _size)
        {
            return range().take(_size);
        }

        URange skip(Offset _size)
        {
            return range().skip(_size);
        }

        Filtered filter()
        {
            return range().filter();
        }

        Reversed reverse()
        {
            return range().reverse();
        }

        template<typename TMapper>
        Mapped<TMapper> map(const TMapper& _mapper = {})
        {
            return range().template map<TMapper>(_mapper);
        }

        template<typename TOutReference>
        Casted<TOutReference> cast()
        {
            return range().template cast<TOutReference>();
        }

        Addressed address()
        {
            return range().address();
        }

        Dereferenced dereference()
        {
            return range().dereference();
        }

        Const immutable()
        {
            return range().immutable();
        }

        Collected collect()
        {
            return range().collect();
        }

        Collected clone() const
        {
            return range().clone();
        }

        Collected sort()
        {
            return range().sort();
        }

        Distinct distinct()
        {
            return range().distinct();
        }

        Duplicated duplicated()
        {
            return range().duplicated();
        }

        template<typename TAccumulator, typename TReduce>
        TAccumulator reduce(const TReduce& _reduce, const TAccumulator& _start) const
        {
            return range().template reduce<TAccumulator, TReduce>(_reduce, _start);
        }

        template<typename TCompare>
        Reference best(const TCompare& _compare, Reference _else) const
        {
            return range().template best<TCompare>(_compare, _else);
        }

        template<typename TCompare>
        Reference best(const TCompare& _compare) const
        {
            return range().template best<TCompare>(_compare);
        }

        template<typename TCompare>
        Iterator bestIt(const TCompare& _compare) const
        {
            return range().template bestIt<TCompare>(_compare);
        }

        Reference min(Reference _else) const
        {
            return range().min(_else);
        }

        Reference max(Reference _else) const
        {
            return range().max(_else);
        }

        Reference min() const
        {
            return range().min();
        }

        Reference max() const
        {
            return range().max();
        }

        template<typename TSum = Value>
        TSum sum() const
        {
            return range().template sum<TSum>();
        }

        template<typename TSum = Value>
        TSum avg(TSum _else) const
        {
            return range().template avg<TSum>(_else);
        }

        template<typename TSum = Value>
        TSum avg() const
        {
            return range().template avg<TSum>();
        }

        std::vector<Value> toVector() const
        {
            return range().toVector();
        }

        template<std::size_t TSize>
        std::array<Value, TSize> toArray(const Value& _defaultValue = {}) const
        {
            return range().template toArray<TSize>(_defaultValue);
        }

        std::list<Value> toList() const
        {
            return range().toList();
        }

        std::unordered_set<Value> toUnorderedSet() const
        {
            return range().toUnorderedSet();
        }

        template<typename TOutIterator>
        void assign(const TOutIterator& _begin) const
        {
            return range().template assign<TOutIterator>(_begin);
        }

        template<typename TOutIterator>
        TOutIterator assign(const TOutIterator& _begin, const TOutIterator& _end) const
        {
            return range().template assign<TOutIterator>(_begin, _end);
        }

        template<typename TOutIterator>
        void assign(const TOutIterator& _begin, const TOutIterator& _end, const Value& _defaultValue) const
        {
            return range().template assign<TOutIterator>(_begin, _end, _defaultValue);
        }

    };

}