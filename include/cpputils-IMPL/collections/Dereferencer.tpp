#ifndef CPPUTILS_COLLECTIONS_DEREFERENCER_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Dereferencer.hpp>

namespace cpputils::collections
{

	CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINED_TEMPLATE
	TView& CPPUTILS_COLLECTIONS_DEREFERENCER::dereference(TClass* _pointer)
	{
		return *reinterpret_cast<TView*>(_pointer);
	}

	CPPUTILS_COLLECTIONS_DEREFERENCER_CONSTRAINED_TEMPLATE
	const TView& CPPUTILS_COLLECTIONS_DEREFERENCER::dereferenceConst(const TClass* _pointer)
	{
		return *reinterpret_cast<const TView*>(_pointer);
	}

}