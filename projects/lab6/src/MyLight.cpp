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

#include "MyLight.h"

namespace lab6 {

	MyLight::MyLight(std::string id) : cg::Entity(id) {
	}
	MyLight::~MyLight() {
	}
	void MyLight::init() {
		_physics.setPosition(-4.0,3.0,-4.0);
		_physics.setLinearVelocity(5.0);
		_physics.setAngularVelocity(100.0);
		_physics.setAxesScale(1.0);

		GLfloat ambient_light[] = {0.1f,0.1f,0.1f,1.0f};
		GLfloat diffuse_light[] = {0.9f,0.9f,0.9f,1.0f};
		GLfloat specular_light[] = {0.9f,0.9f,0.9f,1.0f};
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
		glEnable(GL_LIGHT0);

		makeLight();
		_isDebug = false;
	}
	inline
	void MyLight::makeLight() {
		float position[] = {0.0,0.0,0.0,1.0};
		float direction[] = {1.0,0.0,0.0};
		_lightDL = glGenLists(1);
		assert(_lightDL != 0);
		glNewList(_lightDL,GL_COMPILE);
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
		glEndList();
	}
	void MyLight::update(unsigned long elapsed_millis) {
		if(cg::KeyBuffer::instance()->isKeyDown('t')) {
			_physics.goAhead();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('g')) {
			_physics.goBack();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('f')) {
			_physics.yawLeft();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('h')) {
			_physics.yawRight();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('r')) {
			_physics.pitchUp();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('v')) {
			_physics.pitchDown();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('b')) {
			_physics.rollLeft();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('n')) {
			_physics.rollRight();
		}
		double elapsed_seconds = elapsed_millis / (double)1000;
		_physics.step(elapsed_seconds);
	}
	void MyLight::draw() {
		glPushMatrix();
			_physics.applyTransforms();
			glCallList(_lightDL);
		glPopMatrix();
		if(_isDebug) {
			glDisable(GL_LIGHTING);
			glPushMatrix();
				_physics.drawAxes();
			glPopMatrix();
			glPushMatrix();
				_physics.applyTransforms();
				glColor3f(0.9f,0.9f,0.9f);
				glTranslatef(0.4f,0.0f,0.0f);
				glRotatef(-90.0f,0.0f,1.0f,0.0f);
				glutWireCone(0.4,0.4,10,10);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		}
	}
	void MyLight::toggleDebugMode() {
		_isDebug = !_isDebug;
	}
}