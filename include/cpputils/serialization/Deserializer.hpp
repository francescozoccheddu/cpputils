#ifndef CPPUTILS_SERIALIZATION_DESERIALIZER_INCLUDED
#define CPPUTILS_SERIALIZATION_DESERIALIZER_INCLUDED

#include <mixins/ReferenceClass.hpp>
#include <type_traits>
#include <string>
#include <istream>

namespace cpputils::serialization
{

	class Deserializer : public virtual mixins::ReferenceClass
	{

	private:

		std::istream& m_stream;

	public:

		inline explicit Deserializer(std::istream& _stream);

		template<typename TArithmetic> requires std::is_arithmetic_v<TArithmetic> && (!std::is_const_v<TArithmetic>)
		void operator>>(TArithmetic& _data);

		template<typename TEnum> requires std::is_enum_v<TEnum> && (!std::is_const_v<TEnum>)
		void operator>>(TEnum& _data);

		inline void operator>>(std::string& _data);

		template<typename TType> requires std::is_arithmetic_v<TType> || std::is_enum_v<TType> || std::is_same_v<std::remove_const_t<TType>, std::string>
		inline TType get();

	};

}

#define CPPUTILS_SERIALIZATION_DESERIALIZER_IMPLEMENTATION
#include <cpputils-IMPL/serialization/Deserializer.tpp>
#undef CPPUTILS_SERIALIZATION_DESERIALIZER_IMPLEMENTATION

#endif