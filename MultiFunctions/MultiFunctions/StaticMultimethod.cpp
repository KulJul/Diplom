//http://www.oocities.org/marco_corvi/games/loki/test/


#include <iostream>
#include <vector>
#include <functional>
#include "game_hierarchy.hpp"
#include <typeinfo>
#include <unordered_map>

#include "typecollection.h"
#include "Loki/Typelist.h"
#include "Loki/SimpleMultiMethod.h"
#include "Loki/MultiMethods.h"

using namespace std;

struct Left0
{
	virtual void help() { std::cout << "Left-0 \n"; }
};

struct Left1 : public Left0
{
	virtual void help() override { std::cout << "Left-1 \n"; }
};

struct Left2 : public Left0
{
	virtual void help() override { std::cout << "Left-2 \n"; }
};



class MyExec
{
public:
	void Fire(Left0 & l1, Left0 & l2)
	{
		std::cout << "MyExec::Fire() \n";
		l1.help();
		l2.help();
	}

	void OnError(Left0 & l1, Left0 & l2)
	{
		std::cout << "MyExec::OnError() \n";
	}
};


using MyDispatcher = StaticDispatcher2<MyExec, Left0, TYPELIST_2(Left1, Left2)>;

//int main()
//{
//	Left0 left0;
//	Left1 left1;
//	Left2 left2;
//
//	MyDispatcher dsp;
//	MyExec exec;
//
//	dsp.Go(left1, left0, exec);
//	dsp.Go(left2, left1, exec);
//}

