#ifndef CPPUTILS_COLLECTIONS_NAMER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Namer.hpp>

namespace cpputils::collections
{

	template <typename TData>
	std::string Namer<TData>::unknown() const
	{
		return { '?' };
	}

	template <typename TData>
	bool Namer<TData>::has(const TData& _data) const
	{
		std::string name;
		return operator()(_data, name);
	}

	template <typename TData>
	std::string Namer<TData>::nameOrUnknown(const TData& _data) const
	{
		return nameOrElse(_data, unknown());
	}

	template <typename TData>
	std::string Namer<TData>::nameOrElse(const TData& _data, const std::string& _else) const
	{
		std::string name;
		return operator()(_data, name) ? name : _else;
	}

}