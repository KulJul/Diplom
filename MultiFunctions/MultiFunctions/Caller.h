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


	template <class Tobj, class T> static void TryMakeCall(uint4 code, Tobj* obj)
	{
		//изменить на полную версию кода, uint8!!
		uint4 codeT = typeid(T).hash_code();
		if (codeT == code)
		{
			T* typeObj = dynamic_cast<T*>(obj);
			void(*fnc) (T&) = (MyMap<T>::collisionCases->find(code))->second;
			T tObj = *typeObj;
			fnc(tObj);
		}
	}


	template <class T, class TList > static void MakeCall_List(TList x, uint4 code, T* obj)
	{
		TryMakeCall<T, TList::Head>(code, obj);
		MakeCall_List(TList::Tail(),code, obj);
	}

	template<class T>
	static void MakeCall_List(NullType, uint4 code, T* obj)
	{
	}


	template<class T, class TList> static void Call(T* obj);
};


#endif 