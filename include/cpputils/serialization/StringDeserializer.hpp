#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/DeserializerWorker.hpp>
#include <cpputils/serialization/Deserializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>
#include <string_view>

namespace cpputils::serialization
{

	template <concepts::DeserializerWorker TWorker = DeserializerWorker>
	class StringDeserializer final: public mixins::ReferenceClass
	{

	private:

		std::istringstream m_stream;
		Deserializer<TWorker> m_deserializer;

	public:

		explicit StringDeserializer(const std::string& _string)
			: m_stream{ _string }, m_deserializer{ m_stream }
		{}

		explicit StringDeserializer(std::string_view _string)
			: StringDeserializer{ std::string{_string} }
		{}

		explicit StringDeserializer(const char* _string)
			: StringDeserializer{ std::string{_string} }
		{}

		Deserializer<TWorker>& deserializer()
		{
			return m_deserializer;
		}

		const Deserializer<TWorker>& deserializer() const
		{
			return m_deserializer;
		}

		template<typename TData>
		StringDeserializer& operator>>(TData& _data)
		{
			m_deserializer >> _data;
			return *this;
		}

		template<typename TData>
		TData get()
		{
			TData data;
			m_deserializer >> data;
			return data;
		}

	};

}
