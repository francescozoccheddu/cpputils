#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/StringDeserializer.hpp>

namespace cpputils::serialization
{

	template <concepts::DeserializerWorker TWorker>
	StringDeserializer<TWorker>::StringDeserializer(const std::string& _string)
		: m_stream{ _string }, m_worker{ m_stream }
	{}

	template <concepts::DeserializerWorker TWorker>
	template<typename TData>
	StringDeserializer<TWorker>& StringDeserializer<TWorker>::operator>>(TData& _data)
	{
		m_worker >> _data;
		return *this;
	}

	template <concepts::DeserializerWorker TWorker>
	template<typename TData>
	TData StringDeserializer<TWorker>::get()
	{
		TData data;
		m_worker >> data;
		return data;
	}

}