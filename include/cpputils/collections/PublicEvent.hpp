#ifndef CPPUTILS_COLLECTIONS_PUBLICEVENT_INCLUDED
#define CPPUTILS_COLLECTIONS_PUBLICEVENT_INCLUDED

#include <cpputils/collections/Event.hpp>


namespace cpputils::collections
{

	template<typename ... TArgs>
	using PublicEvent = Event<internal::AnyEventInvoker, TArgs ...>;

}

#endif