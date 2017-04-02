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


template <typename T>
class MyMap
{
	private:
		static uint8 key(const uint4 id1, const uint4 id2);

	public:

		static std::unordered_map<uint4, void(*)(T& other)>* collisionCases;


		static void  addHandler(const uint4 id1, void(*handler)(T&));

		static void collideWith(T & other);

};



#endif 
