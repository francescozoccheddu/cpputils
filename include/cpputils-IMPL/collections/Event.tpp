#ifndef CPPUTILS_COLLECTIONS_EVENT_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Event.hpp>

namespace cpputils::collections
{

	template<typename ... TArgs>
	void internal::EventBase<TArgs...>::operator()(TArgs ... _args)
	{
		for (const Handler* handler : m_handlers)
		{
			(*handler)(_args ...);
		}
	}

	template<typename ... TArgs>
	bool internal::EventBase<TArgs...>::operator+=(Handler& _handler)
	{
		return m_handlers.insert(&_handler).second;
	}

	template<typename ... TArgs>
	bool internal::EventBase<TArgs...>::operator-=(const Handler& _handler)
	{
		return m_handlers.erase(&_handler).second;
	}

	CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE
		void CPPUTILS_COLLECTIONS_EVENT::operator()(TArgs..._args) requires (!std::is_same_v<TInvoker, internal::AnyEventInvoker>)
	{
		internal::EventBase<TArgs...>::operator()(_args ...);
	}

	CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE
		void CPPUTILS_COLLECTIONS_EVENT::operator()(TArgs..._args) requires std::is_same_v<TInvoker, internal::AnyEventInvoker>
	{
		internal::EventBase<TArgs...>::operator()(_args ...);
	}

}