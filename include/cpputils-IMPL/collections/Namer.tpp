#ifndef CPPUTILS_COLLECTIONS_NAMER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Namer.hpp>

#include <algorithm>
#include <cmath>
#include <sstream>
#include <ios>

namespace cpputils::collections
{

	template <concepts::NamerData TData>
	const double Namer<TData>::c_alphabetCharsSizeLog{ std::log(alphabetChars.size()) };

	template <concepts::NamerData TData>
	std::string Namer<TData>::name(std::size_t _index) const
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

	template <concepts::NamerData TData>
	Namer<TData>::Namer(const std::string& _prefix, bool _pad)
		: m_map{}, m_nextIndex{}, m_pad{ _pad }, m_prefix{ _prefix }, m_maxIndexLength{ 1 }
	{}

	template <concepts::NamerData TData>
	std::size_t Namer<TData>::maxLength() const
	{
		return m_prefix.size() + m_maxIndexLength;
	}

	template <concepts::NamerData TData>
	std::string& Namer<TData>::prefix()
	{
		return m_prefix;
	}

	template <concepts::NamerData TData>
	const std::string& Namer<TData>::prefix() const
	{
		return m_prefix;
	}

	template <concepts::NamerData TData>
	bool& Namer<TData>::pad()
	{
		return m_pad;
	}

	template <concepts::NamerData TData>
	bool Namer<TData>::pad() const
	{
		return m_pad;
	}

	template <concepts::NamerData TData>
	std::string Namer<TData>::operator()(const TData& _data)
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

	template <concepts::NamerData TData>
	std::string Namer<TData>::unknown() const
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

	template <concepts::NamerData TData>
	std::string Namer<TData>::nameOrUnknown(const TData& _data) const
	{
		return nameOrElse(_data, unknown());
	}

	template <concepts::NamerData TData>
	std::string Namer<TData>::nameOrElse(const TData& _data, const std::string& _else) const
	{
		const auto it{ m_map.find(_data) };
		return (it == m_map.end()) ? _else : name(it->second);
	}

	template <concepts::NamerData TData>
	bool Namer<TData>::has(const TData& _data) const
	{
		m_map.erase(_data);
	}

	template <concepts::NamerData TData>
	void Namer<TData>::remove(const TData& _data)
	{
		m_map.erase(_data);
	}

	template <concepts::NamerData TData>
	void Namer<TData>::removeAll()
	{
		m_map.clear();
	}

	template <concepts::NamerData TData>
	void Namer<TData>::reset()
	{
		removeAll();
		m_nextIndex = 0;
		m_maxIndexLength = 1;
	}

}