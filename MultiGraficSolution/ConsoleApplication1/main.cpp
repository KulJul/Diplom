#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "glaux.h"
#include <glut.h>
#include "MilkshapeModel.h"
#include <cstdio>
#include "tgaload.h"
#include "Object.h"
#include <vector>
#include "library/Loki/Typelist.h"
#include "library/SimpleMiltimethodSeveral.h"
#include "library/Loki/TypeCollection.h"
#include "library/Loki/SimpleMultiMethod.h"
#include "Collapsing.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

using namespace std;

Model *pModel = NULL;
Model *pModel2 = NULL;
Model *pModel3 = NULL;

GLuint texture_id[2];

GLuint	texture[2];	


space_ship ship;
asteroid ast;
space_station station;


static vector<game_object*> vec;

using MyDispatcher = StaticDispatcherTwo<MyExecObject, game_object, game_object, TYPELIST_3(space_ship, asteroid, space_station)>;
MyDispatcher dsp;

Collapsing collapsing;

AUX_RGBImageRec *LoadBMP(const char *Filename)						
{
	FILE *File = NULL;												

	if (!Filename)													
	{
		return NULL;												
	}

	File = fopen(Filename, "r");										

	if (File)														
	{
		fclose(File);												
		return auxDIBImageLoadA(Filename);							
	}

	return NULL;													
}

GLuint LoadGLTexture(const char *filename)						
{
	AUX_RGBImageRec *pImage;										
	GLuint texture = 0;												

	pImage = LoadBMP(filename);									

	
	if (pImage != NULL && pImage->data != NULL)					
	{
		glGenTextures(1, &texture);									

		
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		free(pImage->data);											
		free(pImage);												
	}

	return texture;													
}



vector<game_object*>& get_obj_pointers()
{
	static vector<game_object*> objs; 

	if (objs.empty())
	{
		objs.push_back(&ship);
		objs.push_back(&ast);
		objs.push_back(&station);
	}

	return objs;
}

void collide()
{

	for (auto i = 0; i < vec.size(); i++)
	{
		for (auto j = 0; j < vec.size(); j++)
		{
			if (i >= j)
				continue;

			if (abs(get_obj_pointers()[i]->x - get_obj_pointers()[j]->x) < 10 &&
				abs(get_obj_pointers()[i]->y - get_obj_pointers()[j]->y) < 10)
			{
				collapsing.Collapse(*(get_obj_pointers()[i]), *(get_obj_pointers()[j]));

				MyExecObject exec;

				dsp.Go(*get_obj_pointers()[i],*get_obj_pointers()[j], exec);
				get_obj_pointers();
			}
		}
	}

}

void InitGL(GLvoid)     
{

	collapsing.Init();

	glScalef(10.0, 10.0, 10.0f);
	station.pModel->reloadTextures();
	ship.pModel->reloadTextures();


	glShadeModel(GL_SMOOTH);							
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				
	glClearDepth(1.0f);									
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);								
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);



	
	glEnable(GL_TEXTURE_2D);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, texture_id);
	image_t   temp_image;

	glBindTexture(GL_TEXTURE_2D, texture_id[0]);
	tgaLoad("data/as.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
	glEnable(GL_CULL_FACE);




	ast.InitModelTexture();

	AUX_RGBImageRec *texture2;
	texture2 = auxDIBImageLoadA("Data/space.bmp");
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture2->data);

}

void display(void)   
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	gluLookAt(0, 0, 60, 0, 0, 0, 0, 1, 0);
	glScalef(-180.0, -130.0, -3.0f);
	glTranslated(-10, 15, 5);
	glRotatef(1, 1.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-300.0f, -300.0f, 300.0f);
	glTexCoord2f(300.0f, 0.0f); glVertex3f(300.0f, -300.0f, 300.0f);
	glTexCoord2f(300.0f, 300.0f); glVertex3f(300.0f, 300.0f, 300.0f);
	glTexCoord2f(0.0f, 300.0f); glVertex3f(-300.0f, 300.0f, 300.0f);
	glEnd();
	glPopMatrix();

	collide();

	ast.render();
	station.render();
	ship.render();

	glutSwapBuffers();
	
}

void reshape(int width, int height)   
{
	if (height == 0)													
	{
		height = 1;													
	}

	glViewport(0, 0, width, height);									

	glMatrixMode(GL_PROJECTION);									
	glLoadIdentity();												

	
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);	

	glMatrixMode(GL_MODELVIEW);										
	glLoadIdentity();												
}

void keyboard(unsigned char key, int x, int y)  
{
	switch (key) {
	case 27:        
		exit(0);   
		break;  

	case 'w':
		ast.y += 2.0f;
		break;
	case 's':
		ast.y -= 2.0f;
		break;
	case 'a':
		ast.x -= 2.0f;
		break;
	case 'd':
		ast.x += 2.0f;
		break;


	case 'u':
		station.y += 2.0f;
		break;
	case 'j':
		station.y -= 2.0f;
		break;
	case 'h':
		station.x -= 2.0f;
		break;
	case 'k':
		station.x += 2.0f;
		break;
	default:        
		break;
	}
}

void arrow_keys(int a_keys, int x, int y)  
{
	switch (a_keys) {


	case 101:
		ship.y += 2.0f;
		break;
	case 103:
		ship.y -= 2.0f;
		break;
	case 100:
		ship.x -= 2.0f;
		break;
	case 102:
		ship.x += 2.0f;
		break;



	default:
		break;
	}
}


int main(int argc, char** argv)   
{

	if (ship.InitModel() == 0 || ast.InitModel() == 0 || station.InitModel() == 0)
		return 0;

	vec = get_obj_pointers();

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("Diplom"); 
	
	InitGL();
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(arrow_keys);
	glutIdleFunc(display);
	glutMainLoop();          
	return 0;
}

