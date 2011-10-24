#include "MyWorld.h"

namespace shaders {

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
	MyWorld::MyWorld(std::string id) : cg::Entity(id) {
	}
	MyWorld::~MyWorld() {
	}
	void MyWorld::makeModel() {
		cg::Vector2f half_size = _size/2;
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
	        glColor3f(0.9f,0.9f,0.9f);
			glBegin(GL_QUADS);
				glNormal3f(0.0f,1.0f,0.0f);
				glTexCoord2f(0.0f,0.0f);
				glVertex3f(-half_size[0],0.0f,-half_size[1]);
				glTexCoord2f(1.0f,0.0f);
				glVertex3f(half_size[0],0.0f,-half_size[1]);
				glTexCoord2f(1.0f,1.0f);
				glVertex3f(half_size[0],0.0f,half_size[1]);
				glTexCoord2f(0.0f,1.0f);
				glVertex3f(-half_size[0],0.0f,half_size[1]);
			glEnd();
		glEndList();
	}
	void MyWorld::init() {
		_size.set(3.0,3.0);
		gl_texID = loadTexture("..\\..\\src\\crate.jpg");
		makeModel();
		cg::ShaderManager *sm = cg::ShaderManager::instance();
		cg::VertexShader *vs = sm->createVertexShader("tex_vp","..\\..\\src\\tex_vp.glsl");
		cg::FragmentShader *fs = sm->createFragmentShader("tex_fp","..\\..\\src\\tex_fp.glsl");
		tex_program = sm->createShaderProgram("tex_prg");
		tex_program->attachVertexShader(vs);
		tex_program->attachFragmentShader(fs);
		tex_program->link();
		uniform_tex = glGetUniformLocation(tex_program->getOpenglId(), "tex");
	}
	void MyWorld::draw() {
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0 + gl_texID);
		glBindTexture(GL_TEXTURE_2D, gl_texID);
		tex_program->bind();
		glUniform1i(uniform_tex,gl_texID);
		glPushMatrix();
			glCallList(_modelDL);
		glPopMatrix();
		tex_program->unbind();
		glDisable(GL_TEXTURE_2D);
	}
}