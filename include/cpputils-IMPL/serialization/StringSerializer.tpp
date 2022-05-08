#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringSerializer.hpp>

namespace cpputils::serialization
{

	template <concepts::SerializerWorker TWorker>
	StringSerializer<TWorker>::StringSerializer()
		: m_stream{}, m_worker{ m_stream }
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
	template<typename TData>
	StringSerializer<TWorker>& StringSerializer<TWorker>::operator<<(const TData& _data)
	{
		m_worker << _data;
		return *this;
	}

}