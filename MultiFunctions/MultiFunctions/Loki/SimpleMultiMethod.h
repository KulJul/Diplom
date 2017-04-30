# ifndef _SM_H_
# define _SM_H_

#include "typecollection.h"
#include "Typelist.h"


template <class SomeLhs, class SomeRhs, class Executor>
struct Traits
{
	static auto DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Loki::Int2Type<false>)
	{
		return exec.Fire(lhs, rhs);
	}

	static auto DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Loki::Int2Type<true>)
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
	static auto DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec, Loki::NullType)
	{
		return exec.OnError(lhs, rhs);
	}


	static auto DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor exec, Loki::NullType)
	{
		return exec.OnError(lhs, rhs);
	}

	template <class Head, class Tail, class SomeLhs>
	static auto DispatchRhs(SomeLhs& lhs, BaseRhs& rhs, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* p2 = dynamic_cast<Head*>(&rhs))
		{
			Loki::Int2Type<(symmetric && int(Loki::TL::IndexOf<TypesRhs, Head>::value) <
				                         int(Loki::TL::IndexOf<TypesLhs, SomeLhs>::value))> i2t;

			using CallTraits = Traits<SomeLhs, Head, Executor>;

			return CallTraits::DoDispatch(lhs, *p2, exec, i2t);
		}


		return DispatchRhs(lhs, rhs, exec, Tail());
	}

	

	template <class Head, class Tail>
	static auto DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor exec, Loki::Typelist<Head, Tail>)
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