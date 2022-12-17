#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <type_traits>
#include <string>
#include <string_view>
#include <ostream>

namespace cpputils::serialization
{

	class SerializerWorker: public virtual mixins::ReferenceClass
	{

	private:

		std::ostream& m_stream;

	public:

		inline SerializerWorker(std::ostream& _stream)
			: m_stream{ _stream }
		{}

		template <typename TArithmetic> requires std::is_arithmetic_v<TArithmetic>
		inline SerializerWorker& operator<<(TArithmetic _data)
		{
			return *this << std::to_string(_data);
		}

		template <typename TEnum> requires std::is_enum_v<TEnum>
		SerializerWorker& operator<<(TEnum _data)
		{
			return *this << static_cast<std::underlying_type_t<TEnum>>(_data);
		}

		inline SerializerWorker& operator<<(const std::string& _data)
		{
			return *this << std::string_view{ _data };
		}

		inline SerializerWorker& operator<<(std::string_view _data)
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
			return *this;
		}

		inline SerializerWorker& operator<<(const char* _data)
		{
			return *this << std::string_view{ _data };
		}

	};

}
