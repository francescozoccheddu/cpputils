#ifndef CPPUTILS_COLLECTIONS_NAMER_INCLUDED
#define CPPUTILS_COLLECTIONS_NAMER_INCLUDED

#include <cpputils/mixins/ReferenceClass.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <concepts>

namespace cpputils::collections
{

	namespace concepts
	{

		template <typename TData>
		concept NamerData = std::equality_comparable<TData> && std::assignable_from<TData&, const TData&>;

	}

	template <concepts::NamerData TData>
	class Namer final : public mixins::ReferenceClass
	{

	private:

		std::unordered_map<TData, std::size_t> m_map;
		std::size_t m_nextIndex;
		std::string m_prefix;
		bool m_pad;

		std::string name(std::size_t _index) const;

		std::size_t maxIndexLength() const;

		std::string format(const std::string& _index, char _padChar) const;

	public:

		static constexpr char unknownChar{ '?' };

		Namer(const std::string& _prefix = "", bool _pad = true);

		std::size_t maxLength() const;

		std::string& prefix();
		const std::string& prefix() const;

		bool& pad();
		bool pad() const;

		std::string operator()(const TData& _data);

		std::string unknown() const;

		std::string nameOrUnknown(const TData& _data) const;
		std::string nameOrElse(const TData& _data, const std::string& _else) const;

		bool has(const TData& _data) const;
		void remove(const TData& _data);
		void removeAll();
		void reset();

	};

}

#define CPPUTILS_COLLECTIONS_NAMER_IMPLEMENTATION
#include <cpputils-IMPL/collections/Namer.tpp>
#undef CPPUTILS_COLLECTIONS_NAMER_IMPLEMENTATION

#endif