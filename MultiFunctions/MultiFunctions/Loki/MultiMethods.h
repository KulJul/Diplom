#ifndef MULTIMETHODS_INC_
#define MULTIMETHODS_INC_

#include "Typelist.h"
#include "LokiTypeInfo.h"
#include "Functor.h"
#include "AssocVector.h"
#include "Typelist.h"


namespace Loki
{
	////////////////////////////////////////////////////////////////////////////////
	// class template InvocationTraits (helper)
	// Helps implementing optional symmetry
	////////////////////////////////////////////////////////////////////////////////

	namespace Private
	{
		template <class SomeLhs, class SomeRhs,
			class Executor, typename ResultType>
			struct InvocationTraits
		{
			static ResultType
				DoDispatch(SomeLhs& lhs, SomeRhs& rhs,
					Executor& exec, Int2Type<false>)
			{
				return exec.Fire(lhs, rhs);
			}
			static ResultType
				DoDispatch(SomeLhs& lhs, SomeRhs& rhs,
					Executor& exec, Int2Type<true>)
			{
				return exec.Fire(rhs, lhs);
			}
		};
	}

	////////////////////////////////////////////////////////////////////////////////
	// class template StaticDispatcher
	// Implements an automatic static double dispatcher based on two typelists
	////////////////////////////////////////////////////////////////////////////////

	template
		<
		class Executor,
		class BaseLhs,
		class TypesLhs,
		bool symmetric = true,
		class BaseRhs = BaseLhs,
		class TypesRhs = TypesLhs,
		typename ResultType = void
		>
		class StaticDispatcher
	{
		template <class SomeLhs>
		static ResultType DispatchRhs(SomeLhs& lhs, BaseRhs& rhs,
			Executor exec, NullType)
		{
			return exec.OnError(lhs, rhs);
		}

		template <class Head, class Tail, class SomeLhs>
		static ResultType DispatchRhs(SomeLhs& lhs, BaseRhs& rhs,
			Executor exec, Typelist<Head, Tail>)
		{
			if (Head* p2 = dynamic_cast<Head*>(&rhs))
			{
				Int2Type<(symmetric &&
					int(TL::IndexOf<TypesRhs, Head>::value) <
					int(TL::IndexOf<TypesLhs, SomeLhs>::value))> i2t;

				typedef Private::InvocationTraits<
					SomeLhs, Head, Executor, ResultType> CallTraits;

				return CallTraits::DoDispatch(lhs, *p2, exec, i2t);
			}
			return DispatchRhs(lhs, rhs, exec, Tail());
		}

		static ResultType DispatchLhs(BaseLhs& lhs, BaseRhs& rhs,
			Executor exec, NullType)
		{
			return exec.OnError(lhs, rhs);
		}

		template <class Head, class Tail>
		static ResultType DispatchLhs(BaseLhs& lhs, BaseRhs& rhs, Executor exec, Typelist<Head, Tail>)
		{
			if (Head* p1 = dynamic_cast<Head*>(&lhs))
			{
				return DispatchRhs(*p1, rhs, exec, TypesRhs());
			}
			return DispatchLhs(lhs, rhs, exec, Tail());
		}

	public:
		static ResultType Go(BaseLhs& lhs, BaseRhs& rhs,
			Executor exec)
		{
			return DispatchLhs(lhs, rhs, exec, TypesLhs());
		}
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template BasicDispatcher
	// Implements a logarithmic double dispatcher for functors (or functions)
	// Doesn't offer automated casts or symmetry
	////////////////////////////////////////////////////////////////////////////////

	template
		<
		class BaseLhs,
		class BaseRhs = BaseLhs,
		typename ResultType = void,
		typename CallbackType = ResultType(*)(BaseLhs&, BaseRhs&)
		>
		class BasicDispatcher
	{
		typedef std::pair<TypeInfo, TypeInfo> KeyType;
		typedef CallbackType MappedType;
		typedef AssocVector<KeyType, MappedType> MapType;
		MapType callbackMap_;

		void DoAdd(TypeInfo lhs, TypeInfo rhs, CallbackType fun);
		bool DoRemove(TypeInfo lhs, TypeInfo rhs);

	public:
		template <class SomeLhs, class SomeRhs>
		void Add(CallbackType fun)
		{
			DoAdd(typeid(SomeLhs), typeid(SomeRhs), fun);
		}

		template <class SomeLhs, class SomeRhs>
		bool Remove()
		{
			return DoRemove(typeid(SomeLhs), typeid(SomeRhs));
		}

		ResultType Go(BaseLhs& lhs, BaseRhs& rhs);
	};

	// Non-inline to reduce compile time overhead...
	template <class BaseLhs, class BaseRhs,
		typename ResultType, typename CallbackType>
		void BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
		::DoAdd(TypeInfo lhs, TypeInfo rhs, CallbackType fun)
	{
		callbackMap_[KeyType(lhs, rhs)] = fun;
	}

	template <class BaseLhs, class BaseRhs,
		typename ResultType, typename CallbackType>
		bool BasicDispatcher<BaseLhs, BaseRhs, ResultType, CallbackType>
		::DoRemove(TypeInfo lhs, TypeInfo rhs)
	{
		return callbackMap_.erase(KeyType(lhs, rhs)) == 1;
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

	////////////////////////////////////////////////////////////////////////////////
	// class template StaticCaster
	// Implementation of the CastingPolicy used by FunctorDispatcher
	////////////////////////////////////////////////////////////////////////////////

	template <class To, class From>
	struct StaticCaster
	{
		static To& Cast(From& obj)
		{
			return static_cast<To&>(obj);
		}
	};

	////////////////////////////////////////////////////////////////////////////////
	// class template DynamicCaster
	// Implementation of the CastingPolicy used by FunctorDispatcher
	////////////////////////////////////////////////////////////////////////////////

	template <class To, class From>
	struct DynamicCaster
	{
		static To& Cast(From& obj)
		{
			return dynamic_cast<To&>(obj);
		}
	};


	////////////////////////////////////////////////////////////////////////////////
	// class template FnDispatcher
	// Implements an automatic logarithmic double dispatcher for functions
	// Features automated conversions
	////////////////////////////////////////////////////////////////////////////////

	template <class BaseLhs, class BaseRhs = BaseLhs,
		typename ResultType = void,
		template <class, class> class CastingPolicy = DynamicCaster,
		template <class, class, class, class>
	class DispatcherBackend = BasicDispatcher>
		class FnDispatcher
	{
		DispatcherBackend<BaseLhs, BaseRhs, ResultType,
			std::function<ResultType(BaseLhs&, BaseRhs&)>> backEnd_;


		template <class SomeLhs, class SomeRhs>
		void AddToBackDisp(std::function<ResultType(BaseLhs&, BaseRhs&)> pFun)
		{
			return backEnd_.Add<SomeLhs, SomeRhs>(pFun);
		}

	public:


		template <class SomeLhs, class SomeRhs,
			bool symmetric = false>
			void Add(std::function<ResultType(SomeLhs&, SomeRhs&)> callback)
		{
			AddToBackDisp<SomeLhs, SomeRhs>([=](BaseLhs& lhs, BaseRhs& rhs)
			{
				return callback(CastingPolicy<SomeLhs, BaseLhs>::Cast(lhs), CastingPolicy<SomeRhs, BaseRhs>::Cast(rhs));
			});
			if (symmetric)
			{
				AddToBackDisp<SomeRhs, SomeLhs>([=](BaseRhs& rhs, BaseLhs& lhs)
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

		ResultType Go(BaseLhs& lhs, BaseRhs& rhs)
		{
			return backEnd_.Go(lhs, rhs);
		}
	};

	////////////////////////////////////////////////////////////////////////////////////
	//��� 3 ����������
	///////////////////////////////////////////////////////////////////////////////////
	template
		<
		class BaseType,
		typename ResultType = void,
		typename CallbackType = ResultType(*)(BaseType&, BaseType&, BaseType&)
		>
		class BasicDispatcher3
	{
		typedef TYPELIST_3(TypeInfo, TypeInfo, TypeInfo) KeyType;
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
	};

	// Non-inline to reduce compile time overhead...
	template <class BaseType, typename ResultType, typename CallbackType>
		void BasicDispatcher3<BaseType, ResultType, CallbackType>
		::DoAdd(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3, CallbackType fun)
		{
			callbackMap_[KeyType(tp1, tp2, tp3)] = fun;
		}

	template <class BaseType,
		typename ResultType, typename CallbackType>
		bool BasicDispatcher3<BaseType, ResultType, CallbackType>
		::DoRemove(TypeInfo tp1, TypeInfo tp2, TypeInfo tp3)
		{
			return callbackMap_.erase(KeyType(tp1, tp2, tp3)) == 1;
		}

	template <class BaseType,
		typename ResultType, typename CallbackType>
		ResultType BasicDispatcher3<BaseType, ResultType, CallbackType>
		::Go(BaseType& param1, BaseType& param2, BaseType& param3)
		{
			typename MapType::key_type k(typeid(param1), typeid(param2), typeid(param3));
			typename MapType::iterator i = callbackMap_.find(k);
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
		class FnDispatcher
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


	////////////////////////////////////////////////////////////////////////////////
	// class template FunctorDispatcherAdaptor
	// permits use of FunctorDispatcher under gcc.2.95.2/3
	///////////////////////////////////////////////////////////////////////////////

	namespace Private
	{
		template <class BaseLhs, class BaseRhs,
			class SomeLhs, class SomeRhs,
			typename ResultType,
			class CastLhs, class CastRhs,
			class Fun, bool SwapArgs>
			class FunctorDispatcherHelper
		{
			Fun fun_;
			ResultType Fire(BaseLhs& lhs, BaseRhs& rhs, Int2Type<false>)
			{
				return fun_(CastLhs::Cast(lhs), CastRhs::Cast(rhs));
			}
			ResultType Fire(BaseLhs& rhs, BaseRhs& lhs, Int2Type<true>)
			{
				return fun_(CastLhs::Cast(lhs), CastRhs::Cast(rhs));
			}
		public:
			FunctorDispatcherHelper(const Fun& fun) : fun_(fun) {}

			ResultType operator()(BaseLhs& lhs, BaseRhs& rhs)
			{
				return Fire(lhs, rhs, Int2Type<SwapArgs>());
			}
		};
	}

	////////////////////////////////////////////////////////////////////////////////
	// class template FunctorDispatcher
	// Implements a logarithmic double dispatcher for functors
	// Features automated casting
	////////////////////////////////////////////////////////////////////////////////

	template <class BaseLhs, class BaseRhs = BaseLhs,
		typename ResultType = void,
		template <class, class> class CastingPolicy = DynamicCaster,
		template <class, class, class, class>
	class DispatcherBackend = BasicDispatcher>
		class FunctorDispatcher
	{
		typedef TYPELIST_2(BaseLhs&, BaseRhs&) ArgsList;
		typedef Functor<ResultType, ArgsList, DEFAULT_THREADING> FunctorType;

		DispatcherBackend<BaseLhs, BaseRhs, ResultType, FunctorType> backEnd_;

	public:
		template <class SomeLhs, class SomeRhs, class Fun>
		void Add(const Fun& fun)
		{
			typedef Private::FunctorDispatcherHelper<
				BaseLhs, BaseRhs,
				SomeLhs, SomeRhs,
				ResultType,
				CastingPolicy<SomeLhs, BaseLhs>,
				CastingPolicy<SomeRhs, BaseRhs>,
				Fun, false> Adapter;

			backEnd_.Add<SomeLhs, SomeRhs>(FunctorType(Adapter(fun)));
		}
		template <class SomeLhs, class SomeRhs, bool symmetric, class Fun>
		void Add(const Fun& fun)
		{
			Add<SomeLhs, SomeRhs>(fun);

			if (symmetric)
			{
				// Note: symmetry only makes sense where BaseLhs==BaseRhs
				using AdapterR = Private::FunctorDispatcherHelper<
					BaseLhs, BaseLhs,
					SomeLhs, SomeRhs,
					ResultType,
					CastingPolicy<SomeLhs, BaseLhs>,
					CastingPolicy<SomeRhs, BaseLhs>,
					Fun, true>;

				backEnd_.Add<SomeRhs, SomeLhs>(FunctorType(AdapterR(fun)));
			}
		}

		template <class SomeLhs, class SomeRhs>
		void Remove()
		{
			backEnd_.Remove<SomeLhs, SomeRhs>();
		}

		ResultType Go(BaseLhs& lhs, BaseRhs& rhs)
		{
			return backEnd_.Go(lhs, rhs);
		}
	};
} // namespace Loki


#endif
