#pragma once

#include <optional>
#include <cstddef>
#include <iterator>
#include <array>
#include <type_traits>
#include <tuple>
#include <cpputils/range/Range.hpp>

namespace cpputils::range
{

    namespace internal
    {

        template<typename TType>
        struct IsStdArray: std::false_type {};

        template<typename TValue, std::size_t TSize>
        struct IsStdArray<std::array<TValue, TSize>>: std::true_type {};

        struct NoCompTimeSizeType { static constexpr std::size_t value{ noCompTimeSize }; };

        template<typename TType>
        struct ArraySize: std::extent<TType> {};

        template<typename TValue, std::size_t TSize>
        struct ArraySize<std::array<TValue, TSize>>: std::tuple_size<std::array<TValue, TSize>> {};

        template<typename TIterable>
        constexpr std::size_t compTimeSizeDirect = std::conditional_t<(IsStdArray<TIterable>::value || std::is_bounded_array_v<TIterable>), ArraySize<TIterable>, NoCompTimeSizeType>::value;

    }

    template<typename TIterable>
    class RangeMaker final
    {

    private:

        const TIterable& m_iterable;
        mutable std::optional<std::size_t> m_sizeHint;

    public:

        static constexpr std::size_t compTimeSize = internal::compTimeSizeDirect<std::remove_cv_t<std::remove_reference_t<TIterable>>>;
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

        RangeMaker(const TIterable& _iterable): m_iterable{ _iterable }, m_sizeHint{ std::nullopt }
        {
            if constexpr (hasCompTimeSize)
            {
                m_sizeHint = compTimeSize;
            }
        }

        template<typename TIterator>
        inline auto make(const TIterator& _begin, const TIterator& _end) const
        {
            if constexpr (hasCompTimeSize)
            {
                return Range<TIterator, compTimeSize>{ _begin, _end };
            }
            else
            {
                return Range<TIterator>{ _begin, _end, m_sizeHint};
            }
        }

    };

}