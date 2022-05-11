#ifndef CPPUTILS_COLLECTIONS_SETNAMER_INCLUDED
#define CPPUTILS_COLLECTIONS_SETNAMER_INCLUDED

#include <cpputils/collections/Namer.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <concepts>

namespace cpputils::collections
{

	namespace concepts
	{

		template <typename TData>
		concept SetNamerData = std::equality_comparable<TData> && std::assignable_from<TData&, const TData&>;

	}

	template <concepts::SetNamerData TData>
	class SetNamer final : public Namer<TData>
	{

	private:

		static const double c_alphabetCharsSizeLog;

		std::unordered_map<TData, std::size_t> m_map;
		std::size_t m_nextIndex, m_maxIndexLength;
		std::string m_prefix;
		bool m_pad;

		std::string name(std::size_t _index) const;

	public:

		static constexpr auto alphabetChars{ std::array{
			'1','2','3','4','5','6','7','8','9',
			'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
		} };
		static constexpr char padChar{ '0' };
		static constexpr char unknownChar{ '?' };

		SetNamer(const std::string& _prefix = "", bool _pad = true);

		std::size_t maxLength() const;

		std::string& prefix();
		const std::string& prefix() const;

		bool& pad();
		bool pad() const;

		bool operator()(const TData& _data, std::string& _name) const override;
		std::string operator()(const TData& _data) override;

		std::string unknown() const override;

		bool has(const TData& _data) const override;
		void remove(const TData& _data);
		void removeAll();
		void reset();

	};

}

#define CPPUTILS_COLLECTIONS_SETNAMER_IMPLEMENTATION
#include <cpputils-IMPL/collections/SetNamer.tpp>
#undef CPPUTILS_COLLECTIONS_SETNAMER_IMPLEMENTATION

#endif