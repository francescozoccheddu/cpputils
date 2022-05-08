#ifndef CPPUTILS_SERIALIZATION_DESERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_DESERIALIZER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/DeserializerWorker.hpp>
#include <cpputils/concepts.hpp>
#include <concepts>
#include <type_traits>
#include <istream>

namespace cpputils::serialization
{

	namespace concepts
	{

		template<typename TWorker>
		concept DeserializerWorker = cpputils::concepts::DerivedSimpleClass<TWorker, serialization::DeserializerWorker> && std::constructible_from<TWorker, std::istream&>;

	}

	template<concepts::DeserializerWorker TWorker = DeserializerWorker>
	class Deserializer final : public mixins::ReferenceClass
	{

	private:

		TWorker m_worker;

	public:

		explicit Deserializer(std::istream& _stream);

		template<typename TData>
		Deserializer& operator>>(TData& _data);

		template<typename TData>
		TData get();

	};

}

#define CPPUTILS_SERIALIZATION_DESERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/Deserializer.tpp>
#undef CPPUTILS_SERIALIZATION_DESERIALIZER_IMPLEMENTATION

#endif