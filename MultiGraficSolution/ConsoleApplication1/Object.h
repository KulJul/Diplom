#pragma once
#include <iostream>

struct game_object
{
	Model* pModel;
	char* name_struct;

	int x = 0;
	int y = 0;
	int z = 0;
	int rot;

	int radius;

	virtual ~game_object()
	{
	}
};


struct space_ship
	: game_object
{

	int InitModel()
	{
		pModel = new MilkshapeModel();
		pModel->m_name = "data/marksman.bmp";
		if (pModel->loadModelData("data/marksman.ms3d") == false)
		{
			return 0;
		}

		return 1;
	}

	int render()
	{

		glPushMatrix();
		glLoadIdentity();
		gluLookAt(0, 0, 75, 0, 0, 0, 0, 1, 0);
		glRotatef(rot, 0.0f, 1.0f, 0.0f);
		glTranslatef(-20, 0.0f, 0.0f);
		glTranslated(x + 5, y + 5, 0);
		glScalef(20.0, 20.0, 20.0f);
		pModel->draw();
		glPopMatrix();

		return 1;
	}
};

struct space_station
	: game_object
{
	int x_space_station = 0;
	int y_space_station = 0;

	int ast_space_station_rot = 0;


	int InitModel()
	{
		pModel = new MilkshapeModel();
		pModel->m_name = "data/succubus.bmp";
		if (pModel->loadModelData("data/succubus.ms3d") == false)
		{
			return 0;
		}

		return 1;
	}

	int render()
	{

		glPushMatrix();
		glLoadIdentity();
		gluLookAt(75, 75, 75, 0, 0, 0, 0, 1, 0);
		glRotatef(rot + 0, 0.0f, 1.0f, 0.0f);
		glTranslated(x + 5, y + 5, 0);
		glScalef(10.0, 10.0, 10.0f);
		pModel->draw();
		glPopMatrix();

		return 1;
	}
};

struct asteroid
	: game_object
{
	int x_space_ast = 0;
	int y_space_ast = 0;

	int ast_space_rot = 0;


	GLuint texture_id[2];

	GLuint	texture_ast;


	void InitModelTexture()
	{
		AUX_RGBImageRec *texture1;
		texture1 = auxDIBImageLoadA("Data/aster.bmp");
		glGenTextures(1, &texture_ast);
		glBindTexture(GL_TEXTURE_2D, texture_ast);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	}

	int InitModel()
	{
		pModel = new MilkshapeModel();
		pModel->m_name = "data/aster.bmp";
		if (pModel->loadModelData("data/ast.ms3d") == false)
		{
			return 0;
		}

		return 1;
	}


	int render()
	{
		glPushMatrix();
		glLoadIdentity();
		glBindTexture(GL_TEXTURE_2D, texture_ast);
		gluLookAt(20, 25, 60, 0, 0, 0, 0, 1, 0);
		glScalef(3.0, 3.0, 3.0f);
		glTranslated(x + 5, y + 5, 0);
		glRotatef(rot + 10, 5.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
		auto quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		gluQuadricTexture(quadratic, GL_TRUE);
		gluSphere(quadratic, 1.3f, 20, 20);
		glEnd();
		glPopMatrix();

		return 1;
	}

};



class MyExecObject
{
public:
	static void Fire(game_object, game_object)
	{
		//return "Unsupported colliding!";
	}

	static void Fire(space_ship, space_ship)
	{
		//return "Space ship collides with space ship";
	}

	static void Fire(space_ship, asteroid)
	{
		//return "Space ship collides with asteroid";
	}

	static void Fire(asteroid, space_ship)
	{
		//return "Asteroid collides with space ship";
	}

	static void Fire(asteroid, asteroid)
	{
		//return "Asteroid collides with asteroid";
	}


	void OnError(game_object & l1, game_object & l2)
	{
		//std::cout << "MyExec::OnError() \n";
	}

};
