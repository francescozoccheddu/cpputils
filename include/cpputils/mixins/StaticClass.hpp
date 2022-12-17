#pragma once

#include <cpputils/mixins/NonCopyable.hpp>
#include <cpputils/mixins/NonMovable.hpp>

namespace cpputils::mixins
{

	class StaticClass: public virtual NonCopyable, public virtual NonMovable
	{

	private:

		StaticClass() = delete;

	};

}
