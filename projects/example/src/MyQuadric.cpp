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

#include "MyQuadric.h"

namespace example {

	MyQuadric::MyQuadric(std::string id) : cg::Entity(id) {
	}
	MyQuadric::~MyQuadric() {
	}
	inline
	void MyQuadric::makeQuadric() {
		_quadricObj = gluNewQuadric();
		gluQuadricCallback(_quadricObj, GLU_ERROR, 0);
		gluQuadricDrawStyle(_quadricObj, GLU_FILL);
		gluQuadricOrientation(_quadricObj, GLU_OUTSIDE); 
		gluQuadricNormals(_quadricObj, GLU_SMOOTH);
		gluQuadricTexture(_quadricObj, GL_FALSE);
	}
	inline
	void MyQuadric::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
			gluSphere(_quadricObj,1.0,25,20);
		glEndList();
	}
	inline
	void MyQuadric::makeMaterial() {
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
	void MyQuadric::init() {
		_physics.setPosition(3.5,1.0,-3.5);
		_physics.setAngularVelocity(20.0);
		makeQuadric();
		makeModel();
		makeMaterial();
	}
	void MyQuadric::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / (double)1000;
		_physics.step(elapsed_seconds);
	}
	void MyQuadric::draw() {
		glPushMatrix();
			glCallList(_materialDL);
			_physics.applyTransforms();
			glCullFace(GL_BACK);
			glCallList(_modelDL);
			glCullFace(GL_FRONT);
		glPopMatrix();
	}
}