#ifndef _CALLER_H_
#define _CALLER_H_

#include <iostream>
#include <vector>
#include <functional>

#include <typeinfo>
#include <unordered_map>

#include "MyMap.h"

#include "TypeCollection.h"

using namespace std;

typedef unsigned uint4;
typedef unsigned long long uint8;

class Caller
{

public:
	static std::unordered_map<int*, uint4>* hashCodesByVirtualAddress;

	template <typename T> static void FillHashCodes();

	template <typename TList > static void FillHashCodesFor_List(TList x)
	{
		FillHashCodes< TList::Head >();
		FillHashCodesFor_List(TList::Tail());
	}

	static void FillHashCodesFor_List(NullType)
	{
	}

	template<class TList>  static void  INit();


	//функции для "раскрытия первого типа"
	template <class TBase, class DeriveType, class DeriviesTypes> static void TryMakeCallFirstType(uint4 code1, uint4 code2, TBase* obj1, TBase* obj2)
	{
		//изменить на полную версию кода, uint8!!
		uint4 deriveTypeCode = typeid(DeriveType).hash_code();
		if (deriveTypeCode == code1)
		{
			DeriveType* typeObj = dynamic_cast<DeriveType*>(obj1);

			MakeCall_ListSecondType<TBase, DeriveType, DeriviesTypes>(DeriviesTypes(), code1, code2, typeObj, obj2);

			//void(*fnc) (T&) = (MyMap<DeriveType>::collisionCases->find(code1))->second;
			//DeriveType tObj = *typeObj;
			//fnc(tObj);
		}
	}

	template <class TBase, class DeriviesTypes1, class DeriviesTypes2> static void MakeCall_ListFirstType(DeriviesTypes1 x, uint4 code1, uint4 code2, TBase* obj1, TBase* obj2)
	{
		TryMakeCallFirstType<TBase, DeriviesTypes1::Head, DeriviesTypes2>(code1, code2, obj1, obj2);
		MakeCall_ListFirstType(DeriviesTypes1::Tail(),code1, code2, obj1, obj2);
	}

	template<class TBase>
	static void MakeCall_ListFirstType(NullType, uint4 code1, uint4 code2, TBase* obj1, TBase* obj2)
	{
	}


	//экспериментальные функции с которыми все ок
	template <class Tobj, class DeriveType> static void TryMakeCallAllRight(uint4 code1, uint4 code2, Tobj* obj1, Tobj* obj2)
	{
		//изменить на полную версию кода, uint8!!
		uint4 codeT = typeid(DeriveType).hash_code();
		if (codeT == code)
		{
			//T* typeObj = dynamic_cast<T*>(obj);
			//void(*fnc) (T&) = (MyMap<T>::collisionCases->find(code))->second;
			//T tObj = *typeObj;
			//fnc(tObj);
		}
	}


	template <class T, class DeriviesTypes > static void MakeCall_ListAllRight(DeriviesTypes x, uint4 code1, uint4 code2, T* obj1, T* obj2)
	{
		TryMakeCallAllRight<T, DeriviesTypes::Head>(code1, code2, obj1, obj2);
		MakeCall_ListAllRight(DeriviesTypes::Tail(), code1, code2, obj1, obj2);
	}

	template<class T>
	static void MakeCall_ListAllRight(NullType, uint4 code1, uint4 code2, T* obj1, T* obj2)
	{
	}





	//функции для "раскрытия второго типа"
	template <class TBase, class TObj1, class DeriveType> static void TryMakeCallSecondType(uint4 code1, uint4 code2, TObj1* obj1, TBase* obj2)
	{
		//изменить на полную версию кода, uint8!!
		uint4 deriveTypeCode = typeid(DeriveType).hash_code();
		if (deriveTypeCode == code2)
		{
			DeriveType* typeObj = dynamic_cast<DeriveType*>(obj2);

			void(*fnc) (TObj1&, DeriveType&) = (MyMap<TObj1,DeriveType>::collisionCases->find(MyMap<TObj1, DeriveType>::key(code1, code2)))->second;
			DeriveType tObj2 = *typeObj;
			fnc(*obj1, tObj2);
		}
	}

	template <class TBase, class TObj1, class DeriviesTypes > static void MakeCall_ListSecondType(DeriviesTypes x, uint4 code1, uint4 code2, TObj1* obj1, TBase* obj2)
	{
		TryMakeCallSecondType<TBase, TObj1, DeriviesTypes::Head>(code1, code2, obj1, obj2);
		MakeCall_ListSecondType(DeriviesTypes::Tail(), code1, code2, obj1, obj2);
	}

	template<class TBase, class Tobj1>
	static void MakeCall_ListSecondType(NullType, uint4 code1, uint4 code2, Tobj1* obj1, TBase* obj2)
	{
	}


	template<class T, class TList> static  void Call(T* obj1, T* obj2);
};


#endif 