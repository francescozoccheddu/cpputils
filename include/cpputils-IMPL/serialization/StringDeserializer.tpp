#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringDeserializer.hpp>

namespace cpputils::serialization
{

	template<typename TDeserializer> requires std::is_base_of_v<Deserializer, TDeserializer>
	StringDeserializer<TDeserializer>::StringDeserializer(const std::string& _string)
		: m_stream{ _string }, m_deserializer{ m_stream }
	{}

	template<typename TDeserializer> requires std::is_base_of_v<Deserializer, TDeserializer>
	TDeserializer& StringDeserializer<TDeserializer>::deserializer()
	{
		return m_deserializer;
	}

	template<typename TDeserializer> requires std::is_base_of_v<Deserializer, TDeserializer>
	const TDeserializer& StringDeserializer<TDeserializer>::deserializer() const
	{
		return m_deserializer;
	}

}