# ifndef _SM2_H_
# define _SM2_H_

namespace Private
{
	template <int I>
	struct Int2Type
	{
		enum { value = I };
	};

	template <class SomeLhs, class SomeRhs, class Executor, typename ResultType>
	struct InvocationTraits
	{
		static auto DoExec(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Int2Type<false>)
		{
			return exec.Fire(lhs, rhs);
		}

		static auto DoExec(SomeLhs& lhs, SomeRhs& rhs, Executor& exec, Int2Type<true>)
		{
			return exec.Fire(rhs, lhs);
		}
	};
}
#endif 