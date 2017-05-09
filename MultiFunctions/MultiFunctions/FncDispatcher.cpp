
#include "Loki/MultiMethods.h"
#include <iostream>
#include "Loki/MultiMethods.h"

#include "GameObject.h"
#include "Asteroid.h"
#include "SpaceShip.h"
#include "SpaceStantion.h"
#include "Collide.h"
#include "Conversation.h"


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

typedef Loki::FnDispatcher<GameObject> MyDispatcher;

int main()
{
	std::vector<GameObject> gameObjectCollection;

	GameObject* asteroid1 = new Asteroid();
	auto asteroid2 = new Asteroid();
	gameObjectCollection.push_back(*asteroid1);
	gameObjectCollection.push_back(*asteroid2);

	GameObject* spaceShip1 = new SpaceShip();
	auto spaceShip2 = new SpaceShip();
	gameObjectCollection.push_back(*spaceShip1);
	gameObjectCollection.push_back(*spaceShip2);

	GameObject* spaceStation1 = new SpaceStation();
	auto spaceStation2 = new SpaceStation();
	gameObjectCollection.push_back(*spaceStation1);
	gameObjectCollection.push_back(*spaceStation2);


	auto collideRelationship = new Collide();
	auto conversationRelationship = new Сonversation();


	Loki::FnDispatcher<GameObject> dispatcher;
	Loki::MultiFnDispatcher<GameObject> multiDispatcher;

	try {

		dispatcher.Add<Asteroid, SpaceShip, true >([collideRelationship](Asteroid& ast, SpaceShip& spsh) 
			{
			return collideRelationship->Colliding(ast, spsh);
			});

		dispatcher.Go(*asteroid1, *spaceShip1);

		multiDispatcher.Add<Asteroid, SpaceShip, SpaceStation, true>([collideRelationship](Asteroid& ast, SpaceShip& spsh, SpaceStation& spst)
			{
			return collideRelationship->Colliding(ast, spsh, spst);
			});

		multiDispatcher.Go(*asteroid1, *spaceShip1, *spaceStation1);



		////теперь так не будем обращаиться, это бы требовала кастинга внутри функций нашей бизнес логики
		////dsp.Add< Left0, Left0 >(fct1); // (1)
		////dsp.Add< Left1, Left0 >(fct1); // (2)
		////dsp.Add< Left0, Left1 >(fct1); // (3)
		// ;/// dsp.Add< Left0, Left1 >( fct2 ); // illegal

		//dsp.Add< Left0, Left0, fct1 >(); // (4) == (1) 
		//dsp.Add< Left0, Left1, fct2 >(); // (5) replace (2)
		//dsp.Add<Left1, Left2, fct3, true>();

		//dsp.Go(l0, l0); // use (4)
		//dsp.Go(l0, l1); // use (5)

		//dsp.Go(l1, l2);
		//dsp.Go(l2, l1);



	}
	catch (std::runtime_error & e) {
		std::cout << "Error: " << e.what() << "\n";
	}



}