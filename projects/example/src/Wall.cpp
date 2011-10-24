#include "Wall.h"

namespace example{
Wall::Wall(std::string id) : cg::Entity(id) 
{
}

Wall::~Wall(void)
{
}

GLuint loadTexture(const char *filename) {

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

		FreeImage_Unload(dib);

		return gl_texID;
}

inline
	void Wall::dividedPlane(int n, 
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
	void Wall::makeModel() {
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

	void Wall::init() {
		_physics.setPosition(3,1.01,3);
		makeTexture();
		makeModel();
	}

	void Wall::draw() {
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureDL);
			glCallList(_modelDL);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}



void Wall::settextureDL(GLuint textureDL){
		_textureDL = textureDL;
}

}