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
// Copyright 2007-2011 Carlos Martinho

#include "MyTexturedBox.h"

namespace example {

	static GLuint loadTexture(const char *filename) {

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib(0);
		BYTE* bits(0);
		GLuint gl_texID;
		unsigned int width(0), height(0);

		fif = FreeImage_GetFileType(filename, 0);
		if(fif == FIF_UNKNOWN) {
			fif = FreeImage_GetFIFFromFilename(filename);
			return 0;
		}

		if(FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if(!dib)
			return false;

		dib = FreeImage_ConvertTo24Bits(dib);
		bits = FreeImage_GetBits(dib);
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		if((bits == 0) || (width == 0) || (height == 0))
			return 0;

		glGenTextures(1, &gl_texID);
		glBindTexture(GL_TEXTURE_2D, gl_texID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
		// FreeImage loads textures in BGR format.

		FreeImage_Unload(dib);

		return gl_texID;
	}

	MyTexturedBox::MyTexturedBox(std::string id) : cg::Entity(id) {
	}
	MyTexturedBox::~MyTexturedBox() {
	}
	inline
	void MyTexturedBox::dividedPlane(int n, 
		double x0, double y0, double x1, double y1,
		double nx, double ny, double nz,
		double tx0, double ty0, double tx1, double ty1) 
	{
		int countx = 0;
		int county = 0;
		double x = x0;
		double y = y0;
		double stepx = (x1-x0)/(double)n;
		double stepy = (y1-y0)/(double)n;
		double tx = tx0;
		double ty = ty0;
		double steptx = (tx1-tx0)/(double)n;
		double stepty = (ty1-ty0)/(double)n;

		glBegin(GL_QUADS);
		glNormal3d(nx,ny,nz);

		while (countx != n) {
			while (county != n) {
				glTexCoord2d(tx, ty);
				glVertex3d(x, 0, y);
				glTexCoord2d(tx+steptx, ty);
				glVertex3d(x+stepx, 0, y);
				glTexCoord2d(tx+steptx, ty+stepty);
				glVertex3d(x+stepx, 0, y+stepy);
				glTexCoord2d(tx, ty+stepty);
				glVertex3d(x, 0, y+stepy);
				county++;
				y += stepy;
				ty += stepty;
			}
			countx++;
			x += stepx;
			tx += steptx;
			county = 0;
			y = y0;
			ty = ty0;
		}

		glEnd();
	}

	inline
	void MyTexturedBox::makeTexture() {
		_textureDL = loadTexture("..\\..\\src\\crate.tga");
	}

	inline
	void MyTexturedBox::makeMaterial() {
		GLfloat mat_emission[] = {0.0f,0.0f,0.0f,0.0f};
		GLfloat mat_ambient[] = {0.5f,0.5f,0.5f,1.0f};
		GLfloat mat_diffuse[] = {0.7f,0.7f,0.7f,1.0f};
		GLfloat mat_specular[] = {0.0f,0.0f,0.0f,1.0f};
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
	inline
	void MyTexturedBox::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
			// TOP
			glPushMatrix();
				glTranslatef(0,1,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0, 0,0,1,1);
			glPopMatrix();
			// BOTTOM
			glPushMatrix();
				glTranslatef(0,-1,0);
				glRotatef(180, 1,0,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0, 0,0,1,1);
			glPopMatrix();
			// LEFT
			glPushMatrix();
				glTranslatef(0,0,1);
				glRotatef(90,1,0,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0, 0,0,1,1);
			glPopMatrix();
			// RIGHT
			glPushMatrix();
				glTranslatef(0,0,-1);
				glRotatef(-90,1,0,0);
				dividedPlane(10, -1,-1,1,1, 0,1,0, 0,0,1,1);
			glPopMatrix();
			// FRONT
			glPushMatrix();
				glTranslatef(1,0,0);
				glRotatef(-90,0,0,1);
				dividedPlane(10, -1,-1,1,1, 0,1,0, 0,0,1,1);
			glPopMatrix();
			// BACK
			glPushMatrix();
				glTranslatef(-1,0,0);
				glRotatef(90,0,0,1);
				dividedPlane(10, -1,-1,1,1, 0,1,0, 0,0,1,1);
			glPopMatrix();
		glEndList();
	}
	void MyTexturedBox::init() {
		_physics.setPosition(3,1.01,3);
		_physics.setAngularVelocity(10.0);
		makeMaterial();
		makeTexture();
		makeModel();
	}
	void MyTexturedBox::update(unsigned long elapsed_millis) {
		_physics.yawLeft();//nao esta a andar..
		double elapsed_seconds = elapsed_millis / (double)1000;
		_physics.step(elapsed_seconds);
	}
	void MyTexturedBox::draw() {
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureDL);
			glCallList(_materialDL);
			_physics.applyTransforms();
			glCallList(_modelDL);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}