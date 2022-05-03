#ifndef CPPUTILS_COLLECTIONS_DEREFERENCER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Dereferencer.hpp>

namespace cpputils::collections
{

	template<typename TClass, typename TView> requires internal::IsValidDereferencer<TClass, TView>
	TView& Dereferencer<TClass, TView>::dereference(TClass* _pointer)
	{
		return *reinterpret_cast<TView*>(_pointer);
	}

	template<typename TClass, typename TView> requires internal::IsValidDereferencer<TClass, TView>
	const TView& Dereferencer<TClass, TView>::dereferenceConst(const TClass* _pointer)
	{
		return *reinterpret_cast<const TView*>(_pointer);
	}

}