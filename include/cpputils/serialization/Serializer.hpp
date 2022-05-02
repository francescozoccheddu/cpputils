#ifndef CPPUTILS_SERIALIZATION_SERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_SERIALIZER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <type_traits>
#include <string>
#include <ostream>

namespace cpputils::serialization
{

	class Serializer : public virtual mixins::ReferenceClass
	{

	private:

		std::ostream& m_stream;

	public:

		inline Serializer(std::ostream& _stream);

		template<typename TArithmetic> requires std::is_arithmetic_v<TArithmetic>
		void operator<<(TArithmetic _data);

		template<typename TEnum> requires std::is_enum_v<TEnum>
		void operator<<(TEnum _data);

		inline void operator<<(const std::string& _data);

	};

}

#define CPPUTILS_SERIALIZATION_SERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/Serializer.tpp>
#undef CPPUTILS_SERIALIZATION_SERIALIZER_IMPLEMENTATION

#endif