#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringSerializer.hpp>

namespace cpputils::serialization
{

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	StringSerializer<TSerializer>::StringSerializer()
		: m_stream{}, m_serializer{ m_stream }
	{}

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	std::string StringSerializer<TSerializer>::string() const
	{
		return m_stream.str();
	}

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	TSerializer& StringSerializer<TSerializer>::serializer()
	{
		return m_serializer;
	}

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	const TSerializer& StringSerializer<TSerializer>::serializer() const
	{
		return m_serializer;
	}

}