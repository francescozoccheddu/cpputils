#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <cpputils/serialization/SerializerWorker.hpp>
#include <cpputils/serialization/Serializer.hpp>
#include <cpputils/concepts.hpp>
#include <sstream>
#include <string>

namespace cpputils::serialization
{

	template <concepts::SerializerWorker TWorker = SerializerWorker>
	class StringSerializer final: public mixins::ReferenceClass
	{

	private:

		std::ostringstream m_stream;
		Serializer<TWorker> m_serializer;

	public:

		explicit StringSerializer()
			: m_stream{}, m_serializer{ m_stream }
		{}

		operator std::string() const
		{
			return m_stream.str();
		}

		std::string string() const
		{
			return m_stream.str();
		}

		friend std::ostream& operator<<(std::ostream& _stream, const StringSerializer<TWorker>& _serializer)
		{
			return _stream << _serializer.string();
		}

		Serializer<TWorker>& serializer()
		{
			return m_serializer;
		}

		const Serializer<TWorker>& serializer() const
		{
			return m_serializer;
		}

		template<typename TData>
		StringSerializer& operator<<(const TData& _data)
		{
			m_serializer << _data;
			return *this;
		}

	};

}
