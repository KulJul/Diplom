# ifndef _SM2_H_
# define _SM2_H_

namespace Private
{
	template <class SomeLhs, class SomeRhs, class Executor, typename ResultType>
	struct InvocationTraits
	{
		static ResultType DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Loki::Int2Type<false>)
		{
			return exec.Fire(lhs, rhs);
		}

		static ResultType DoDispatch(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Loki::Int2Type<true>)
		{
			return exec.Fire(rhs, lhs);
		}
	};
}
#endif 