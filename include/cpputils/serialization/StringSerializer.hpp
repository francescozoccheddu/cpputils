#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED

#include <cpputils/serialization/Serializer.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	class StringSerializer : public Serializer
	{

	private:

		std::ostringstream m_stream;

	public:

		inline StringSerializer();

		inline std::string string() const;

		inline friend std::ostream& operator<<(std::ostream& _stream, const StringSerializer& _serializer);

	};

}

#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringSerializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION

#endif