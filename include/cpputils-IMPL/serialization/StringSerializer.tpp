#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringSerializer.hpp>

namespace cpputils::serialization
{

	inline StringSerializer::StringSerializer()
		: m_stream{}, Serializer{ m_stream }
	{}

	inline std::string StringSerializer::string() const
	{
		return m_stream.str();
	}

	inline std::ostream& operator<<(std::ostream& _stream, const StringSerializer& _serializer)
	{
		return _stream << _serializer.string();
	}

}