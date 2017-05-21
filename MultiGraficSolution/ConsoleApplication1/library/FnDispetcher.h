#include <utility>
#include "Loki/AssocVector.h"
#include "Loki/LokiTypeInfo.h"

template
<
	class BaseLhs,
	class BaseRhs = BaseLhs,
	typename ResultType = void,
	typename CallbackType = ResultType(*)(BaseLhs&, BaseRhs&)
>
class BasicDispatcher
{
	typedef std::pair<Loki::TypeInfo, Loki::TypeInfo> KeyType;
	using MappedType = CallbackType;
	using MapType = Loki::AssocVector<KeyType, MappedType>;
	MapType callbackMap_;

	void DoAdd(Loki::TypeInfo lhs, Loki::TypeInfo rhs, CallbackType fun);
	bool DoRemove(Loki::TypeInfo lhs, Loki::TypeInfo rhs);

public:
	template <class SomeLhs, class SomeRhs>
	void Add(CallbackType fun);

	template <class SomeLhs, class SomeRhs>
	bool Remove();

	ResultType Go(BaseLhs& lhs, BaseRhs& rhs);
};


template <class BaseLhs, class BaseRhs,
	typename ResultType, typename CallbackType>
	void BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
	::DoAdd(Loki::TypeInfo lhs, Loki::TypeInfo rhs, CallbackType fun)
{
	callbackMap_[KeyType(lhs, rhs)] = fun;
}

template <class BaseLhs, class BaseRhs,
	typename ResultType, typename CallbackType>
	bool BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
	::DoRemove(Loki::TypeInfo lhs, Loki::TypeInfo rhs)
{
	return callbackMap_.erase(KeyType(lhs, rhs)) == 1;
}

template <class BaseLhs, class BaseRhs, typename ResultType, typename CallbackType>
template <class SomeLhs, class SomeRhs>
void BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>::Add(CallbackType fun)
{
	DoAdd(typeid(SomeLhs), typeid(SomeRhs), fun);
}

template <class BaseLhs, class BaseRhs, typename ResultType, typename CallbackType>
template <class SomeLhs, class SomeRhs>
bool BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>::Remove()
{
	return DoRemove(typeid(SomeLhs), typeid(SomeRhs));
}

template <class BaseLhs, class BaseRhs,
	typename ResultType, typename CallbackType>
	ResultType BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
	::Go(BaseLhs& lhs, BaseRhs& rhs)
{
	typename MapType::key_type k(typeid(lhs), typeid(rhs));
	typename MapType::iterator i = callbackMap_.find(k);
	if (i == callbackMap_.end())
	{
		throw std::runtime_error("Function not found");
	}
	return (i->second)(lhs, rhs);
}

template <class To, class From>
struct DynamicCaster
{
	static To& Cast(From& obj)
	{
		return dynamic_cast<To&>(obj);
	}
};

template <class BaseLhs, class BaseRhs = BaseLhs,
	typename ResultType = void,
	template <class, class> class CastingPolicy = DynamicCaster,
	template <class, class, class, class>
class DispatcherBackend = BasicDispatcher>
	class FnDispatcher
{
	DispatcherBackend<BaseLhs, BaseRhs, ResultType, ResultType(*)(BaseLhs&, BaseRhs&)> backEnd_;

	template <class SomeLhs, class SomeRhs>
	void Add(ResultType(*pFun)(BaseLhs&, BaseRhs&))
	{
		return backEnd_.Add<SomeLhs, SomeRhs>(pFun);
	}

public:

	template <class SomeLhs, class SomeRhs,
		ResultType(*callback)(SomeLhs&, SomeRhs&),
		bool symmetric = false>
		void Add()
	{
		Add<SomeLhs, SomeRhs>([](BaseLhs& lhs, BaseRhs& rhs)
		{
			return callback(CastingPolicy<SomeLhs, BaseLhs>::Cast(lhs), CastingPolicy<SomeRhs, BaseRhs>::Cast(rhs));
		});
		if (symmetric)
		{
			Add<SomeRhs, SomeLhs>([](BaseRhs& rhs, BaseLhs& lhs)
			{
				return callback(CastingPolicy<SomeLhs, BaseLhs>::Cast(lhs), CastingPolicy<SomeRhs, BaseRhs>::Cast(rhs));
			});
		}
	}

	template <class SomeLhs, class SomeRhs>
	void Remove()
	{
		backEnd_.Remove<SomeLhs, SomeRhs>();
	}

	auto Go(BaseLhs& lhs, BaseRhs& rhs)
	{
		return backEnd_.Go(lhs, rhs);
	}
};