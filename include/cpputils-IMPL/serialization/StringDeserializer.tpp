#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringDeserializer.hpp>

namespace cpputils::serialization
{

	inline StringDeserializer::StringDeserializer(const std::string& _string)
		: m_stream{ _string }, Deserializer{ m_stream }
	{}

}