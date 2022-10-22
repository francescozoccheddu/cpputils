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
			for (Handler& handler : m_handlers)
			{
				handler(_args ...);
			}
		}

		template <typename ... TArgs>
		typename EventBase<TArgs...>::HandlerToken EventBase<TArgs...>::operator+=(const Handler& _handler)
		{
			m_handlers.push_front(_handler);
			return m_handlers.before_begin();
		}

		template <typename ... TArgs>
		void EventBase<TArgs...>::operator-=(const HandlerToken& _handlerToken)
		{
			m_handlers.erase_after(_handlerToken);
		}

	}

	template <cpputils::concepts::SimpleClass TInvoker, typename ... TArgs>
	void Event<TInvoker, TArgs...>::operator()(TArgs..._args) requires (!std::same_as<TInvoker, internal::AnyEventInvoker>)
	{
		internal::EventBase<TArgs...>::operator()(_args ...);
	}

	template <cpputils::concepts::SimpleClass TInvoker, typename ... TArgs>
	void Event<TInvoker, TArgs...>::operator()(TArgs..._args) requires std::same_as<TInvoker, internal::AnyEventInvoker>
	{
		internal::EventBase<TArgs...>::operator()(_args ...);
	}

}