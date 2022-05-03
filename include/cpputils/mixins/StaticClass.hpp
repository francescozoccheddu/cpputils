#ifndef CPPUTILS_MIXINS_STATICCLASS_INCLUDED
#define CPPUTILS_MIXINS_STATICCLASS_INCLUDED

#include <cpputils/mixins/NonCopyable.hpp>
#include <cpputils/mixins/NonMovable.hpp>

namespace cpputils::mixins
{

	class StaticClass : public virtual NonCopyable, public virtual NonMovable
	{

	private:

		StaticClass() = delete;

	};

}

#endif