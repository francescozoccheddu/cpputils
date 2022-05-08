#ifndef CPPUTILS_SERIALIZATION_SERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/Serializer.hpp>

namespace cpputils::serialization
{

	template<concepts::SerializerWorker TWorker>
	Serializer<TWorker>::Serializer(std::ostream& _stream)
		: m_worker{ _stream }
	{}

	template<concepts::SerializerWorker TWorker>
	template<typename TData>
	Serializer<TWorker>& Serializer<TWorker>::operator<<(const TData& _data)
	{
		m_worker << _data;
		return *this;
	}

}