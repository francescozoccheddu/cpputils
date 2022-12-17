#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/DeserializerWorker.hpp>
#include <cpputils/concepts.hpp>
#include <concepts>
#include <type_traits>
#include <istream>

namespace cpputils::serialization
{

	namespace concepts
	{

		template<typename TWorker>
		concept DeserializerWorker = cpputils::concepts::DerivedSimpleClass<TWorker, serialization::DeserializerWorker> && std::constructible_from<TWorker, std::istream&>;

	}

	template<concepts::DeserializerWorker TWorker = DeserializerWorker>
	class Deserializer final: public mixins::ReferenceClass
	{

	private:

		TWorker m_worker;

	public:

		Deserializer(std::istream& _stream)
			: m_worker{ _stream }
		{}

		template<typename TData>
		Deserializer<TWorker>& operator>>(TData& _data)
		{
			m_worker >> _data;
			return *this;
		}

		template<typename TData>
		TData get()
		{
			TData data;
			m_worker >> data;
			return data;
		}

	};

}
