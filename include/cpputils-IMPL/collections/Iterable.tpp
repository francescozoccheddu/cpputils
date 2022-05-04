#ifndef CPPUTILS_COLLECTIONS_ITERABLE_IMPLEMENTATION
#error __FILE__ should not be directly included
#endif

#include <cpputils/collections/Iterable.hpp>

#include <memory>
#include <stdexcept>

#define CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE \
template<\
	typename TIterable,\
	typename TDereferenceResult,\
	typename TDereferenceConstResult,\
	TDereferenceResult(*TConvert)(types::DereferenceResult<types::Iterator<TIterable>>),\
	TDereferenceConstResult(*TConvertConst)(types::DereferenceResult<types::ConstIterator<TIterable>>)\
>

#define CPPUTILS_COLLECTIONS_ITERABLE \
Iterable<TIterable, TDereferenceResult, TDereferenceConstResult, TConvert, TConvertConst>

namespace cpputils::collections
{

	template<typename TIterable>
	internal::IterableBase<TIterable>::IterableBase(TIterable& _iterable)
		: m_iterable{ std::addressof(_iterable) }
	{}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		const typename CPPUTILS_COLLECTIONS_ITERABLE::Predicate
		CPPUTILS_COLLECTIONS_ITERABLE::truePredicate
	{ [](const TDereferenceResult&) {return true; } };

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		const typename CPPUTILS_COLLECTIONS_ITERABLE::PredicateConst
		CPPUTILS_COLLECTIONS_ITERABLE::truePredicateConst
	{ [](const TDereferenceConstResult&) {return true; } };


	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::tryFirst(iterator& _result, const Predicate& _predicate)
	{
		iterator it{ begin() };
		const iterator end{ this->end() };
		while (it != end)
		{
			if (_predicate(*it))
			{
				_result = it;
				return true;
			}
			++it;
		}
		return false;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::tryCFirst(const_iterator& _result, const PredicateConst& _predicate) const
	{
		const_iterator it{ begin() };
		const const_iterator end{ this->end() };
		while (it != end)
		{
			if (_predicate(*it))
			{
				_result = it;
				return true;
			}
			++it;
		}
		return false;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::tryLast(reverse_iterator& _result, const Predicate& _predicate)
	{
		reverse_iterator it{ rbegin() };
		const reverse_iterator end{ rend() };
		while (it != end)
		{
			if (_predicate(*it))
			{
				_result = it;
				return true;
			}
			++it;
		}
		return false;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::tryCLast(const_reverse_iterator& _result, const PredicateConst& _predicate) const
	{
		const_reverse_iterator it{ rbegin() };
		const const_reverse_iterator end{ rend() };
		while (it != end)
		{
			if (_predicate(*it))
			{
				_result = it;
				return true;
			}
			++it;
		}
		return false;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::trySingle(iterator& _result, const Predicate& _predicate)
	{
		iterator it{ begin() };
		const iterator end{ this->end() };
		iterator candidate{ end };
		while (it != end)
		{
			if (_predicate(*it))
			{
				if (candidate != end)
				{
					return 2;
				}
				candidate = it;
			}
			++it;
		}
		if (candidate != end)
		{
			_result = candidate;
		}
		return 0;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::tryCSingle(const_iterator& _result, const PredicateConst& _predicate) const
	{
		const_iterator it{ begin() };
		const const_iterator end{ this->end() };
		const_iterator candidate{ end };
		while (it != end)
		{
			if (_predicate(*it))
			{
				if (candidate != end)
				{
					return 2;
				}
				candidate = it;
			}
			++it;
		}
		if (candidate != end)
		{
			_result = candidate;
		}
		return 0;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::Iterable(TIterable& _iterable)
		: internal::IterableBase<TIterable>{ _iterable }
	{}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TIterable&
		CPPUTILS_COLLECTIONS_ITERABLE::iterable() const
	{
		return *internal::IterableBase<TIterable>::m_iterable;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator
		CPPUTILS_COLLECTIONS_ITERABLE::begin()
	{
		return iterator{ iterable().begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::cbegin() const
	{
		return const_iterator{ iterable().cbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::begin() const
	{
		return const_iterator{ iterable().begin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::iterator
		CPPUTILS_COLLECTIONS_ITERABLE::end()
	{
		return iterator{ iterable().end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::cend() const
	{
		return const_iterator{ iterable().cend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::end() const
	{
		return const_iterator{ iterable().end() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::reverse_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rbegin()
	{
		return reverse_iterator{ iterable().rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_reverse_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::crbegin() const
	{
		return const_reverse_iterator{ iterable().crbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_reverse_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rbegin() const
	{
		return const_reverse_iterator{ iterable().rbegin() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::reverse_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rend()
	{
		return reverse_iterator{ iterable().rend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_reverse_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::crend() const
	{
		return const_reverse_iterator{ iterable().crend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		CPPUTILS_COLLECTIONS_ITERABLE::const_reverse_iterator
		CPPUTILS_COLLECTIONS_ITERABLE::rend() const
	{
		return const_reverse_iterator{ iterable().rend() };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::size() const
	{
		return iterable().size();
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::empty() const
	{
		return iterable().empty();
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::operator[](std::size_t _index)
	{
		return begin()[_index];
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::operator[](std::size_t _index) const
	{
		return cbegin()[_index];
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(const Predicate& _predicate)
	{
		iterator it{ end() };
		if (tryFirst(it, _predicate))
		{
			return *it;
		}
		throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(const PredicateConst& _predicate) const
	{
		const_iterator it{ cend() };
		if (tryCFirst(it, _predicate))
		{
			return *it;
		}
		throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(const PredicateConst& _predicate) const
	{
		return cfirst(_predicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(const Predicate& _predicate)
	{
		reverse_iterator it{ rend() };
		if (tryLast(it, _predicate))
		{
			return *it;
		}
		throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(const PredicateConst& _predicate) const
	{
		const_reverse_iterator it{ crend() };
		if (tryCLast(it, _predicate))
		{
			return *it;
		}
		throw std::logic_error{ "no match" };
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(const PredicateConst& _predicate) const
	{
		return clast(_predicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(const Predicate& _predicate)
	{
		iterator it{ end() };
		switch (trySingle(it, _predicate))
		{
			case 0:
				throw std::logic_error{ "no match" };
			case 1:
				return *it;
			default:
				throw std::logic_error{ "multiple matches" };
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(const PredicateConst& _predicate) const
	{
		const_iterator it{ cend() };
		switch (tryCSingle(it, _predicate))
		{
			case 0:
				throw std::logic_error{ "no match" };
			case 1:
				return *it;
			default:
				throw std::logic_error{ "multiple matches" };
		}
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(const PredicateConst& _predicate) const
	{
		return csingle(_predicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::first(TDereferenceResult& _else, const Predicate& _predicate)
	{
		iterator it{ end() };
		return tryFirst(it, _predicate) ? *it : _else;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::cfirst(TDereferenceConstResult& _else, const PredicateConst& _predicate) const
	{
		const_iterator it{ end() };
		return tryCFirst(it, _predicate) ? *it : _else;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::first(TDereferenceConstResult& _else, const PredicateConst& _predicate) const
	{
		return cfirst(_else, _predicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::last(TDereferenceResult& _else, const Predicate& _predicate)
	{
		reverse_iterator it{ end() };
		return tryLast(it, _predicate) ? *it : _else;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::clast(TDereferenceConstResult& _else, const PredicateConst& _predicate) const
	{
		const_reverse_iterator it{ end() };
		return tryCLast(it, _predicate) ? *it : _else;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::last(TDereferenceConstResult& _else, const PredicateConst& _predicate) const
	{
		return clast(_else, _predicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceResult CPPUTILS_COLLECTIONS_ITERABLE::single(TDereferenceResult& _else, const Predicate& _predicate)
	{
		iterator it{ end() };
		return trySingle(it, _predicate) ? *it : _else;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::csingle(TDereferenceConstResult& _else, const PredicateConst& _predicate) const
	{
		const_iterator it{ end() };
		return tryCSingle(it, _predicate) ? *it : _else;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		TDereferenceConstResult CPPUTILS_COLLECTIONS_ITERABLE::single(TDereferenceConstResult& _else, const PredicateConst& _predicate) const
	{
		return csingle(_else, _predicate);
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count(const Predicate& _predicate)
	{
		std::size_t count{ 0 };
		for (const TDereferenceResult& item : *this)
		{
			count += _predicate(item);
		}
		return count;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		std::size_t CPPUTILS_COLLECTIONS_ITERABLE::count(const PredicateConst& _predicate) const
	{
		std::size_t count{ 0 };
		for (const TDereferenceConstResult& item : *this)
		{
			count += _predicate(item);
		}
		return count;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::any(const Predicate& _predicate)
	{
		for (const TDereferenceResult& item : *this)
		{
			if (_predicate(item))
			{
				return true;
			}
		}
		return false;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::any(const PredicateConst& _predicate) const
	{
		for (const TDereferenceConstResult& item : *this)
		{
			if (_predicate(item))
			{
				return true;
			}
		}
		return false;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::all(const Predicate& _predicate)
	{
		for (const TDereferenceResult& item : *this)
		{
			if (!_predicate(item))
			{
				return false;
			}
		}
		return true;
	}

	CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
		bool CPPUTILS_COLLECTIONS_ITERABLE::all(const PredicateConst& _predicate) const
	{
		for (const TDereferenceConstResult& item : *this)
		{
			if (!_predicate(item))
			{
				return false;
			}
		}
		return true;
	}

}

#undef CPPUTILS_COLLECTIONS_ITERABLE_TEMPLATE
#undef CPPUTILS_COLLECTIONS_ITERABLE