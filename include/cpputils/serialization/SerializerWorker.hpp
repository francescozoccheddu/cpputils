#ifndef CPPUTILS_SERIALIZATION_SERIALIZERWORKER_INCLUDED
#define CPPUTILS_SERIALIZATION_SERIALIZERWORKER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <type_traits>
#include <string>
#include <string_view>
#include <ostream>

namespace cpputils::serialization
{

	class SerializerWorker : public virtual mixins::ReferenceClass
	{

	private:

		std::ostream& m_stream;

	public:

		inline explicit SerializerWorker(std::ostream& _stream);

		template <typename TArithmetic> requires std::is_arithmetic_v<TArithmetic>
		SerializerWorker& operator<<(TArithmetic _data);

		template <typename TEnum> requires std::is_enum_v<TEnum>
		SerializerWorker& operator<<(TEnum _data);

		inline SerializerWorker& operator<<(const std::string& _data);

		inline SerializerWorker& operator<<(std::string_view _data);

		inline SerializerWorker& operator<<(const char* _data);

	};

}

#define CPPUTILS_SERIALIZATION_SERIALIZERWORKER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/SerializerWorker.tpp>
#undef CPPUTILS_SERIALIZATION_SERIALIZERWORKER_IMPLEMENTATION

#endif