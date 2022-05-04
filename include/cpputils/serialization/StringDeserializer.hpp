#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED

#include <cpputils/serialization/Deserializer.hpp>
#include <type_traits>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	template<typename TDeserializer = Deserializer> requires std::is_base_of_v<Deserializer, TDeserializer>
	class StringDeserializer final : public TDeserializer
	{

	private:

		std::istringstream m_stream;

	public:

		inline explicit StringDeserializer(const std::string& _string);

	};

}

#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringDeserializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION

#endif