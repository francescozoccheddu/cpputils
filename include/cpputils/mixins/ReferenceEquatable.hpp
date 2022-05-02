#ifndef CPPUTILS_MIXINS_REFERENCEEQUATABLE_INCLUDED
#define CPPUTILS_MIXINS_REFERENCEEQUATABLE_INCLUDED

#include <cpputils/mixins/ReferenceEquatableWith.hpp>

namespace cpputils::mixins
{

	class ReferenceEquatable : public virtual ReferenceEquatableWith<ReferenceEquatable> {};

}

#endif