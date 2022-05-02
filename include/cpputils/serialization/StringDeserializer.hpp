#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED

#include <cpputils/serialization/Deserializer.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	class StringDeserializer : public Deserializer
	{

	private:

		std::istringstream m_stream;

	public:

		inline StringDeserializer(const std::string& _string);

	};

}

#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringDeserializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION

#endif