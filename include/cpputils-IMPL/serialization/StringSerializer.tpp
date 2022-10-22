#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringSerializer.hpp>

namespace cpputils::serialization
{

	template <concepts::SerializerWorker TWorker>
	StringSerializer<TWorker>::StringSerializer()
		: m_stream{}, m_serializer{ m_stream }
	{}

	template <concepts::SerializerWorker TWorker>
	StringSerializer<TWorker>::operator std::string() const
	{
		return m_stream.str();
	}

	template <concepts::SerializerWorker TWorker>
	std::string StringSerializer<TWorker>::string() const
	{
		return m_stream.str();
	}

	template <concepts::SerializerWorker TWorker>
	Serializer<TWorker>& StringSerializer<TWorker>::serializer()
	{
		return m_serializer;
	}

	template <concepts::SerializerWorker TWorker>
	const Serializer<TWorker>& StringSerializer<TWorker>::serializer() const
	{
		return m_serializer;
	}


}