#pragma once

#include <cpputils/mixins/ReferenceClass.hpp>
#include <string>

namespace cpputils::collections
{

	template <typename TData>
	class Namer: public virtual mixins::ReferenceClass
	{

	public:

		virtual std::string operator()(const TData& _data) = 0;
		virtual bool operator()(const TData& _data, std::string& _name) const = 0;

		virtual std::string unknown() const
		{
			return { '?' };
		}

		virtual bool has(const TData& _data) const
		{
			std::string name;
			return operator()(_data, name);
		}

		virtual std::string nameOrUnknown(const TData& _data) const
		{
			return nameOrElse(_data, unknown());
		}

		virtual std::string nameOrElse(const TData& _data, const std::string& _else) const
		{
			std::string name;
			return operator()(_data, name) ? name : _else;
		}

	};

}
