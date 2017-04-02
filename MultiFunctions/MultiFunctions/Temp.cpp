#include <iostream>
#include <vector>
#include <functional>

#include "game_hierarchy.hpp"


#include "TypeCollection.h"


//#include "ContainerMap.h"
//#include "ContainerMap.cpp"

#include <typeinfo>
#include <unordered_map>
//#include <boost/any.hpp>
//#include <stdafh.h>
#include "MyMap.h"


#include "Caller.h"

#include "MyMap.cpp"




using namespace std;

std::unordered_map<int*, uint4>* Caller::hashCodesByVirtualAddress = new std::unordered_map<int*, uint4>();

template <typename T>  void Caller::FillHashCodes()
{
	T* typeObj = new T();
	int* vptr = *(int**)typeObj;
	(*Caller::hashCodesByVirtualAddress).insert({ vptr, typeid(T).hash_code() });
}

//template <typename TList > static void Caller::FillHashCodesFor_List(void)
//{
//	Caller::FillHashCodes< TList::Head >();
//	Caller::FillHashCodesFor_List(TList::Tail());
//}
//
//void Caller::FillHashCodesFor_List(NullType)
//{
//}

template<class TList> void  Caller::INit()
{
	Caller::FillHashCodesFor_List<TList>(TList());
}

template<class T, class TList>  void Caller::Call(T* obj)
{
	int* vptr = *(int**)obj;
	uint4 code = Caller::hashCodesByVirtualAddress->find(vptr)->second;

	//גûחûגאול
	Caller::MakeCall_List<T,TList>(TList(), code, obj);

}


class MyClass
{
public:

	void asteroid_collision(MyClass& other) {  }


	const char* collide_go_go(game_object*, game_object*)
	{
		return "Unsupported colliding!";
	}

	static void collide_sh_sh(space_ship&)
	{
 		auto sh =  "Space ship collides with space ship";
	}

	const char* collide_sh_as(space_ship*, asteroid*)
	{
		return "Space ship collides with asteroid";
	}

	const char* collide_as_sh(asteroid*, space_ship*)
	{
		return "Asteroid collides with space ship";
	}

	static void collide_as_as(asteroid& other)
	{
		auto l = "Asteroid collides with asteroid";
	}

};

/*
template < typename Objs>
void collide_tester(Objs& objs, const std::vector<boost::any> arr, const std::vector<boost::any> arrEl)
{
	
	MyMap<Objs>::collideWith(objs, arr, arrEl);
	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < 2; ++j)
		{
			//comp->collideWith(objs[i], objs[j]);
		}
	}
}*/


vector<game_object*>& get_obj_pointers()
{
	static space_ship ship;
	static asteroid ast;
	static space_station station;

	static vector<game_object*> objs; 


	if (objs.empty())
	{
		objs.push_back(&ship);
		objs.push_back(&ast);
		objs.push_back(&station);
	}

	return objs;
}



template < class  T1, class T2 >
void compare2(T1* obj) 
{
	size_t codeTypeObjT1 = typeid(obj).hash_code();
	size_t codeType2 = typeid(T2).hash_code();
	if (typeid(obj) == typeid(T2*))
	{
		T2 typeObj = dynamic_cast<T2>(obj);
		void (*fnc) (T2&)  = (MyMap<T2>::collisionCases->find(typeid(T2).hash_code()))->second;
		fnc(typeObj);
	}
}


template < class  T1, class T2 >
void static_for(T1* obj, T2 x)
{
	compare2<T1, T2::Head >(obj);
	static_for<T1>(obj, T2::Tail());
}


template <class T1>
void static_for(T1* obj, NullType)
{
}



int main() {

	space_ship astSp;
	asteroid ast2;
	game_object* o = &ast2;


	asteroid* typeObj = dynamic_cast<asteroid*>(o);

		
	MyMap<asteroid>::addHandler(typeid(asteroid).hash_code(),  MyClass::collide_as_as);
	MyMap<space_ship>::addHandler(typeid(space_ship).hash_code(),  MyClass::collide_sh_sh);
	
	using typesCollection = typename TypeCollectionMake<asteroid*, space_ship*>::Collection;

	Caller::INit<TypeCollectionMake<asteroid, space_ship>::Collection>();

	Caller::Call<game_object, TypeCollectionMake<asteroid, space_ship>::Collection>(o);
	

	static_for<game_object, typesCollection>(o, typesCollection());
	auto l = 2;


	/*
	std::cout << "Length<> : " << typeid(IntTypes).name() << '\n';
	std::cout << "Length<> : " << typeid(IntTypes::Tail::Head).name() << '\n';



	std::cout << "IndexOf2 : " << typeid(GetElement<IntTypes, 2>::Collection).name() << '\n';


	std::cout << "Length<> : " << Length<IntTypes>::value << '\n';*/
}
