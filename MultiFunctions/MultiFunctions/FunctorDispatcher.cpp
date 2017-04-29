#include "Loki/MultiMethods.h"
#include <iostream>
#include "Loki/MultiMethods.h"

	// =====================================================
	// Class hierarchy:
	// 

	struct Left0
{
	virtual void help() { std::cout << "Left-0 "; }
};

		struct Left1 : public Left0
		{
			virtual void help() { std::cout << "Left-1 "; }
		};

		struct Left2 : public Left1
		{
			virtual void help() { std::cout << "Left-2 "; }
		};



		// ========================================================
		// Functors

		template< class C1, class C2 >
		struct MyFun
		{
			void operator()(C1 & c1, C2 & c2)
			{
				std::cout << "MyFun-" << typeid(C1).name() << "-"
					<< typeid(C2).name() << ":  ";
				c1.help();
				c2.help();
				std::cout << "\n";
			}
		};

		// ========================================================
		// The dispatcher. By default the BaseRhs
		// coincides with the BaseLhs and the return value is void.
		// The Callback has signature
		//      ReturnType (*)( BaseLhs &, BaseRhs &)
		//

		typedef Loki::FunctorDispatcher< Left0 > MyDispatcher;

		int main()
		{
			Left0 l0;
			Left1 l1;
			Left2 l2;

			MyFun fun00;
			MyFun fun01;
			MyFun fun10;
			MyFun fun02;

			MyDispatcher dsp;

			try {
				dsp.Add< Left0, Left0, MyFun >(fun00); // (1)
				dsp.Add< Left0, Left1, MyFun >(fun01); // (2)
				dsp.Add< Left2, Left1, MyFun >(fun00); // (3)

				dsp.Go(l0, l0); // use (1)
				dsp.Go(l0, l1); // use (2)
				dsp.Go(l2, l1); // use (3)
				dsp.Go(l2, l0); // this throws a runtime_error

			}
			catch (std::runtime_error & e) {
				std::cout << "Error: " << e.what() << "\n";
			}
		}

