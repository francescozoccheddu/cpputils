#pragma once

#include <cpputils/mixins/ReferenceEquatableWith.hpp>

namespace cpputils::mixins
{

	class ReferenceEquatable: public virtual ReferenceEquatableWith<ReferenceEquatable> {};

}
