#ifndef CPPUTILS_MIXINS_NONCOPYABLE_INCLUDED
#define CPPUTILS_MIXINS_NONCOPYABLE_INCLUDED

#include <cpputils/mixins/WithVirtualDestructor.hpp>

namespace cpputils::mixins
{

	class NonCopyable : public virtual WithVirtualDestructor
	{

	protected:

		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

	};

}

#endif