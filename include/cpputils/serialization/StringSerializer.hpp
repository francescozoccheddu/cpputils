#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/SerializerWorker.hpp>
#include <cpputils/serialization/Serializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>
#include <string_view>

namespace cpputils::serialization
{

	template <concepts::SerializerWorker TWorker = SerializerWorker>
	class StringSerializer final : public mixins::ReferenceClass
	{

	private:

		std::ostringstream m_stream;
		Serializer<TWorker> m_serializer;

	public:

		explicit StringSerializer();

		std::string string() const;

		const char* cstr() const;

		std::string_view stringView() const;

		operator std::string() const;

		operator std::string_view() const;
		
		operator const char*() const;

		friend std::ostream& operator<<(std::ostream& _stream, const StringSerializer<TWorker>& _serializer)
		{
			return _stream << _serializer.string();
		}

		Serializer<TWorker>& serializer();
		const Serializer<TWorker>& serializer() const;

	};

}

#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringSerializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION

#endif