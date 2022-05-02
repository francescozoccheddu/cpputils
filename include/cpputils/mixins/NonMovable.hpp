#ifndef CPPUTILS_MIXINS_NONMOVABLE_INCLUDED
#define CPPUTILS_MIXINS_NONMOVABLE_INCLUDED

#include <cpputils/mixins/WithVirtualDestructor.hpp>

namespace cpputils::mixins
{

	class NonMovable : public virtual WithVirtualDestructor
	{

	protected:

		NonMovable() = default;
		NonMovable(NonMovable&&) = delete;
		NonMovable& operator=(NonMovable&&) = delete;

	};

}

#endif