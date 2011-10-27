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

namespace example {

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

		_materialDL = glGenLists(1);
		assert(_materialDL != 0);
		glNewList(_materialDL,GL_COMPILE);
			 glMaterialfv(GL_FRONT,GL_EMISSION ,mat_emission);
			 glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialBank::getAmbientVec(MaterialBank::MATERIAL_GOLD));
			 glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialBank::getDiffuseVec(MaterialBank::MATERIAL_GOLD));
			 glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialBank::getSpecularVec(MaterialBank::MATERIAL_GOLD));
			 glMaterialf(GL_FRONT, GL_SHININESS, MaterialBank::getShininess(MaterialBank::MATERIAL_GOLD));
		glEndList();
	}
	void MyTeapot::init() {
		_physics.setPosition(3,1.01,-3);
		_physics.setLinearVelocity(5.0);
		_physics.setAngularVelocity(100.0);
		_physics.setAxesScale(3.0);
		makeModel();
		makeMaterial();
		_debugMode = false;
	}
	void MyTeapot::update(unsigned long elapsed_millis) {
		
		if(!_debugMode){
			double elapsed_seconds = elapsed_millis / (double)1000;
			if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_UP)) {
				_physics.goAhead();
			}
			if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN)) {
				_physics.goBack();
			}
			if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_LEFT)) {
				_physics.yawLeft();
			}
			if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
				_physics.yawRight();
			}
		
		_physics.step(elapsed_seconds);
		}
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