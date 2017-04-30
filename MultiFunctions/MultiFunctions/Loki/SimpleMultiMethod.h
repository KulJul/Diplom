# ifndef _SM_H_
# define _SM_H_

#include "ExecuteSimpleMethod.h"
#include "typecollection.h"
#include "Typelist.h"

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
	template <class Some_first_parm>
	static ResultType Dispatchsecond_parm(Some_first_parm& first_parm, SecondType& second_parm, Executor exec, Loki::NullType)
	{
		return exec.OnError(first_parm, second_parm);
	}

	static ResultType Dispatchfirst_parm(FirstType& first_parm, SecondType& second_parm, Executor exec, Loki::NullType)
	{
		return exec.OnError(first_parm, second_parm);
	}

	template <class Head, class Tail, class Some_first_parm>
	static ResultType  Run_second_parm(Some_first_parm& first_parm, SecondType& second_parm, Executor exec, Loki::Typelist<Head, Tail>)
	{

		if (Head* param_sec = dynamic_cast<Head*>(&second_parm))
		{

			Loki::Int2Type<(symmetric &&
				int(Loki::TL::IndexOf<SecondTypesCollection, Head>::value) <
				int(Loki::TL::IndexOf<FirstTypesCollection, Some_first_parm>::value))> i2t;

			typedef Private::InvocationTraits<Some_first_parm, Head, Executor, ResultType> CallTraits;

			return CallTraits::DoDispatch(first_parm, *param_sec, exec, i2t);
		}

		return Run_second_parm(first_parm, second_parm, exec, Tail());
	}


	template <class Head, class Tail>
	static ResultType Run_first_parm(FirstType& first_parm, SecondType& second_parm, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* param_first = dynamic_cast<Head*>(&first_parm))
			return Run_second_parm(*param_first, second_parm, exec, SecondTypesCollection());

		return Run_first_parm(first_parm, second_parm, exec, Tail());
	}

public:
	static ResultType RunMultiMethodSimple(FirstType& first_parm, SecondType& second_parm, Executor exec)
	{
		return Run_first_parm(first_parm, second_parm, exec, FirstTypesCollection());
	}
};

#endif 