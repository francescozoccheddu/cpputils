#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringSerializer.hpp>

namespace cpputils::serialization
{

	template <cpputils::concepts::DerivedSimpleClass<Serializer> TSerializer>
	StringSerializer<TSerializer>::StringSerializer()
		: m_stream{}, m_serializer{ m_stream }
	{}

	template <cpputils::concepts::DerivedSimpleClass<Serializer> TSerializer>
	std::string StringSerializer<TSerializer>::string() const
	{
		return m_stream.str();
	}

	template <cpputils::concepts::DerivedSimpleClass<Serializer> TSerializer>
	TSerializer& StringSerializer<TSerializer>::serializer()
	{
		return m_serializer;
	}

	template <cpputils::concepts::DerivedSimpleClass<Serializer> TSerializer>
	const TSerializer& StringSerializer<TSerializer>::serializer() const
	{
		return m_serializer;
	}

}