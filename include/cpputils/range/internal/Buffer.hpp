#pragma once

#include <cstddef>
#include <type_traits>
#include <iterator>
#include <memory>
#include <algorithm>
#include <utility>

namespace cpputils::range::internal
{

    class Buffer final
    {

    private:

        std::unique_ptr<char[]> m_data{};
        std::size_t m_capacity{};
        std::size_t m_size{};

    public:

        template<typename TIterator, typename TValue>
        void collect(const TIterator& _begin, const TIterator& _end)
        {
            const std::size_t size{ static_cast<std::size_t>(std::distance(_begin, _end)) };
            setSize<TValue>(size);
            if constexpr (std::is_pointer_v<TIterator>)
            {
                if (reinterpret_cast<const char*>(_begin) == m_data.get())
                {
                    return;
                }
            }
            TValue* outIt{ reinterpret_cast<TValue*>(m_data.get()) };
            TIterator inIt{ _begin };
            while (inIt != _end)
            {
                *(outIt++) = static_cast<TValue>(*(inIt++));
            }
        }

        template<typename TValue>
        void setSize(std::size_t _size)
        {
            const std::size_t capacity{ _size * sizeof(TValue) };
            if (capacity > m_capacity)
            {
                std::unique_ptr<char[]> temp = std::make_unique<char[]>(capacity);
                std::copy(m_data.get(), m_data.get() + m_capacity, temp.get());
                m_data = std::move(temp);
                m_capacity = capacity;
            }
            m_size = _size;
        }

        template<typename TValue>
        inline TValue* begin() const noexcept
        {
            return reinterpret_cast<TValue*>(m_data.get());
        }

        template<typename TValue>
        inline TValue* end() const noexcept
        {
            return begin<TValue>() + m_size;
        }

    };

}