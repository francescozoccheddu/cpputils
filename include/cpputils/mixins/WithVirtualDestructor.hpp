#ifndef CPPUTILS_MIXINS_WITHVIRTUALDESTRUCTOR_INCLUDED
#define CPPUTILS_MIXINS_WITHVIRTUALDESTRUCTOR_INCLUDED

namespace cpputils::mixins
{

	class WithVirtualDestructor
	{

	protected:

		WithVirtualDestructor() = default;
		virtual ~WithVirtualDestructor() = default;

	};

}

#endif