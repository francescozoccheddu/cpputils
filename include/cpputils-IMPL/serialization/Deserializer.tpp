#ifndef CPPUTILS_SERIALIZATION_DESERIALIZER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/serialization/Deserializer.hpp>

#include <type_traits>
#include <sstream>
#include <stdexcept>

namespace cpputils::serialization
{

	inline Deserializer::Deserializer(std::istream& _stream)
		: m_stream{ _stream }
	{}

	template<typename TArithmetic> requires std::is_arithmetic_v<TArithmetic> && (!std::is_const_v<TArithmetic>)
	inline void Deserializer::operator>>(TArithmetic& _data)
	{
		std::string data;
		*this >> data;
		std::istringstream stream{ data };
		stream >> _data;
	}

	template<typename TEnum> requires std::is_enum_v<TEnum> && (!std::is_const_v<TEnum>)
	void Deserializer::operator>>(TEnum& _data)
	{
		std::underlying_type_t<TEnum> underlying;
		*this >> underlying;
		_data = static_cast<TEnum>(underlying);
	}

	inline void Deserializer::operator>>(std::string& _data)
	{
		std::ostringstream data{};
		bool escaped{ false };
		char c;
		while ((c = m_stream.get()) != '\n')
		{
			if (escaped)
			{
				escaped = false;
				switch (c)
				{
					case '\\':
						data << '\\';
						break;
					case 'n':
						data << '\n';
						break;
					case '0':
						data << '\0';
						break;
					default:
						throw std::logic_error{ "unknown escape" };
						break;
				}
			}
			else
			{
				switch (c)
				{
					case '\\':
						escaped = true;
						break;
					default:
						data << c;
						break;
				}
			}
		}
		_data = data.str();
	}

	template<typename TType> requires std::is_arithmetic_v<TType> || std::is_enum_v<TType> || std::is_same_v<std::remove_const_t<TType>, std::string>
	inline TType Deserializer::get()
	{
		std::remove_const_t<TType> data;
		*this >> data;
		return data;
	}

}