#pragma once

#include <cpputils/mixins/WithVirtualDestructor.hpp>

namespace cpputils::mixins
{

	class NonCopyable: public virtual WithVirtualDestructor
	{

	protected:

		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

	};

}
