#ifndef CPPUTILS_COLLECTIONS_NAMER_INCLUDED
#define CPPUTILS_COLLECTIONS_NAMER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <string>

namespace cpputils::collections
{

	template <typename TData>
	class Namer : public virtual mixins::ReferenceClass
	{

	public:

		virtual std::string unknown() const;

		virtual std::string operator()(const TData& _data) = 0;
		virtual bool operator()(const TData& _data, std::string& _name) const = 0;

		virtual bool has(const TData& _data) const;
		virtual std::string nameOrUnknown(const TData& _data) const;
		virtual std::string nameOrElse(const TData& _data, const std::string& _else) const;

	};

}

#define CPPUTILS_COLLECTIONS_NAMER_IMPLEMENTATION
#include <cpputils-IMPL/collections/Namer.tpp>
#undef CPPUTILS_COLLECTIONS_NAMER_IMPLEMENTATION

#endif