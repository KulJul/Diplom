
#include <iostream>
#include <vector>
#include <functional>

#include "game_hierarchy.hpp"


//#include "ContainerMap.h"
//#include "ContainerMap.cpp"

#include <typeinfo>
#include <unordered_map>
//#include <boost/any.hpp>
//#include <stdafh.h>

#include "MyMap.h"


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

template<class T, class TList>  void Caller::Call(T* obj)
{
	int* vptr = *(int**)obj;
	uint4 code = Caller::hashCodesByVirtualAddress->find(vptr)->second->hash;
	int index = Caller::hashCodesByVirtualAddress->find(vptr)->second->index;
	//извлекаем тип
	//using  GetElement<TList, index>::value;
	//динамически приводим

	//извлекаем функцию

	//вызываем

}



