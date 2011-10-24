#include "MyWorld.h"

namespace lab4 {

	MyWorld::MyWorld() : cg::Entity("World") {
	}
	MyWorld::~MyWorld() {
	}
	void MyWorld::makeModel() {
		cg::Vector2d half_size = _size/2.0;
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
	        glColor3f(0.1f,0.3f,0.1f);
			glBegin(GL_QUADS);
				glVertex3d(-half_size[0],0.0,-half_size[1]);
				glVertex3d( half_size[0],0.0,-half_size[1]);
				glVertex3d( half_size[0],0.0, half_size[1]);
				glVertex3d(-half_size[0],0.0, half_size[1]);
			glEnd();
		glEndList();
	}
	void MyWorld::init() {
		_size.set(10.0,10.0);
		makeModel();
	}
	void MyWorld::draw() {
		glCallList(_modelDL);
	}

}