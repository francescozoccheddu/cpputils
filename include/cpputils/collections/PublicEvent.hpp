#pragma once

#include <cpputils/collections/Event.hpp>


namespace cpputils::collections
{

	template <typename ... TArgs>
	using PublicEvent = Event<internal::AnyEventInvoker, TArgs ...>;

}

