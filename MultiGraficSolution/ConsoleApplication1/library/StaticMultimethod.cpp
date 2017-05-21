//http://www.oocities.org/marco_corvi/games/loki/test/


#include <iostream>

#include "Loki/SimpleMultiMethod.h"
#include "SimpleMiltimethodSeveral.h"
#include "SimpleMultimethodSim.h"
#include "Loki\Typelist.h"


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


struct Left3 : public Left0
{
	virtual void help() override { std::cout << "Left-3 \n"; }
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

	void Fire(Left0 & l1, Left0 & l2, Left0 & l3)
	{
		std::cout << "MyExec::Fire() \n";
		l1.help();
		l2.help();
		l3.help();
	}

	void OnError(Left0 & l1, Left0 & l2)
	{
		std::cout << "MyExec::OnError() \n";
	}

	void OnError(Left0 & l1, Left0 & l2, Left0 & l3)
	{
		std::cout << "MyExec::OnError() \n";
	}
};


using MyDispatcher = StaticDispatcher2<MyExec, Left0, typeCollectionNew::TypeCollectionMake<Left1, Left2>>;
using MyDispatcherSym = StaticDispatcherSym<MyExec, Left0, typeCollectionNew::TypeCollectionMake<Left1, Left2>, false>;
using MyDispatcher2 = StaticDispatcher3<MyExec, Left0, Left0, Left0, TYPELIST_3(Left1, Left2, Left3)>;


/*
int main()
{
	Left0 left0;
	Left1 left1;
	Left2 left2;
	Left3 left3;

	MyDispatcher dsp;
	MyDispatcher2 dsp2;
	MyDispatcherSym dspSym;
	MyExec exec;

	dsp.Go(left1, left2, exec);
	dspSym.Go(left1, left2, exec);
	dsp2.Go(left1, left2, left3, exec);
}

*/