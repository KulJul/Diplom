#include "Loki/MultiMethods.h"
#include <iostream>
#include "Loki/MultiMethods.h"



struct Left0
{
	int left0Member;
	virtual void help() { std::cout << "Left-0 "; }
};

struct Left1 : public Left0
{
	int left1Member;
	void help() override { std::cout << "Left-1 "; }
};

struct Left2 : public Left1
{
	int left2Member;
	void help() override{ std::cout << "Left-2 "; }
};

/*
void fct1(Left0 & l1, Left0 & l2)
{
	std::cout << "fct1(): ";
	l1.help();
	l2.help();
	std::cout << "\n";
}

void fct2(Left0 & l1, Left1 & l2)
{
	std::cout << "fct2(): ";
	l1.help();
	l2.help();
	std::cout << "\n";
}

void fct3(Left1 & l1, Left2 & l2)
{
	std::cout << "fct3(): ";
	l1.help();
	l2.help();
	std::cout << "\n";
}*/



//typedef Loki::FnDispatcher< Left0 > MyDispatcher;
/*
int main()
{
	Left0 l0;
	l0.left0Member = 5;


	Left1 l1;
	l1.left0Member = 7;
	l1.left1Member = 10;
	

	Left2 l2;
	l2.left0Member = 13;
	l2.left2Member = 15;

	MyDispatcher dsp;

	try {
		//теперь так не будем обращаитьс€, это бы требовала кастинга внутри функций нашей бизнес логики
		//dsp.Add< Left0, Left0 >(fct1); // (1)
		//dsp.Add< Left1, Left0 >(fct1); // (2)
		//dsp.Add< Left0, Left1 >(fct1); // (3)
									   // dsp.Add< Left0, Left1 >( fct2 ); // illegal

		dsp.Add< Left0, Left0, fct1 >(); // (4) == (1) 
		dsp.Add< Left0, Left1, fct2 >(); // (5) replace (2)
		dsp.Add<Left1, Left2, fct3, true>();

		dsp.Go(l0, l0); // use (4)
		dsp.Go(l0, l1); // use (5)

		dsp.Go(l1, l2);
		dsp.Go(l2, l1);



	}
	catch (std::runtime_error & e) {
		std::cout << "Error: " << e.what() << "\n";
	}
}*/