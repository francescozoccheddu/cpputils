#ifndef CPPUTILS_SERIALIZATION_DESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/Deserializer.hpp>

namespace cpputils::serialization
{

	template<concepts::DeserializerWorker TWorker>
	Deserializer<TWorker>::Deserializer(std::istream& _stream)
		: m_worker{ _stream }
	{}

	template<concepts::DeserializerWorker TWorker>
	template<typename TData>
	Deserializer<TWorker>& Deserializer<TWorker>::operator>>(TData& _data)
	{
		m_worker >> _data;
		return *this;
	}

	template<concepts::DeserializerWorker TWorker>
	template<typename TData>
	TData Deserializer<TWorker>::get()
	{
		TData data;
		m_worker >> data;
		return data;
	}

}