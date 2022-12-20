#pragma once

#include <optional>
#include <cstddef>
#include <iterator>
#include <array>
#include <type_traits>
#include <tuple>
#include <limits>

namespace cpputils::range
{

    constexpr std::size_t noCompTimeSize = std::numeric_limits<std::size_t>::max();

    namespace internal
    {

        template<typename TType>
        struct CompTimeSize: std::integral_constant<std::size_t, noCompTimeSize> {};

        template<typename TValue, std::size_t TSize>
        struct CompTimeSize<TValue[TSize]>: std::integral_constant<std::size_t, TSize> {};

        template<typename TValue, std::size_t TSize>
        struct CompTimeSize<std::array<TValue, TSize>>: std::integral_constant<std::size_t, TSize> {};

        template<typename TIterable>
        constexpr std::size_t compTimeSize = CompTimeSize<TIterable>::value;

        constexpr std::size_t sumCompTimeSizes(std::size_t _a, std::size_t _b)
        {
            return _a == noCompTimeSize || _b == noCompTimeSize ? noCompTimeSize : (_a + _b);
        }

        constexpr std::optional<std::size_t> sumSizeHints(const std::optional<std::size_t>& _a, const std::optional<std::size_t>& _b)
        {
            return _a.has_value() && _b.has_value() ? (*_a + *_b) : noCompTimeSize;
        }

    }


    template<typename TIterable>
    class RangeSizer final
    {

    private:

        const TIterable& m_iterable;
        mutable std::optional<std::size_t> m_sizeHint;

    public:

        static constexpr std::size_t compTimeSize = internal::compTimeSize<std::remove_cv_t<std::remove_reference_t<TIterable>>>;
        static constexpr bool hasCompTimeSize = compTimeSize != noCompTimeSize;

        std::optional<std::size_t> sizeHint() const
        {
            if (!m_sizeHint)
            {
                if constexpr (requires{ std::size(m_iterable); })
                {
                    m_sizeHint = std::size(m_iterable);
                }
            }
            return m_sizeHint;
        }

        std::size_t size()const
        {
            if (!m_sizeHint)
            {
                m_sizeHint = std::size(m_iterable);
            }
            return *m_sizeHint;
        }

        RangeSizer(const TIterable& _iterable): m_iterable{ _iterable }, m_sizeHint{ std::nullopt }
        {
            if constexpr (hasCompTimeSize)
            {
                m_sizeHint = compTimeSize;
            }
        }

    };

}