/**********************************************************************

  Castle - using Display Lists

  June, 12th, 2000

  This tutorial was written by Philipp Crocoll
  Contact: 
	philipp.crocoll@web.de
	www.codecolony.de

  Every comment would be appreciated.

  If you want to use parts of any code of mine:
	let me know and
	use it!
**********************************************************************
ESC: exit

CAMERA movement:
w : forwards
s : backwards
a : turn left
d : turn right
x : turn up
y : turn down
v : strafe right
c : strafe left
r : move up
f : move down

**********************************************************************/

   
#include <GL\glut.h>		//includes gl.h and glu.h
#include <math.h>			//sine and cosine functions
#include "camera.h"
#include <windows.h>
#define PI 3.1415265359

static GLfloat MatSpec[] = {1.0,1.0,1.0,1.0};
static GLfloat MatShininess[] = {45.0};
static GLfloat LightPos[] = {-2.0,1.5,1.0,0.0};
static GLfloat ModelAmb[] = {0.5,0.5,0.5,0.0};


CCamera Camera;

GLint TowerListNum,WallsListNum;  //Numbers of the display lists
GLint WallsList;
//Tower properties:
int NumOfEdges = 20;
GLfloat LowerHeight = 3.0;
GLfloat HigherHeight = 3.5;
GLfloat HR = 1.3;  //Radius of the highest part

//Wall properties:
GLfloat WallElementSize = 0.2;
GLfloat WallHeight = 2.0;

void DrawHigherWallPart(int NumElements)
/*Draws a wall part like this:
	 ___	___	   ___
	|	|  |   |  |   |
	|___|  |___|  |___| 
  and so on
  such an element is squareshaped and has the height/width WallElementSize*/
{
	glBegin(GL_QUADS);
	for (int i = 0; i < NumElements; i++)
	{
		glNormal3f(0.0,0.0,-1.0);
		glVertex3f(i*2.0 * WallElementSize, 0.0, 0.0);
		glVertex3f(i*2.0 * WallElementSize, WallElementSize, 0.0);
		glVertex3f((i*2.0+1.0) * WallElementSize, WallElementSize, 0.0);
		glVertex3f((i*2.0+1.0) * WallElementSize, 0.0, 0.0);

	}

	glEnd();

}

void DrawWall(GLfloat Length)
{
	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,-1.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,WallHeight,0.0);
		glVertex3f(Length,WallHeight,0.0);
		glVertex3f(Length,0.0,0.0);
	glEnd();
	int i = (int)(Length / WallElementSize / 2);
	if (i * WallElementSize > Length) i--;
	glPushMatrix();
		glTranslatef(0.0,WallHeight,0.0);
		DrawHigherWallPart(i);
	glPopMatrix();
}
		


void Init(void) //used to create the display lists
{
	TowerListNum = glGenLists(1);
	GLfloat x,z;
	GLfloat NVectY;  //y component for the NVects of the higher part

	glNewList(TowerListNum, GL_COMPILE);
		glBegin(GL_QUADS);
		//Create the lower part of the tower:
		for (int i = 0; i < NumOfEdges-1; i++)
		{	
			x = cos((float)i/(float)NumOfEdges * PI * 2.0);
			z = sin((float)i/(float)NumOfEdges * PI * 2.0);
			glNormal3f(x,0.0,z);
			glVertex3f(x,LowerHeight,z);
			//same x,z and NVect:
			glVertex3f(x,0.0,z);

			x = cos((float)(i+1)/(float)NumOfEdges * PI * 2.0);
			z = sin((float)(i+1)/(float)NumOfEdges * PI * 2.0);
			glNormal3f(x,0.0,z);
			glVertex3f(x,0.0,z);
			//same x,z and NVect:
			glVertex3f(x,LowerHeight,z);
		}
		x = cos((float)i/(float)NumOfEdges * PI * 2.0);
		z = sin((float)i/(float)NumOfEdges * PI * 2.0);
		glNormal3f(x,0.0,z);
		glVertex3f(x,LowerHeight,z);
		//same x,z and NVect:
		glVertex3f(x,0.0,z);
		x = cos(1.0/(float)NumOfEdges * PI * 2.0);
		z = sin(1.0/(float)NumOfEdges * PI * 2.0);
		glNormal3f(x,0.0,z);
		glVertex3f(x,0.0,z);
		//same x,z and NVect:
		glVertex3f(x,LowerHeight,z);
		
		
		//Create the higher part:

		//The y component is the same for all NVects, so we can calculate it here:
		NVectY = (HR-1.0) / (LowerHeight - HigherHeight) * (HR-1.0);

		for (i = 0; i < NumOfEdges-1; i++)
		{	
			x = cos((float)i/(float)NumOfEdges * PI * 2.0);
			z = sin((float)i/(float)NumOfEdges * PI * 2.0);
			glNormal3f(x,NVectY,z);
			glVertex3f(x*HR,HigherHeight,z*HR);
			//same x,z and NVect:
			glVertex3f(x,LowerHeight,z);

			x = cos((float)(i+1)/(float)NumOfEdges * PI * 2.0);
			z = sin((float)(i+1)/(float)NumOfEdges * PI * 2.0);
			glNormal3f(x,NVectY,z);
			glVertex3f(x,LowerHeight,z);
			//same x,z and NVect:
			glVertex3f(x*HR,HigherHeight,z*HR);
		}
		x = cos((float)i/(float)NumOfEdges * PI * 2.0);
		z = sin((float)i/(float)NumOfEdges * PI * 2.0);
		glNormal3f(x,NVectY,z);
		glVertex3f(x*HR,HigherHeight,z*HR);
		//same x,z and NVect:
		glVertex3f(x,LowerHeight,z);
		x = cos(1.0/(float)NumOfEdges * PI * 2.0);
		z = sin(1.0/(float)NumOfEdges * PI * 2.0);
		glNormal3f(x,NVectY,z);
		glVertex3f(x,LowerHeight,z);
		//same x,z and NVect:
		glVertex3f(x*HR,HigherHeight,z*HR);
		
		glEnd();
	glEndList();

	////////////////////////////////////////////////////////////

	//WallList

	////////////////////////////////////////////////////////////

	WallsListNum = glGenLists(1);
	glNewList(WallsListNum, GL_COMPILE);
	DrawWall(10.0);
	glPushMatrix();
	glTranslatef(10.0,0.0,0.0);
	glPushMatrix();
		glRotatef(270.0,0.0,1.0,0.0);
		DrawWall(10.0);
	glPopMatrix();
	glTranslatef(0.0,0.0,10.0);
	glPushMatrix();
		glRotatef(180.0,0.0,1.0,0.0);
		DrawWall(5.0);
		glRotatef(90.0,0.0,1.0,0.0);
		glTranslatef(0.0,0.0,5.0);
		DrawWall(5.0);
	glPopMatrix();
	glTranslatef(-5.0,0.0,5.0);
	glPushMatrix();
		glRotatef(180.0,0.0,1.0,0.0);
		DrawWall(5.0);
	glPopMatrix();

	//Last and longest piece:
	glPushMatrix();
		glRotatef(90.0,0.0,1.0,0.0);
		glTranslatef(0.0,0.0,-5.0);
		DrawWall(6.0);
		//the "door"
			glTranslatef(6.0,0.0,0.0);
			glBegin(GL_QUADS);
				glNormal3f(0.0,0.0,-1.0);
				glVertex3f(0.0,WallHeight / 2.0,0.0);
				glVertex3f(0.0,WallHeight,0.0);
				glVertex3f(3.0,WallHeight,0.0);
				glVertex3f(3.0,WallHeight / 2.0,0.0);
				
			glEnd();
			i = (int)(3.0 / WallElementSize / 2);
			if (i * WallElementSize > 3.0) i--;
				glPushMatrix();
				glTranslatef(0.0,WallHeight,0.0);
				DrawHigherWallPart(i);
			glPopMatrix();

		
		glTranslatef(3.0,0.0,0.0);
		DrawWall(6.0);
	glPopMatrix();
	

	glPopMatrix();


	glEndList();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	Camera.Render();
	glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	glTranslatef(-5.0,0.0,0.0);
	glRotatef(90.0,0.0,1.0,0.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0,1.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(10.0,0.0,0.0);
		glVertex3f(10.0,0.0,10.0);
		glVertex3f(5.0,0.0,15.0);
		glVertex3f(0.0,0.0,15.0);
		glVertex3f(0.0,0.0,0.0);
	glEnd();


	//Turn two sided lighting on for the walls
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glCallList(WallsListNum);
	
	//Disable it again for the towers:
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	

	
	glCallList(TowerListNum);
	
	glTranslatef(10.0,0.0,0.0);
	glCallList(TowerListNum);

	glTranslatef(0.0,0.0,10.0);
	glCallList(TowerListNum);

	glTranslatef(-5.0,0.0,5.0);
	glCallList(TowerListNum);

	glTranslatef(-5.0,0.0,0.0);
	glCallList(TowerListNum);

	glFlush();			//Finish rendering
	glutSwapBuffers();	//Swap the buffers ->make the result of rendering visible
}
void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();
	//Angle of view:40 degrees
	//Near clipping plane distance: 0.5
	//Far clipping plane distance: 20.0
	gluPerspective(40.0,(GLdouble)x/(GLdouble)y,1.0,200.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,x,y);  
}
void KeyDown(unsigned char key, int x, int y)
{	
	switch(key)
	{
	case 27:	//ESC
		exit(0);
		break;
	case 'a':		
		Camera.RotateY(5.0);
		Display();
		break;
	case 'd':		
		Camera.RotateY(-5.0);
		Display();
		break;
	case 'w':		
		Camera.MoveForwards( -0.3 ) ;
		Display();
		break;
	case 's':		
		Camera.MoveForwards( 0.3 ) ;
		Display();
		break;
	case 'x':		
		Camera.RotateX(5.0);
		Display();
		break;
	case 'y':		
		Camera.RotateX(-5.0);
		Display();
		break;
	case 'c':		
		Camera.StrafeRight(-0.3);
		Display();
		break;
	case 'v':		
		Camera.StrafeRight(0.3);
		Display();
		break;
	case 'f':
		Camera.Move(F3dVector(0.0,-0.3,0.0));
		Display();
		break;
	case 'r':
		Camera.Move(F3dVector(0.0,0.3,0.0));
		Display();
		break;

	
	}
}

int main(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(300,300);
	glutCreateWindow("Castle");
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glClearColor(0.0,0.0,0.0,0.0);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyDown);
	Camera.Move(F3dVector(0.0,5.0,20.0));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ModelAmb);
	Init();
	glutMainLoop();
	return 0;
}