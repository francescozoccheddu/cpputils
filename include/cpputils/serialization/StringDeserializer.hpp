#ifndef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/DeserializerWorker.hpp>
#include <cpputils/serialization/Deserializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	template <concepts::DeserializerWorker TWorker = DeserializerWorker>
	class StringDeserializer final : public mixins::ReferenceClass
	{

	private:

		std::istringstream m_stream;
		Deserializer<TWorker> m_deserializer;

	public:

		explicit StringDeserializer(const std::string& _string);

		Deserializer<TWorker>& deserializer();
		const Deserializer<TWorker>& deserializer() const;

	};

}

#define CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringDeserializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGDESERIALIZER_IMPLEMENTATION

#endif