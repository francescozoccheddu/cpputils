#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/SerializerWorker.hpp>
#include <cpputils/concepts.hpp>
#include <concepts>
#include <type_traits>
#include <ostream>

namespace cpputils::serialization
{

	namespace concepts
	{

		template<typename TWorker>
		concept SerializerWorker = cpputils::concepts::DerivedSimpleClass<TWorker, serialization::SerializerWorker> && std::constructible_from<TWorker, std::ostream&>;

	}

	template<concepts::SerializerWorker TWorker = SerializerWorker>
	class Serializer final: public mixins::ReferenceClass
	{

	private:

		TWorker m_worker;

	public:

		Serializer(std::ostream& _stream)
			: m_worker{ _stream }
		{}

		template<typename TData>
		Serializer<TWorker>& operator<<(const TData& _data)
		{
			m_worker << _data;
			return *this;
		}

	};

}
