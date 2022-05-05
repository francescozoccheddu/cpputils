#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED

#include <cpputils/serialization/Deserializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	template <cpputils::concepts::DerivedSimpleClass<Deserializer> TDeserializer = Deserializer>
	class StringDeserializer final
	{

	private:

		std::istringstream m_stream;
		TDeserializer m_deserializer;

	public:

		explicit StringDeserializer(const std::string& _string);

		TDeserializer& deserializer();
		const TDeserializer& deserializer() const;

	};

}

#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringDeserializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION

#endif