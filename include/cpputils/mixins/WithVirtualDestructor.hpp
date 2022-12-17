#pragma once

namespace cpputils::mixins
{

	class WithVirtualDestructor
	{

	protected:

		WithVirtualDestructor() = default;
		virtual ~WithVirtualDestructor() = default;

	};

}
