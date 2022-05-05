#ifndef CPPUTILS_CONCEPTS_INCLUDED
#define CPPUTILS_CONCEPTS_INCLUDED

#include <type_traits>
#include <concepts>

namespace cpputils::concepts
{

	template<typename TType>
	concept SimpleClass = std::is_class_v<TType> && (!std::is_const_v<TType>) && (!std::is_volatile_v<TType>);

	template<typename TType, typename TBase>
	concept DerivedSimpleClass = SimpleClass<TType> && std::is_base_of_v<TBase, TType>;

}


#endif