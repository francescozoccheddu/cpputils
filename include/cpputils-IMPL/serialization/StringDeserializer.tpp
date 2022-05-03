#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringDeserializer.hpp>

namespace cpputils::serialization
{

	template<typename TDeserializer> requires std::is_base_of_v<Deserializer, TDeserializer>
	inline StringDeserializer<TDeserializer>::StringDeserializer(const std::string& _string)
		: m_stream{ _string }, TDeserializer{ m_stream }
	{}

}