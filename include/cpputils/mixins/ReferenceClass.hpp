#ifndef CPPUTILS_MIXINS_REFERENCECLASS_INCLUDED
#define CPPUTILS_MIXINS_REFERENCECLASS_INCLUDED

#include <cpputils/mixins/ReferenceEquatable.hpp>
#include <cpputils/mixins/NonCopyable.hpp>
#include <cpputils/mixins/NonMovable.hpp>

namespace cpputils::mixins
{

	class ReferenceClass : public virtual ReferenceEquatable, protected virtual NonCopyable, protected virtual NonMovable {};

}

#endif