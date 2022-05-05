#ifndef CPPUTILS_COLLECTIONS_EVENT_INCLUDED
#define CPPUTILS_COLLECTIONS_EVENT_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/mixins/StaticClass.hpp>
#include <functional>
#include <unordered_set>

namespace cpputils::collections
{

	template <typename TInvoker, typename ...>
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

			template <typename TInvoker, typename ...>
			friend class collections::Event;

			std::unordered_set<Handler*> m_handlers{};

			EventBase() = default;

			void operator()(TArgs ... _args);

		public:

			bool operator+=(Handler& _handler);
			bool operator-=(const Handler& _handler);

		};

	}

	template <typename TInvoker, typename ... TArgs>
	class Event final : public internal::EventBase<TArgs ...>
	{

	private:

		friend TInvoker;

		void operator()(TArgs... _args) requires (!std::is_same_v<TInvoker, internal::AnyEventInvoker>);

	public:

		Event() = default;

		void operator()(TArgs... _args) requires std::is_same_v<TInvoker, internal::AnyEventInvoker>;

	};

}

#define CPPUTILS_COLLECTIONS_EVENT_IMPLEMENTATION
#include <cpputils-IMPL/collections/Event.tpp>
#undef CPPUTILS_COLLECTIONS_EVENT_IMPLEMENTATION

#endif