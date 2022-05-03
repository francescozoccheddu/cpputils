#ifndef CPPUTILS_SERIALIZATION_SERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/Serializer.hpp>

#include <type_traits>
#include <string>
#include <algorithm>

namespace cpputils::serialization
{

	inline Serializer::Serializer(std::ostream& _stream)
		: m_stream{ _stream }
	{}

	template<typename TArithmetic> requires std::is_arithmetic_v<TArithmetic>
	inline void Serializer::operator<<(TArithmetic _data)
	{
		*this << std::to_string(_data);
	}

	template<typename TEnum> requires std::is_enum_v<TEnum>
	void Serializer::operator<<(TEnum _data)
	{
		*this << static_cast<std::underlying_type_t<TEnum>>(_data);
	}

	inline void Serializer::operator<<(const std::string& _data)
	{
		for (const char c : _data)
		{
			switch (c)
			{
				case '\\':
					m_stream << '\\' << '\\';
					break;
				case '\n':
					m_stream << '\\' << 'n';
					break;
				case '\0':
					m_stream << '\\' << '0';
					break;
				default:
					m_stream << c;
					break;
			}
		}
		m_stream << '\n';
	}

}