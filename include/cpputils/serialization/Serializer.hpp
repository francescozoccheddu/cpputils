#ifndef CPPUTILS_SERIALIZATION_SERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_SERIALIZER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/SerializerWorker.hpp>
#include <cpputils/concepts.hpp>
#include <concepts>
#include <type_traits>
#include <ostream>

namespace cpputils::serialization
{

	namespace concepts
	{

		template<typename TWorker>
		concept SerializerWorker = cpputils::concepts::DerivedSimpleClass<TWorker, serialization::SerializerWorker> && std::constructible_from<TWorker, std::ostream&>;

	}

	template<concepts::SerializerWorker TWorker = SerializerWorker>
	class Serializer final : public mixins::ReferenceClass
	{

	private:

		TWorker m_worker;

	public:

		explicit Serializer(std::ostream& _stream);

		template<typename TData>
		Serializer& operator<<(const TData& _data);

	};

}

#define CPPUTILS_SERIALIZATION_SERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/Serializer.tpp>
#undef CPPUTILS_SERIALIZATION_SERIALIZER_IMPLEMENTATION

#endif