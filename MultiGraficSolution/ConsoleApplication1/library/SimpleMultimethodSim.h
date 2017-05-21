# ifndef _SMSym_H_
# define _SMSym_H_

#include "typecollection.h"

#include "Loki\Typelist.h"


template <int v>
struct IntSymType
{
	enum { value = v };
};


template <class SomeLhs, class SomeRhs, class Executor>
struct TraitsSym
{

	static auto DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, IntSymType<true>)
	{
		return exec.Fire(rhs, lhs);
	}

	static auto DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, IntSymType<false>)
	{
		return exec.Fire(lhs, rhs);
	}

};


template
<
	class Executor,
	class BaseLhs,
	class TypesLhs,
	bool symmetric = true,
	class BaseRhs = BaseLhs,
	class TypesRhs = TypesLhs
>
class StaticDispatcherSym
{
	template <class SomeLhs>
	static auto DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec)
	{
		return exec.OnError(lhs, rhs);
	}


	static auto DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor exec)
	{
		return exec.OnError(lhs, rhs);
	}



	template <class OneParam, class SomeLhs>
	static auto DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec, OneParam oneParam)
	{
		if (OneParam* p2 = dynamic_cast<OneParam*>(&rhs))
		{
			IntSymType<(symmetric)> sym;


			using CallTraits = TraitsSym<SomeLhs, OneParam, Executor>;

			return CallTraits::DoDispatch(lhs, *p2, exec, sym);
		}


		return DispatchRhs(lhs, rhs, exec);
	}


	template <class Head, class Tail, class SomeLhs>
	static auto DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec, typeCollectionNew::TypeCollectionMake<Head, Tail>)
	{
		if (Head* p2 = dynamic_cast<Head*>(&rhs))
		{
			IntSymType<(symmetric)> sym;


			using CallTraits = TraitsSym<SomeLhs, Head, Executor>;

			return CallTraits::DoDispatch(lhs, *p2, exec, sym);
		}


		return DispatchRhs(lhs, rhs, exec, Tail());
	}



	template <class OneParam>
	static auto DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor exec, OneParam oneParam)
	{
		if (OneParam* p1 = dynamic_cast<OneParam*>(&lhs))
			return DispatchRhs(*p1, rhs, exec, TypesRhs());

		return DispatchLhs(lhs, rhs, exec);
	}

	template <class Head, class Tail>
	static auto DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor exec, typeCollectionNew::TypeCollectionMake<Head, Tail>)
	{
		if (Head* p1 = dynamic_cast<Head*>(&lhs))
			return DispatchRhs(*p1, rhs, exec, TypesRhs());

		return DispatchLhs(lhs, rhs, exec, Tail());
	}


public:
	static auto Go(BaseLhs& lhs, BaseRhs& rhs, Executor exec)
	{
		return DispatchLhs(lhs, rhs, exec, TypesLhs());
	}
};


#endif 