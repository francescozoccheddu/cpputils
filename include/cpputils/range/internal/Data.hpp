#pragma once

#include <cpputils/range/internal/Buffer.hpp>
#include <iterator>
#include <utility>

namespace cpputils::range::internal
{

    template<typename TIterator, typename TValue = std::iter_value_t<TIterator>>
    class Data final
    {

    private:

        Buffer m_buffer;
        TIterator m_begin, m_end;

    public:

        Data(const TIterator& _begin, const TIterator& _end, Buffer&& _buffer)
            : m_buffer{ std::move(_buffer) }, m_begin{ _begin }, m_end{ _end }
        {}

        Data(const TIterator& _begin, const TIterator& _end)
            : m_buffer{}, m_begin{ _begin }, m_end{ _end }
        {}

        inline const TIterator& begin() const noexcept
        {
            return m_begin;
        }

        inline const TIterator& end() const noexcept
        {
            return m_end;
        }

        inline Buffer&& extractBuffer() noexcept
        {
            return std::move(m_buffer);
        }

    };

}