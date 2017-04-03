#include "MyMap.h"

template <class T1, class T2>
uint8 MyMap<T1,T2>::key(const uint4 id1, const uint4 id2)
{
	return uint8(id1) << 32 | id2;
}

template <class T1, class T2>
void MyMap<T1,T2>::addHandler(const uint4 id1, const uint4 id2, void(*handler)(T1&, T2&))
{
	(*collisionCases).insert({ key(id1, id2), handler });
}

template <class T1, class T2>
void MyMap<T1, T2>::addHandler(void(*handler)(T1&, T2&))
{
	(*collisionCases).insert({ key(typeid(T1).hash_code(), typeid(T2).hash_code()), handler });
}



template <class T1, class T2>
std::unordered_map<uint8, void(*)(T1& arg1, T2& arg2)>* MyMap<T1,T2>::collisionCases = new std::unordered_map<uint8, void(*)(T1& arg1, T2& arg2)>;


