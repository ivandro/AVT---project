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

#include "MyWorld.h"

namespace lab6 {

	MyWorld::MyWorld() : cg::Entity("World") {
	}
	MyWorld::~MyWorld() {
	}
	void MyWorld::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
	        glColor3f(0.1f,0.3f,0.1f);
			glBegin(GL_QUADS);
				glNormal3f(0.0,1.0,0.0);
				cg::Vector2d cursor = -_size/(double)2;
				cg::Vector2d step = _size / (double)_n;
				for(double x = cursor[0], nx = 0; nx != _n ; x += step[0], nx++) {
					for(double y = cursor[1], ny = 0; ny != _n ; y += step[1], ny++) {
						glVertex3d(x, 0, y);
						glVertex3d(x + step[0], 0, y);
						glVertex3d(x + step[0], 0, y + step[1]);
						glVertex3d(x, 0, y + step[1]);
					}
				}
			glEnd();
		glEndList();
	}
	void MyWorld::makeMaterial() {
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,0.0f};
		GLfloat mat_ambient[] = {0.7f,0.7f,0.7f,1.0f};
		GLfloat mat_diffuse[] = {0.1f,0.9f,0.1f,1.0f};
		GLfloat mat_specular[] = {0.1f,0.1f,0.1f,1.0f};
		GLfloat mat_shininess[] = {0.0f};

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
	void MyWorld::init() {
		_n = 100;
		_size.set(10.0,10.0);
		makeModel();
		makeMaterial();
	}
	void MyWorld::draw() {
		glCallList(_materialDL);
		glCallList(_modelDL);
	}

}