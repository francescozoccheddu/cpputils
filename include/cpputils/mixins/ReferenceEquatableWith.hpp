#ifndef CPPUTILS_MIXINS_REFERENCEEQUATABLEWITH_INCLUDED
#define CPPUTILS_MIXINS_REFERENCEEQUATABLEWITH_INCLUDED

#include <cpputils/mixins/WithVirtualDestructor.hpp>
#include <type_traits>

namespace cpputils::mixins
{

	template<typename TOther> requires std::is_class_v<TOther> && (!std::is_const_v<TOther>)
	class ReferenceEquatableWith : public virtual WithVirtualDestructor
	{

	public:

		bool operator==(const TOther& _b) const;
		bool operator!=(const TOther& _b) const;

	};

}

#define CPPUTILS_MIXINS_REFERENCEEQUATABLEWITH_IMPLEMENTATION
#include <cpputils-IMPL/mixins/ReferenceEquatableWith.tpp>
#undef CPPUTILS_MIXINS_REFERENCEEQUATABLEWITH_IMPLEMENTATION

#endif