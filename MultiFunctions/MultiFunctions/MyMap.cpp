#include "MyMap.h"

template <class T>
uint8 MyMap<T>::key(const uint4 id1, const uint4 id2)
{
	return uint8(id1) << 32 | id2;
}

template <class T>
void MyMap<T>::addHandler(const uint4 id1, void(*handler)(T&))
{
	(*collisionCases).insert({ id1, handler });
}


template <class T>
void MyMap<T>::collideWith(T& other) {

}


template <class T>
std::unordered_map<uint4, void(*)(T& other)>* MyMap<T>::collisionCases = new std::unordered_map<uint4, void(*)(T& other)>;


