# ifndef _SM_H_
# define _SM_H_

#include "typecollection.h"


template <class SomeLhs, class SomeRhs, class Executor>
struct Traits
{

	static auto DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec)
	{
		return exec.Fire(rhs, lhs);
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
class StaticDispatcher2
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
			using CallTraits = Traits<SomeLhs, OneParam, Executor>;

			return CallTraits::DoDispatch(lhs, *p2, exec);
		}


		return DispatchRhs(lhs, rhs, exec);
	}


	template <class Head, class Tail, class SomeLhs>
	static auto DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec, typeCollectionNew::TypeCollectionMake<Head, Tail>)
	{
		if (Head* p2 = dynamic_cast<Head*>(&rhs))
		{
			using CallTraits = Traits<SomeLhs, Head, Executor>;

			return CallTraits::DoDispatch(lhs, *p2, exec);
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