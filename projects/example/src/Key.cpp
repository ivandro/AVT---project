#include "Key.h"

namespace example {

	Key::Key(std::string id) : cg::Entity(id) {
	}
	Key::~Key() {
	}
	inline
	void Key::makeQuadric() {
		_quadricObj = gluNewQuadric();
		gluQuadricCallback(_quadricObj, GLU_ERROR, 0);
		gluQuadricDrawStyle(_quadricObj, GLU_FILL);
		gluQuadricOrientation(_quadricObj, GLU_OUTSIDE); 
		gluQuadricNormals(_quadricObj, GLU_SMOOTH);
		gluQuadricTexture(_quadricObj, GL_FALSE);
	}
	inline
	void Key::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
			gluCylinder	(_quadricObj, 0.07, 0.07, 1.5, 25, 20);
		glEndList();
	}
	
	inline
	void Key::makeMaterial() {
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,1.0f};
		GLfloat mat_ambient[] = {0.3f,0.3f,0.1f,1.0f};
		GLfloat mat_diffuse[] = {0.9f,0.9f,0.1f,1.0f};
		GLfloat mat_specular[] = {0.9f,0.9f,0.9f,1.0f};
		GLfloat mat_shininess[] = {100.0f};

		_materialDL = glGenLists(1);
		assert(_materialDL != 0);
		glNewList(_materialDL,GL_COMPILE);
			glMaterialfv(GL_FRONT,GL_EMISSION,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
		glEndList();
	}
	void Key::init() {
		_physics.setPosition(0,1.0,-6);
		//_physics.setAngularVelocity(20.0);
		makeQuadric();
		makeModel();
		makeFront();
		//makeMaterial();
	}
	void Key::update(unsigned long elapsed_millis) {
		/*double elapsed_seconds = elapsed_millis / (double)1000;
		_physics.step(elapsed_seconds);*/
	}
	void Key::draw() {
		glPushMatrix();
		//	glCallList(_materialDL);
			_physics.applyTransforms();
			glCullFace(GL_BACK);
			glCallList(_modelDL);
			glCallList(_modelFront);
			glCullFace(GL_FRONT);
		glPopMatrix();
	}

	
/*criacao da parte da frente da chave*/
inline 
	void  Key::createBox(int n, 
		double x0, double y0, double x1, double y1,
		double nx, double ny, double nz) 
	{
		int countx = 0;
		int county = 0;
		double x = x0;
		double y = y0;
		double stepx = (x1-x0)/(double)n; 
		double stepy = (y1-y0)/(double)n;

		glBegin(GL_QUADS);
		glNormal3d(nx,ny,nz);

		while (countx != n) {
			while (county != n) {
				glVertex3d(x, 0, y);
				glVertex3d(x+stepx, 0, y);
				glVertex3d(x+stepx, 0, y+stepy);
				glVertex3d(x, 0, y+stepy);
				county++;
				y += stepy;				
			}
			countx++;
			x += stepx;			
			county = 0;
			y = y0;			
		}

		glEnd();
	}

inline void Key::drawCube(){
			// TOP
			glPushMatrix();
				glTranslatef(0,1,0);
				createBox(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// BOTTOM
			glPushMatrix();
				glTranslatef(0,-1,0);
				glRotatef(180, 1,0,0);
				createBox(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// LEFT
			glPushMatrix();
				glTranslatef(0,0,1);
				glRotatef(90,1,0,0);
				createBox(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// RIGHT
			glPushMatrix();
				glTranslatef(0,0,-1);
				glRotatef(-90,1,0,0);
				createBox(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// FRONT
			glPushMatrix();
				glTranslatef(1,0,0);
				glRotatef(-90,0,0,1);
				createBox(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
			// BACK
			glPushMatrix();
				glTranslatef(-1,0,0);
				glRotatef(90,0,0,1);
				createBox(10, -1,-1,1,1, 0,1,0);
			glPopMatrix();
}

inline
	void Key::makeFront() {
		_modelFront = glGenLists(1);
		assert(_modelFront != 0);
		
		glNewList(_modelFront,GL_COMPILE);
	
		glPushMatrix();
			glScaled(0.05,0.15,0.3);
			drawCube();
		glPopMatrix();

		glScaled(0.07,0.3,0.07);

		glPushMatrix();
			drawCube();
		glPopMatrix();		
		
		glPushMatrix();
			glTranslated(0,0,3);
			drawCube();
		glPopMatrix();		

		glPushMatrix();
			glTranslated(0,0,-3);
			drawCube();
		glPopMatrix();		

		glEndList();
	}
 }