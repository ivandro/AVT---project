// This file is an example for CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#include "MyTeapot.h"

namespace lab6 {

	MyTeapot::MyTeapot(std::string id) : cg::Entity(id) {
	}
	MyTeapot::~MyTeapot() {
	}
	inline
	void MyTeapot::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
			glColor3f(0.7f,0.7f,0.3f);
			glutSolidTeapot(1.0);
		glEndList();
	}
	inline
	void MyTeapot::makeMaterial() {
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,0.0f};
		GLfloat mat_ambient[] = {0.7f,0.7f,0.7f,1.0f};
		GLfloat mat_diffuse[] = {0.9f,0.5f,0.1f,1.0f};
		GLfloat mat_specular[] = {0.9f,0.9f,0.9f,1.0f};
		GLfloat mat_shininess[] = {100.0f};

		_materialDL = glGenLists(1);
		assert(_materialDL != 0);
		glNewList(_materialDL,GL_COMPILE);
			glMaterialfv(GL_FRONT,GL_EMISSION ,mat_emission);
			glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
		glEndList();
	}
	void MyTeapot::init() {
		_physics.setPosition(-3.5,0.75,3.5);
		_physics.setLinearVelocity(5.0);
		_physics.setAngularVelocity(100.0);
		_physics.setAxesScale(3.0);
		makeModel();
		makeMaterial();
		_debugMode = false;
	}
	void MyTeapot::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / (double)1000;
		if(cg::KeyBuffer::instance()->isKeyDown('w')) {
			_physics.goAhead();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('s')) {
			_physics.goBack();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('a')) {
			_physics.yawLeft();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('d')) {
			_physics.yawRight();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('z')) {
			_physics.pitchUp();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('q')) {
			_physics.pitchDown();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('x')) {
			_physics.rollLeft();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('c')) {
			_physics.rollRight();
		}
		_physics.step(elapsed_seconds);
	}
	void MyTeapot::draw() {
		if(_debugMode) {
			glDisable(GL_LIGHTING);
			_physics.drawAxes();
			glEnable(GL_LIGHTING);
		}
        glPushMatrix();
			glCallList(_materialDL);
			_physics.applyTransforms();
			glCallList(_modelDL);
		glPopMatrix();
	}
	void MyTeapot::toggleDebugMode() {
		_debugMode = !_debugMode;
	}
}