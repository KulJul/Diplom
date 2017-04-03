#ifndef _MYMAP_H_
#define _MYMAP_H_

#include <iostream>
#include <vector>
#include <functional>

#include <typeinfo>
#include <unordered_map>

#include "TypeCollection.h"

using namespace std;


typedef unsigned uint4;
typedef unsigned long long uint8;


template <class T1, class T2>
class MyMap
{
	//private:
	//	static uint8 key(const uint4 id1, const uint4 id2);

	public:
		static uint8 key(const uint4 id1, const uint4 id2);

		static std::unordered_map<uint8, void(*)(T1& arg1, T2& arg2)>* collisionCases;

		static void  addHandler(const uint4 id1, const uint4 id2, void(*handler)(T1&, T2&));
		
		static void  addHandler(void(*handler)(T1&, T2&));
};



#endif 
