#ifndef CPPUTILS_COLLECTIONS_EVENT_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Event.hpp>

namespace cpputils::collections
{

	namespace internal
	{

		template <typename ... TArgs>
		void EventBase<TArgs...>::operator()(TArgs ... _args)
		{
			for (const Handler* handler : m_handlers)
			{
				(*handler)(_args ...);
			}
		}

		template <typename ... TArgs>
		bool EventBase<TArgs...>::operator+=(Handler& _handler)
		{
			return m_handlers.insert(&_handler).second;
		}

		template <typename ... TArgs>
		bool EventBase<TArgs...>::operator-=(const Handler& _handler)
		{
			return m_handlers.erase(&_handler).second;
		}

	}

	template <typename TInvoker, typename ... TArgs>
	void Event<TInvoker, TArgs...>::operator()(TArgs..._args) requires (!std::is_same_v<TInvoker, internal::AnyEventInvoker>)
	{
		internal::EventBase<TArgs...>::operator()(_args ...);
	}

	template <typename TInvoker, typename ... TArgs>
	void Event<TInvoker, TArgs...>::operator()(TArgs..._args) requires std::is_same_v<TInvoker, internal::AnyEventInvoker>
	{
		internal::EventBase<TArgs...>::operator()(_args ...);
	}

}