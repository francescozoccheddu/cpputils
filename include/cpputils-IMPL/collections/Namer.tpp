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
	std::string Namer<TData>::name(std::size_t _index) const
	{
		std::stringstream stream{};
		stream << std::hex << std::uppercase << _index;
		return format(stream.str(), '0');
	}

	template <concepts::NamerData TData>
	std::size_t Namer<TData>::maxIndexLength() const
	{
		return std::max(static_cast<std::size_t>(std::ceil(std::log2(std::max(m_nextIndex - 1, std::size_t{ 1 })))) / 4, std::size_t{ 1 });
	}

	template <concepts::NamerData TData>
	std::string Namer<TData>::format(const std::string& _index, char _padChar) const
	{
		const std::string padding{ (m_pad && maxIndexLength() > _index.size()) ? std::string(maxIndexLength() - _index.size(), _padChar) : ""};
		return m_prefix + padding + _index;
	}

	template <concepts::NamerData TData>
	Namer<TData>::Namer(const std::string& _prefix, bool _pad)
		: m_map{}, m_nextIndex{}, m_pad{ _pad }, m_prefix{ _prefix }
	{}

	template <concepts::NamerData TData>
	std::size_t Namer<TData>::maxLength() const
	{
		return m_prefix.size() + maxIndexLength();
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
		return format({ unknownChar }, unknownChar);
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
	}

}