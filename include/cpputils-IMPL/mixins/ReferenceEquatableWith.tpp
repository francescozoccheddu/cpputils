#ifndef CPPUTILS_MIXINS_REFERENCEEQUATABLEWITH_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/mixins/ReferenceEquatableWith.hpp>

#include <memory>

namespace cpputils::mixins
{

	template <typename TOther>
	bool ReferenceEquatableWith<TOther>::operator==(const TOther& _b) const
	{
		return std::addressof(_b) == this;
	}

	template <typename TOther>
	bool ReferenceEquatableWith<TOther>::operator!=(const TOther& _b) const
	{
		return std::addressof(_b) != this;
	}

}