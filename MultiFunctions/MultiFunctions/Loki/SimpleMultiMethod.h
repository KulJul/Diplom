# ifndef _SM_H_
# define _SM_H_

#include "ExecuteSimpleMethod.h"
#include "typecollection.h"

template
<
	class Executor,
	class FirstType,
	class FirstTypesCollection,
	bool symmetric = true,
	class SecondType = FirstType,
	class SecondTypesCollection = FirstTypesCollection,
	typename ResultType = void
>
class SimpleMultiMethod
{
	template <typename...> struct typeSym { };
	using IndexedTypes = typeSym<bool>;

	template <class Somefirst_parm>
	static auto Dispatchsecond_parm(Somefirst_parm& first_parm, SecondType& second_parm, Executor exec, NullType)
	{
		return exec.OnError(first_parm, second_parm);
	}

	static auto Dispatchfirst_parm(FirstType& first_parm, SecondType& second_parm, Executor exec, NullType)
	{
		return exec.OnError(first_parm, second_parm);
	}

	template <class Head, class Tail, class Some_first_parm>
	static auto  Run_second_parm(Some_first_parm& first_parm, SecondType& second_parm, Executor exec, TypeCollectionMake<Head, Tail>)
	{

		if (Head* param_sec = dynamic_cast<Head*>(&second_parm))
		{
			IndexedTypes symmetrFlag <(symmetric &&
				int(IndexOf<SecondTypesCollection, Head>::value) <
				int(IndexOf<FirstTypesCollection, Some_first_parm>::value))> ;

			typedef Private::InvocationTraits<Some_first_parm, Head, Executor> CallTraits;

			return CallTraits::DoDispatch(first_parm, *param_sec, exec, symmetrFlag);
		}

		return Run_second_parm(first_parm, second_parm, exec, Tail());
	}


	template <class Head, class Tail>
	static auto Run_first_parm(FirstType& first_parm, SecondType& second_parm, Executor exec, TypeCollectionMake<Head, Tail>)
	{
		if (Head* param_first = dynamic_cast<Head*>(&first_parm))
			return Run_second_parm(*param_first, second_parm, exec, SecondTypesCollection());

		return Run_first_parm(first_parm, second_parm, exec, Tail());
	}

public:
	static auto RunMultiMethodSimple(FirstType& first_parm, SecondType& second_parm, Executor exec)
	{
		return Run_first_parm(first_parm, second_parm, exec, FirstTypesCollection());
	}
};

#endif 