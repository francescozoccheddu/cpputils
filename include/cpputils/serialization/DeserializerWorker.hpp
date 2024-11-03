#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <type_traits>
#include <string>
#include <istream>
#include <sstream>

namespace cpputils::serialization
{

	class DeserializerWorker: public virtual mixins::ReferenceClass
	{

	private:

		std::istream& m_stream;

	public:

		inline DeserializerWorker(std::istream& _stream)
			: m_stream{ _stream }
		{}

		template <typename TArithmetic> requires std::is_arithmetic_v<TArithmetic> && (!std::is_const_v<TArithmetic>)
			inline DeserializerWorker& operator>>(TArithmetic& _data)
		{
			std::string data;
			*this >> data;
			std::istringstream stream{ data };
			stream >> _data;
			return *this;
		}

		template <typename TEnum> requires std::is_enum_v<TEnum> && (!std::is_const_v<TEnum>)
			DeserializerWorker& operator>>(TEnum& _data)
		{
			std::underlying_type_t<TEnum> underlying;
			*this >> underlying;
			_data = static_cast<TEnum>(underlying);
			return *this;
		}

		inline DeserializerWorker& operator>>(std::string& _data)
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
			return *this;
		}


	};

}

