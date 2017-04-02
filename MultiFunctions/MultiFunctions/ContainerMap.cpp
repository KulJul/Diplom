#include "ContainerMap.h"


template <int First, int Last>
struct static_for
{
	template <typename Fn>
	void operator()(Fn const& fn) const
	{
		if (First < Last)
		{
			fn(First);
			static_for<First + 1, Last>()(fn);
		}
	}
};

template <int N>
struct static_for<N, N>
{
	template <typename Fn>
	void operator()(Fn const& fn) const
	{ }
};

template<class T1, class  T2>
void MyMapContainer<T1, T2>::compare(T1* obj, T2 obj2)
{
	static_for<0, 5>()([&](int i)
	{
		auto k = 0;
		//if (dynamic_cast<GetElement<T2, i>>(obj) != NULL)
		{/*
			auto handler = MyMap<GetElement<T2, i>::Collection>::
				collisionCases->find(typeid(GetElement<T2, i>::Collection).hash_code());

			if (handler != MyMap<GetElement<T2, i>::Collection>::collisionCases->end()) {
				(*handler->second)(obj);
			}*/
		}
	});
}

/*
template <class T1, class  T2>
void MyMapContainer<T1, T2>::compare(T1* obj, T2 obj2)
{
	//for (unsigned int i = 0; i < Length<T2>::value; i++)
	{

		if (dynamic_cast<GetElement<T2, 1>::Collection>(obj) != NULL)
		{
			auto handler = MyMap<GetElement<T2, 1>::Collection>::
				           collisionCases->find(typeid(GetElement<T2, 1>::Collection).hash_code());

			if (handler != MyMap<GetElement<T2, 1>::Collection>::collisionCases->end()) {
				(*handler->second)(obj);
			}
		}

	}
	/*
	auto as2 = static_cast<T2::Head&>(obj);

	auto as22 = static_cast<T2::Head&>(obj);

	auto handler = MyMap<T2::Head>::collisionCases->find(typeid(T2::Head).hash_code());
	if (handler != MyMap<T2::Head>::collisionCases->end()) {
		(*handler->second)(as2);
		(*handler->second)(as22);
	}*/

	//auto temp = static_cast<T2::Head &>(obj);
	//auto xCollisionCases = MyMap<T2::Head&>::collisionCases;
	//auto xCollisionCases = MyMap<T2::Tail()  &>::collisionCases;

	//auto handler = xCollisionCases->find(typeid(obj).hash_code());
	//if (handler != xCollisionCases->end()) {
		//(*handler->second)(obj); // pointer-to-method call
	//}
	//auto z = 0;
//}