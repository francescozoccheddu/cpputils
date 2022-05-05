#ifndef CPPUTILS_COLLECTIONS_EVENT_INCLUDED
#define CPPUTILS_COLLECTIONS_EVENT_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/mixins/StaticClass.hpp>
#include <cpputils/concepts.hpp>
#include <functional>
#include <concepts>
#include <unordered_set>

namespace cpputils::collections
{

	template <cpputils::concepts::SimpleClass TInvoker, typename ...>
	class Event;

	namespace internal
	{
		
		class AnyEventInvoker final : public mixins::StaticClass {};

		template <typename ... TArgs>
		class EventBase : public mixins::ReferenceClass
		{

		public:

			using Handler = std::function<void(TArgs...)>;

		private:

			template <cpputils::concepts::SimpleClass TInvoker, typename ...>
			friend class collections::Event;

			std::unordered_set<Handler*> m_handlers{};

			EventBase() = default;

			void operator()(TArgs ... _args);

		public:

			bool operator+=(Handler& _handler);
			bool operator-=(const Handler& _handler);

		};

	}

	template <cpputils::concepts::SimpleClass TInvoker, typename ... TArgs>
	class Event final : public internal::EventBase<TArgs ...>
	{

	private:

		friend TInvoker;

		void operator()(TArgs... _args) requires (!std::same_as<TInvoker, internal::AnyEventInvoker>);

	public:

		Event() = default;

		void operator()(TArgs... _args) requires std::same_as<TInvoker, internal::AnyEventInvoker>;

	};

}

#define CPPUTILS_COLLECTIONS_EVENT_IMPLEMENTATION
#include <cpputils-IMPL/collections/Event.tpp>
#undef CPPUTILS_COLLECTIONS_EVENT_IMPLEMENTATION

#endif