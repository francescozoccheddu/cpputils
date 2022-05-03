#ifndef CPPUTILS_COLLECTIONS_EVENT_INCLUDED
#define CPPUTILS_COLLECTIONS_EVENT_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/mixins/StaticClass.hpp>
#include <functional>
#include <unordered_set>

#define CPPUTILS_COLLECTIONS_EVENT_TEMPLATE template<typename TInvoker, typename ... TArgs>

#define CPPUTILS_COLLECTIONS_EVENT_ARGS <TInvoker, TArgs ...>

#define CPPUTILS_COLLECTIONS_EVENT_CONSTRAINT requires internal::IsValidEvent<TInvoker>

#define CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE CPPUTILS_COLLECTIONS_EVENT_TEMPLATE CPPUTILS_COLLECTIONS_EVENT_CONSTRAINT

#define CPPUTILS_COLLECTIONS_EVENT Event CPPUTILS_COLLECTIONS_EVENT_ARGS

namespace cpputils::collections
{

	namespace internal
	{

		template<typename TInvoker> concept IsValidEvent = std::is_class_v<TInvoker> && (!std::is_const_v<TInvoker>);

	}

	CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE class Event;

	namespace internal
	{

		template<typename ... TArgs>
		class EventBase : public mixins::ReferenceClass
		{

		public:

			using Handler = std::function<void(TArgs...)>;

		private:

			CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE friend class Event;

			std::unordered_set<Handler*> m_handlers{};

			EventBase() = default;

			void operator()(TArgs ... _args);

		public:

			bool operator+=(Handler& _handler);
			bool operator-=(const Handler& _handler);

		};

		class AnyEventInvoker final : public mixins::StaticClass {};

	}


	CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE
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

#undef CPPUTILS_COLLECTIONS_EVENT_TEMPLATE
#undef CPPUTILS_COLLECTIONS_EVENT_ARGS
#undef CPPUTILS_COLLECTIONS_EVENT_CONSTRAINT
#undef CPPUTILS_COLLECTIONS_EVENT_CONSTRAINED_TEMPLATE
#undef CPPUTILS_COLLECTIONS_EVENT

#endif