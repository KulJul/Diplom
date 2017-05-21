# ifndef _SM2_H_
# define _SM2_H_

#include "typecollection.h"

#include "Loki\Typelist.h"

template <class SomeFirst, class SomeSecond, class SomeThird, class Executor>
struct TraitSeveral
{

	static auto DoDispatch(SomeFirst& first, SomeSecond& second, SomeThird& third, Executor& exec)
	{
		return exec.Fire(first, first, first);
	}
};


template <class SomeFirst, class SomeSecond, class Executor>
struct TraitSeveral2
{

	static auto DoDispatch2(SomeFirst& first, SomeSecond& second, Executor& exec)
	{
		return exec.Fire(first, second);
	}
};


template
<
	class Executor,
	class BaseFirst,
	class BaseSecond,
	class BaseThird,
	class TypesBase
>
class StaticDispatcher3
{
	template <class SomeFirst, class SomeSecond>
	static auto DispatchThird(SomeFirst& first, SomeSecond& second, BaseThird& third, Executor exec, Loki::NullType)
	{
		return exec.OnError(third, third, third);
	}

	template <class SomeFirst>
	static auto DispatchSecond(SomeFirst& first, BaseSecond& second, BaseThird& third, Executor exec, Loki::NullType)
	{
		return exec.OnError(third, third, third);
	}


	static auto DispatchOne(BaseFirst& first, BaseSecond& second, BaseThird& third, Executor exec, Loki::NullType)
	{
		return exec.OnError(first, second, third);
	}




	template <class Head, class Tail, class SomeFirst, class SomeSecond>
	static auto DispatchThird(SomeFirst& first, SomeSecond& second, BaseThird& third, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* p3 = dynamic_cast<Head*>(&third))
		{
			using CallTraits = TraitSeveral<SomeFirst, SomeSecond, Head, Executor>;

			return CallTraits::DoDispatch(first, second, *p3, exec);
		}


		return DispatchThird(first, second, third, exec, Tail());
	}




	template <class Head, class Tail, class SomeFirst>
	static auto DispatchSecond(SomeFirst& first, BaseSecond& second, BaseThird& third, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* p2 = dynamic_cast<Head*>(&second))
			return DispatchThird(first, *p2, third, exec, TypesBase());

		return DispatchSecond(first, second, third, exec, Tail());
	}




	template <class Head, class Tail>
	static auto DispatchOne(BaseFirst& first, BaseSecond& second, BaseThird& third, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* p1 = dynamic_cast<Head*>(&first))
			return DispatchSecond(*p1, second, third, exec, TypesBase());

		return DispatchOne(first, second, third, exec, Tail());
	}


public:
	static auto Go(BaseFirst& first, BaseSecond& second, BaseThird& third, Executor exec)
	{
		return DispatchOne(first, second, third, exec, TypesBase());
	}
};

template
<
	class Executor,
	class BaseFirst,
	class BaseSecond,
	class TypesBase
>
class StaticDispatcherTwo
{
	template <class SomeFirst>
	static auto DispatchSecond(SomeFirst& first, BaseSecond& second, Executor exec, Loki::NullType)
	{
		return exec.OnError(first, second);
	}


	static auto DispatchOne(BaseFirst& first, BaseSecond& second, Executor exec, Loki::NullType)
	{
		return exec.OnError(first, second);
	}




	template <class Head, class Tail, class SomeFirst>
	static auto DispatchSecond(SomeFirst& first, BaseSecond& second, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* p2 = dynamic_cast<Head*>(&second))
		{
			using CallTraits = TraitSeveral2<SomeFirst, Head, Executor>;

			return CallTraits::DoDispatch2(first, *p2, exec);
		}


		return DispatchSecond(first, second,  exec, Tail());
	}





	template <class Head, class Tail>
	static auto DispatchOne(BaseFirst& first, BaseSecond& second, Executor exec, Loki::Typelist<Head, Tail>)
	{
		if (Head* p1 = dynamic_cast<Head*>(&first))
			return DispatchSecond(*p1, second, exec, TypesBase());

		return DispatchOne(first, second, exec, Tail());
	}


public:
	static auto Go(BaseFirst& first, BaseSecond& second, Executor exec)
	{
		return DispatchOne(first, second, exec, TypesBase());
	}
};

#endif 