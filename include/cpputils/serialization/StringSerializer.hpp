#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED

#include <cpputils/serialization/Serializer.hpp>
#include <type_traits>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	namespace concepts
	{

		template <typename TSerializer>
		concept Serializer = std::is_base_of_v<serialization::Serializer, TSerializer>;

	}

	template <concepts::Serializer TSerializer = Serializer>
	class StringSerializer final
	{

	private:

		std::ostringstream m_stream;
		TSerializer m_serializer;

	public:

		explicit StringSerializer();

		std::string string() const;

		template <concepts::Serializer TSerializerSerializer>
		friend std::ostream& operator<<(std::ostream& _stream, const StringSerializer<TSerializerSerializer>& _serializer)
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