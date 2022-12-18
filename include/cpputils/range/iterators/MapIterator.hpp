#pragma once

#include <cpputils/range/iterators/internal/Iterator.hpp>
#include <cpputils/range/internal/consts.hpp>
#include <iterator>
#include <memory>

namespace cpputils::range::iterators
{

    namespace internal
    {

        template<typename TIterator, typename TMapper>
        using MapperResult = std::invoke_result_t<const TMapper, std::iter_reference_t<const TIterator>>;

    }

    template<typename TIterator, typename TMapper>
    class MapIterator final: public internal::Iterator<TIterator, internal::MapperResult<TIterator, TMapper>>
    {

    private:

        using Base = internal::Iterator<TIterator, internal::MapperResult<TIterator, TMapper>>;

        TMapper m_mapper;
        TIterator m_it;

    public:

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;
        using typename Base::difference_type;
        using typename Base::iterator_category;

        MapIterator(const std::shared_ptr<range::internal::Data<TIterator>>& _data, const TIterator& _it, const TMapper& _mapper)
            : Base{ _data }, m_it{ _it }, m_mapper{ _mapper }
        {}

        const TMapper& mapper() const
        {
            return m_mapper;
        }

        reference operator*() const
        {
            return m_mapper(*m_it);
        }

        pointer operator->() const
        {
            return std::addressof(*(*this));
        }

        reference operator[](difference_type _offset) const
        {
            return m_mapper(*std::next(m_it, _offset));
        }

        MapIterator& operator++()
        {
            std::advance(m_it, 1);
            return *this;
        }

        MapIterator operator++(int)
        {
            MapIterator clone{ *this };
            ++(*this);
            return clone;
        }

        MapIterator& operator+=(difference_type _offset)
        {
            std::advance(m_it, _offset);
            return *this;
        }

        MapIterator operator+(difference_type _offset) const
        {
            MapIterator clone{ *this };
            clone += _offset;
            return clone;
        }

        MapIterator& operator--()
        {
            std::advance(m_it, -1);
            return *this;
        }

        MapIterator operator--(int)
        {
            MapIterator clone{ *this };
            --(*this);
            return clone;
        }

        MapIterator& operator-=(difference_type _offset)
        {
            std::advance(m_it, -_offset);
            return *this;
        }

        MapIterator operator-(difference_type _offset) const
        {
            MapIterator clone{ *this };
            clone -= _offset;
            return clone;
        }

        bool operator==(const MapIterator& _other) const
        {
            return m_it == _other.m_it;
        }

        difference_type operator-(const MapIterator& _other) const
        {
            return std::distance(_other.m_it, m_it);
        }

    };

}