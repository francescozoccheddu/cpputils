#pragma once

#include <cpputils/collections/Namer.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <concepts>
#include <cmath>

namespace cpputils::collections
{

	namespace concepts
	{

		template <typename TData>
		concept SetNamerData = std::equality_comparable<TData> && std::assignable_from<TData&, const TData&>;

	}

	template <concepts::SetNamerData TData>
	class SetNamer final: public Namer<TData>
	{

	public:

		static constexpr auto alphabetChars{ std::array{
			'1','2','3','4','5','6','7','8','9',
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
		} };
		static constexpr char padChar{ '0' };
		static constexpr char unknownChar{ '?' };

	private:

		inline static const double c_alphabetCharsSizeLog{ std::log(alphabetChars.size()) };

		std::unordered_map<TData, std::size_t> m_map;
		std::size_t m_nextIndex, m_maxIndexLength;
		std::string m_prefix;
		bool m_pad;

		std::string name(std::size_t _index) const
		{
			std::string name{};
			const std::size_t maxLength{ this->maxLength() };
			name.reserve(maxLength);
			name += m_prefix;
			do
			{
				name += alphabetChars[_index % alphabetChars.size()];
				_index /= alphabetChars.size();
			}
			while (_index > 0);
			if (m_pad)
			{
				while (name.size() < maxLength)
				{
					name += padChar;
				}
			}
			return name;
		}

	public:

		SetNamer(const std::string& _prefix = "", bool _pad = true)
			: m_map{}, m_nextIndex{}, m_pad{ _pad }, m_prefix{ _prefix }, m_maxIndexLength{ 1 }
		{}

		std::size_t maxLength() const
		{
			return m_prefix.size() + m_maxIndexLength;
		}

		std::string& prefix()
		{
			return m_prefix;
		}

		const std::string& prefix() const
		{
			return m_prefix;
		}

		bool& pad()
		{
			return m_pad;
		}

		bool pad() const
		{
			return m_pad;
		}

		bool operator()(const TData& _data, std::string& _name) const override
		{
			const auto it{ m_map.find(_data) };
			if (it == m_map.end())
			{
				return false;
			}
			else
			{
				_name = name(it->second);
				return true;
			}
		}

		std::string operator()(const TData& _data) override
		{
			std::size_t index;
			{
				const auto it{ m_map.find(_data) };
				if (it == m_map.end())
				{
					index = m_nextIndex++;
					m_maxIndexLength = std::max(static_cast<std::size_t>(std::ceil(std::log(std::max(index, std::size_t{ 1 })) / c_alphabetCharsSizeLog)), std::size_t{ 1 });
					m_map.insert(it, { _data, index });
				}
				else
				{
					index = it->second;
				}
			}
			return name(index);
		}

		std::string unknown() const override
		{
			std::string name{};
			const std::size_t length{ m_prefix.size() + (m_pad ? m_maxIndexLength : 1) };
			name.reserve(length);
			name += m_prefix;
			while (name.size() < length)
			{
				name += unknownChar;
			}
			return name;
		}

		bool has(const TData& _data) const override
		{
			return m_map.contains(_data);
		}

		void remove(const TData& _data)
		{
			m_map.erase(_data);
		}

		void removeAll()
		{
			m_map.clear();
		}

		void reset()
		{
			removeAll();
			m_nextIndex = 0;
			m_maxIndexLength = 1;
		}

	};

}
