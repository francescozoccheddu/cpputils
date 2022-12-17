#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/mixins/StaticClass.hpp>
#include <cpputils/concepts.hpp>
#include <functional>
#include <concepts>
#include <forward_list>

namespace cpputils::collections
{

	template <cpputils::concepts::SimpleClass TInvoker, typename ...>
	class Event;

	namespace internal
	{

		class AnyEventInvoker final: public mixins::StaticClass {};

		template <typename ... TArgs>
		class EventBase: public mixins::ReferenceClass
		{

		public:

			using Handler = std::function<void(TArgs...)>;
			using HandlerToken = typename std::forward_list<Handler>::const_iterator;

		private:

			template <cpputils::concepts::SimpleClass TInvoker, typename ...>
			friend class collections::Event;

			std::forward_list<Handler> m_handlers{};

			EventBase() = default;

			void operator()(TArgs ... _args)
			{
				for (Handler& handler : m_handlers)
				{
					handler(_args ...);
				}
			}

		public:

			HandlerToken operator+=(const Handler& _handler)
			{
				m_handlers.push_front(_handler);
				return m_handlers.before_begin();
			}

			void operator-=(const HandlerToken& _handlerToken)
			{
				m_handlers.erase_after(_handlerToken);
			}

		};

	}

	template <cpputils::concepts::SimpleClass TInvoker, typename ... TArgs>
	class Event final: public internal::EventBase<TArgs ...>
	{

	private:

		friend TInvoker;

		void operator()(TArgs..._args) requires (!std::same_as<TInvoker, internal::AnyEventInvoker>)
		{
			internal::EventBase<TArgs ...>::operator()(_args ...);
		}

	public:

		Event() = default;

		void operator()(TArgs..._args) requires std::same_as<TInvoker, internal::AnyEventInvoker>
		{
			internal::EventBase<TArgs ...>::operator()(_args ...);
		}

	};

}
