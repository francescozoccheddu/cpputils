#ifndef CPPUTILS_COLLECTIONS_TYPES_INCLUDED
#define CPPUTILS_COLLECTIONS_TYPES_INCLUDED

#include <cpputils/mixins/StaticClass.hpp>
#include <type_traits>
#include <iterator>
#include <utility>

namespace cpputils::collections::types
{

	namespace internal
	{

		template<typename TIterable>
		using BeginResult = decltype(std::declval<TIterable&>().begin());

		template<typename TIterable, typename = void>
		struct CBeginResultOrBeginResultStruct final : public mixins::StaticClass { using Type = BeginResult<TIterable>; };

		template<typename TIterable>
		struct CBeginResultOrBeginResultStruct<TIterable, std::void_t<decltype(std::declval<TIterable&>().cbegin())>> final : public mixins::StaticClass { using Type = decltype(std::declval<TIterable&>().cbegin()); };

		template<typename TIterable, typename = void>
		struct RBeginOrBeginResultStruct final : public mixins::StaticClass { using Type = BeginResult<TIterable>; };

		template<typename TIterable>
		struct RBeginOrBeginResultStruct<TIterable, std::void_t<decltype(std::declval<TIterable&>().rbegin())>> final : public mixins::StaticClass { using Type = decltype(std::declval<TIterable&>().rbegin()); };

		template<typename TIterable, typename = void>
		struct CRBeginOrBeginResultStruct final : public mixins::StaticClass { using Type = BeginResult<TIterable>; };

		template<typename TIterable>
		struct CRBeginOrBeginResultStruct<TIterable, std::void_t<decltype(std::declval<TIterable&>().crbegin())>> final : public mixins::StaticClass { using Type = decltype(std::declval<TIterable&>().crbegin()); };

	}

	template<typename TIterable>
	using Iterator = internal::BeginResult<TIterable>;

	template<typename TIterable>
	using ConstIterator = typename internal::CBeginResultOrBeginResultStruct<TIterable>::Type;

	template<typename TIterable>
	using ReverseIterator = typename internal::RBeginOrBeginResultStruct<TIterable>::Type;

	template<typename TIterable>
	using ConstReverseIterator = typename internal::CRBeginOrBeginResultStruct<TIterable>::Type;

	template<typename TType>
	using DereferenceResult = decltype(*std::declval<TType&>());

	template<typename TFrom, typename TTo>
	inline constexpr TTo cast(TFrom _from);

	template<typename TFrom, typename TTo>
	inline constexpr TTo dereferenceAndCast(TFrom _from);

	template<typename TFrom, typename TTo>
	inline constexpr DereferenceResult<TTo> castAndDereference(TFrom _from);

}

#define CPPUTILS_COLLECTIONS_TYPES_IMPLEMENTATION
#include <cpputils-IMPL/collections/types.tpp>
#undef CPPUTILS_COLLECTIONS_TYPES_IMPLEMENTATION

#endif