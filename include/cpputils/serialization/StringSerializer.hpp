#ifndef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/SerializerWorker.hpp>
#include <cpputils/serialization/Serializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	template <concepts::SerializerWorker TWorker = SerializerWorker>
	class StringSerializer final : public mixins::ReferenceClass
	{

	private:

		std::ostringstream m_stream;
		TWorker m_worker;

	public:

		explicit StringSerializer();

		std::string string() const;

		operator std::string() const;

		friend std::ostream& operator<<(std::ostream& _stream, const StringSerializer<TWorker>& _serializer)
		{
			return _stream << _serializer.string();
		}

		template<typename TData>
		StringSerializer& operator<<(const TData& _data);

	};

}

#define CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/StringSerializer.tpp>
#undef CPPUTILS_SERIALIZATION_STRINGSERIALIZER_IMPLEMENTATION

#endif