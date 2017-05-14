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
#include "MyMap.cpp"

#include "Caller.h"






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

template<class T, class TList>  void Caller::Call(T* obj1, T* obj2)
{
	int* vptr1 = *(int**)obj1;
	int* vptr2 = *(int**)obj2;

	uint4 code1 = Caller::hashCodesByVirtualAddress->find(vptr1)->second;
	uint4 code2 = Caller::hashCodesByVirtualAddress->find(vptr2)->second;

	//גûחûגאול
	Caller::MakeCall_ListFirstType<T,TList, TList>(TList(), TList(), code1, code2, obj1, obj2);
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

	static void collide_as_sh(asteroid&, space_ship&)
	{
		auto l = "Asteroid collides with space ship";
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


/*
int main() {


	asteroid asteroidObj;
	space_ship shipObj;

	game_object* asteroidGameObj  = &asteroidObj;
	game_object* shipGameObj = &shipObj;

	game_object& asteroidGameRef = asteroidObj;
	game_object& shipGameRef = shipObj;

	size_t asteroidHCD = typeid(asteroid).hash_code();
	size_t shipHCD = typeid(space_ship).hash_code();

	size_t asteroidPointerHCD = typeid(asteroidGameObj).hash_code();
	size_t shipPointerHCD = typeid(shipGameObj).hash_code();

	size_t asteroidRefHCD = typeid(asteroidGameRef).hash_code();
	size_t shipRefHCH = typeid(shipGameRef).hash_code();

	
*/
	MyMap<asteroid, space_ship>::addHandler(MyClass::collide_as_sh);

	Caller::INit<TypeCollectionMake<asteroid, space_ship>>();

	Caller::Call<game_object, TypeCollectionMake<asteroid, space_ship>::Collection>(asteroidGameObj, shipGameObj);
	
}
