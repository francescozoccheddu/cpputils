#ifndef CPPUTILS_COLLECTIONS_SETNAMER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/SetNamer.hpp>

#include <algorithm>
#include <cmath>
#include <sstream>
#include <ios>

namespace cpputils::collections
{

	template <concepts::SetNamerData TData>
	const double SetNamer<TData>::c_alphabetCharsSizeLog{ std::log(alphabetChars.size()) };

	template <concepts::SetNamerData TData>
	std::string SetNamer<TData>::name(std::size_t _index) const
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

	template <concepts::SetNamerData TData>
	SetNamer<TData>::SetNamer(const std::string& _prefix, bool _pad)
		: m_map{}, m_nextIndex{}, m_pad{ _pad }, m_prefix{ _prefix }, m_maxIndexLength{ 1 }
	{}

	template <concepts::SetNamerData TData>
	std::size_t SetNamer<TData>::maxLength() const
	{
		return m_prefix.size() + m_maxIndexLength;
	}

	template <concepts::SetNamerData TData>
	std::string& SetNamer<TData>::prefix()
	{
		return m_prefix;
	}

	template <concepts::SetNamerData TData>
	const std::string& SetNamer<TData>::prefix() const
	{
		return m_prefix;
	}

	template <concepts::SetNamerData TData>
	bool& SetNamer<TData>::pad()
	{
		return m_pad;
	}

	template <concepts::SetNamerData TData>
	bool SetNamer<TData>::pad() const
	{
		return m_pad;
	}

	template <concepts::SetNamerData TData>
	bool SetNamer<TData>::operator()(const TData& _data, std::string& _name) const
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

	template <concepts::SetNamerData TData>
	std::string SetNamer<TData>::operator()(const TData& _data)
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

	template <concepts::SetNamerData TData>
	std::string SetNamer<TData>::unknown() const
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

	template <concepts::SetNamerData TData>
	bool SetNamer<TData>::has(const TData& _data) const
	{
		return m_map.contains(_data);
	}

	template <concepts::SetNamerData TData>
	void SetNamer<TData>::remove(const TData& _data)
	{
		m_map.erase(_data);
	}

	template <concepts::SetNamerData TData>
	void SetNamer<TData>::removeAll()
	{
		m_map.clear();
	}

	template <concepts::SetNamerData TData>
	void SetNamer<TData>::reset()
	{
		removeAll();
		m_nextIndex = 0;
		m_maxIndexLength = 1;
	}

}