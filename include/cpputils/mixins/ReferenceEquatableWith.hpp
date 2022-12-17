#pragma once

#include <cpputils/mixins/WithVirtualDestructor.hpp>

namespace cpputils::mixins
{

	template <typename TOther>
	class ReferenceEquatableWith: public virtual WithVirtualDestructor
	{

	public:

		inline bool operator==(const TOther& _b) const noexcept
		{
			return std::addressof(_b) == this;
		}

		inline bool operator!=(const TOther& _b) const noexcept
		{
			return std::addressof(_b) != this;
		}

	};

}
