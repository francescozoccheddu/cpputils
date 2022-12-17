#pragma once

#include <type_traits>

namespace cpputils::range::internal::consts
{

    template<typename TType>
    using Ptr = std::conditional_t<std::is_pointer_v<TType>, std::add_pointer_t<std::add_const_t<std::remove_pointer_t<TType>>>, TType>;

    template<typename TType>
    using LRef = std::conditional_t<std::is_lvalue_reference_v<TType>, std::add_lvalue_reference_t<std::add_const_t<std::remove_reference_t<TType>>>, TType>;

    template<typename TType>
    using RRef = std::conditional_t<std::is_rvalue_reference_v<TType>, std::add_rvalue_reference_t<std::add_const_t<std::remove_reference_t<TType>>>, TType>;

    template<typename TType>
    using Ref = std::conditional_t<std::is_lvalue_reference_v<TType>, LRef<TType>, RRef<TType>>;

    template<typename TType>
    using RefOrPtr = std::conditional_t<std::is_pointer_v<TType>, Ptr<TType>, Ref<TType>>;

}