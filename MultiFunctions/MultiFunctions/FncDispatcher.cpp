/** sample test for the Loki library
*
* @author marco corvi
* @date dec 2004
*
* This code is part of a set of sample test programs for the Loki library.
*
* The Loki library is copyright(c) 2001 by Andrei Alexandrescu.
* It is described in the book:
*     Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and
*     Design Patterns Applied". Copyright (c) 2001. Addison-Wesley.
* and is available from
*     http://sourceforge.net/projects/loki-lib/
*
* Permission to use, copy, modify, distribute and sell this software
*     (ie, the test programs) for any purpose is hereby granted without fee.
* Permission to use, copy, modify, distribute and sell the software
*     changes made to the Loki library is hereby granted without fee
*     for any purposes provided the original Loki library copyright notice
*     appears in all copies and that both that notice and this
*     permission notice appear in supporting documentation.
* The author makes no representations about the suitability of this
*     software for any purpose. It is provided "as is" without express
*     or implied warranty.
*
* ===========================================================
* This sample program show the usage of the function
* dispatcher (see pg. 281)
*
*/

#include "Loki/MultiMethods.h"
#include <iostream>
#include "Loki/MultiMethods.h"


// =====================================================
// Class hierarchy:

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

// ========================================================
// Functions

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
}


// ========================================================
// The dispatcher. By default the BaseRhs
// coincides with the BaseLhs and the return value is void.
// The Callback has signature
//      ReturnType (*)( BaseLhs &, BaseRhs &)
//

typedef Loki::FnDispatcher< Left0 > MyDispatcher;

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
}