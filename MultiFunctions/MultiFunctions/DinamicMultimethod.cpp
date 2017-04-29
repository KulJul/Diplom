#include "Loki/MultiMethods.h"
#include <iostream>
#include "Loki/MultiMethods.h"

	// =====================================================
	// Class hierarchy:

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

		typedef void(*FctType)(Left0 &, Left0 &);

		// ========================================================
		// Functions

		void fct1(Left0 & l1, Left0 & l2)
		{
			std::cout << "fct1(): ";
			l1.help();
			l2.help();
			std::cout << "\n";
		}

		void fct2(Left0 & l1, Left0 & l2)
		{
			std::cout << "fct2(): ";
			l2.help();
			l1.help();
			std::cout << "\n";
		}



		// ========================================================
		// The dispatcher. By default the BaseRhs
		// coincides with the BaseLhs and the return value is void.
		// The Callback has signature
		//      ReturnType (*)( BaseLhs &, BaseRhs &)
		//

		typedef Loki::BasicDispatcher< Left0 > MyDispatcher;

		int main()
		{
			Left0 l0;
			Left1 l1;
			Left2 l2;

			MyDispatcher dsp;

			try {
				dsp.Add< Left0, Left0 >(fct1);
				dsp.Add< Left0, Left1 >(fct1);

				dsp.Go(l0, l0); // this calls fct1

								// fct2 replaces fct1 for 
				dsp.Add< Left0, Left0 >(fct2);
				dsp.Go(l0, l0); // this now calls fct2
				dsp.Go(l0, l1); // this still calls fct1

				dsp.Go(l1, l0); // this throws a runtime_error
			}
			catch (std::runtime_error & e) {
				std::cout << "Error: " << e.what() << "\n";
			}
		}
		
