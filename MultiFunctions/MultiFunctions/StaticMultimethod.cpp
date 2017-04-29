//http://www.oocities.org/marco_corvi/games/loki/test/


#include "Loki/MultiMethods.h"
#include <iostream>
#include <vector>
#include <functional>
#include "game_hierarchy.hpp"
#include <typeinfo>
#include <unordered_map>

#include "typecollection.h"
#include "Loki/Typelist.h"
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



typedef Loki::StaticDispatcher<MyExec, Left0, TYPELIST_2(Left1, Left2)> MyDispatcher;

int main()
{
	Left0 l0;
	Left1 l1;
	Left2 l2;

	MyDispatcher dsp;
	MyExec exec;


	dsp.Go(l0, l1, exec);
	dsp.Go(l2, l1, exec);
}

