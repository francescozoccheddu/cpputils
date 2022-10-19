#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringDeserializer.hpp>

namespace cpputils::serialization
{

	template <concepts::DeserializerWorker TWorker>
	StringDeserializer<TWorker>::StringDeserializer(const std::string& _string)
		: m_stream{ _string }, m_deserializer{ m_stream }
	{}

	template <concepts::DeserializerWorker TWorker>
	StringDeserializer<TWorker>::StringDeserializer(std::string_view _string)
		: StringDeserializer{ std::string{_string} }
	{}

	template <concepts::DeserializerWorker TWorker>
	StringDeserializer<TWorker>::StringDeserializer(const char* _string)
		: StringDeserializer{ std::string{_string} }
	{}

	template <concepts::DeserializerWorker TWorker>
	Deserializer<TWorker>& StringDeserializer<TWorker>::deserializer()
	{
		return m_deserializer;
	}

	template <concepts::DeserializerWorker TWorker>
	const Deserializer<TWorker>& StringDeserializer<TWorker>::deserializer() const
	{
		return m_deserializer;
	}

}