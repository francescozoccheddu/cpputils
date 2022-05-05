#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED

#include <cpputils/serialization/Serializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	template <cpputils::concepts::DerivedSimpleClass<Serializer> TSerializer = Serializer>
	class StringSerializer final
	{

	private:

		std::ostringstream m_stream;
		TSerializer m_serializer;

	public:

		explicit StringSerializer();

		std::string string() const;

		template <cpputils::concepts::DerivedSimpleClass<Serializer> TOtherSerializer>
		friend std::ostream& operator<<(std::ostream& _stream, const StringSerializer<TOtherSerializer>& _serializer)
		{
			return _stream << _serializer.string();
		}

		TSerializer& serializer();
		const TSerializer& serializer() const;

	};

}

#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringSerializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION

#endif