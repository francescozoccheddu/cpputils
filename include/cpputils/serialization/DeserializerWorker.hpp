#ifndef CPPUTILS_SERIALIZATION_DESERIALIZERWORKER_INCLUDED
#define CPPUTILS_SERIALIZATION_DESERIALIZERWORKER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <type_traits>
#include <string>
#include <istream>

namespace cpputils::serialization
{

	class DeserializerWorker : public virtual mixins::ReferenceClass
	{

	private:

		std::istream& m_stream;

	public:

		inline explicit DeserializerWorker(std::istream& _stream);

		template <typename TArithmetic> requires std::is_arithmetic_v<TArithmetic> && (!std::is_const_v<TArithmetic>)
		DeserializerWorker& operator>>(TArithmetic& _data);

		template <typename TEnum> requires std::is_enum_v<TEnum> && (!std::is_const_v<TEnum>)
		DeserializerWorker& operator>>(TEnum& _data);

		inline DeserializerWorker& operator>>(std::string& _data);

	};

}

#define CPPUTILS_SERIALIZATION_DESERIALIZERWORKER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/DeserializerWorker.tpp>
#undef CPPUTILS_SERIALIZATION_DESERIALIZERWORKER_IMPLEMENTATION

#endif