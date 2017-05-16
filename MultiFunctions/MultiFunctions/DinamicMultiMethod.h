#pragma once

#include "Loki/MultiMethods.h"

namespace  Loki
{

	////////////////////////////////////////////////////////////////////////////////////
	//Для 3 параметров
	///////////////////////////////////////////////////////////////////////////////////

	template
		<
		class BaseType,
		typename ResultType = void,
		typename CallbackType = ResultType(*)(BaseType&, BaseType&, BaseType&)
		>
		class BasicDispatcher3
	{
		typedef std::string KeyType;
		typedef CallbackType MappedType;
		typedef AssocVector<KeyType, MappedType> MapType;
		MapType callbackMap_;

		void DoAdd(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3, CallbackType fun);
		bool DoRemove(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3);

	public:
		template <class SomeType1, class SomeType2, class  SomeType3>
		void Add(CallbackType fun)
		{
			DoAdd(typeid(SomeType1), typeid(SomeType2), typeid(SomeType3), fun);
		}

		template <class SomeType1, class SomeType2, class  SomeType3>
		bool Remove()
		{
			return DoRemove(typeid(SomeType1), typeid(SomeType2), typeid(SomeType3));
		}

		ResultType Go(BaseType& param1, BaseType& param2, BaseType& param3);

		std::string GetKey(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3)
		{
			return  std::to_string(tp1.Get().hash_code())
				+ std::to_string(tp1.Get().hash_code())
				+ std::to_string(tp1.Get().hash_code());
		}
	};

	// Non-inline to reduce compile time overhead...
	template <class BaseType, typename ResultType, typename CallbackType>
	void BasicDispatcher3<BaseType, ResultType, CallbackType>
		::DoAdd(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3, CallbackType fun)
	{
		callbackMap_[GetKey(tp1, tp2, tp3)] = fun;
	}

	template <class BaseType,
		typename ResultType, typename CallbackType>
		bool BasicDispatcher3<BaseType, ResultType, CallbackType>
		::DoRemove(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3)
	{
		return callbackMap_.erase(GetKey(tp1, tp2, tp3)) == 1;
	}

	template <class BaseType,
		typename ResultType, typename CallbackType>
		ResultType BasicDispatcher3<BaseType, ResultType, CallbackType>
		::Go(BaseType& param1, BaseType& param2, BaseType& param3)
	{
		auto key = GetKey(typeid(param1), typeid(param2), typeid(param3));
		typename MapType::iterator i = callbackMap_.find(key);
		if (i == callbackMap_.end())
		{
			throw std::runtime_error("Function not found");
		}
		return (i->second)(param1, param2, param3);
	}


	///////////////////////////////////////////
	template <class BaseType,
		typename ResultType = void,
		template <class, class> class CastingPolicy = DynamicCaster,
		template <class, class, class>
	class DispatcherBackend3 = BasicDispatcher3>
		class FnDispatcher3
	{
		DispatcherBackend3<BaseType, ResultType,
			std::function<ResultType(BaseType&, BaseType&, BaseType&)>> backEnd_;


		template <class SomeType1, class SomeType2, class SomeType3>
		void AddToBackDisp(std::function<ResultType(BaseType&, BaseType&, BaseType&)> pFun)
		{
			return backEnd_.Add<SomeType1, SomeType2, SomeType3>(pFun);
		}

	public:


		template <class SomeType1, class SomeType2, class SomeType3,
			bool symmetric = false>
			void Add(std::function<ResultType(SomeType1&, SomeType2&, SomeType3&)> callback)
		{
			AddToBackDisp<SomeType1, SomeType2, SomeType3>([=](BaseType& param1, BaseType& param2, BaseType& param3)
			{
				return callback(CastingPolicy<SomeType1, BaseType>::Cast(param1),
					CastingPolicy<SomeType2, BaseType>::Cast(param2),
					CastingPolicy<SomeType3, BaseType>::Cast(param3));
			});
			if (symmetric)
			{
				AddToBackDisp<SomeType1, SomeType2, SomeType3>([=](BaseType& param1, BaseType& param2, BaseType& param3)
				{
					return callback(CastingPolicy<SomeType1, BaseType>::Cast(param1),
						CastingPolicy<SomeType2, BaseType>::Cast(param2),
						CastingPolicy<SomeType3, BaseType>::Cast(param3));
				});
			}
		}


		template <class SomeType1, class SomeType2, class SomeType3>
		void Remove()
		{
			backEnd_.Remove<SomeType1, SomeType2, SomeType3>();
		}

		ResultType Go(BaseType& param1, BaseType& param2, BaseType& param3)
		{
			return backEnd_.Go(param1, param2, param3);
		}
	};
}