#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringSerializer.hpp>

namespace cpputils::serialization
{

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	inline StringSerializer<TSerializer>::StringSerializer()
		: m_stream{}, TSerializer{ m_stream }
	{}

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	inline std::string StringSerializer<TSerializer>::string() const
	{
		return m_stream.str();
	}

	template<typename TSerializer> requires std::is_base_of_v<Serializer, TSerializer>
	inline std::ostream& operator<<(std::ostream& _stream, const StringSerializer<TSerializer>& _serializer)
	{
		return _stream << _serializer.string();
	}

}