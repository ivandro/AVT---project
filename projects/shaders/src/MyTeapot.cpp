#include "MyTeapot.h"

namespace shaders {

	MyTeapot::MyTeapot(std::string id) : cg::Entity(id) {
	}
	MyTeapot::~MyTeapot() {
	}
	void MyTeapot::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
			glutSolidTeapot(1.0);
		glEndList();
	}
	void MyTeapot::init() {
		makeModel();
		cg::ShaderManager *sm = cg::ShaderManager::instance();
		cg::VertexShader *vs = sm->createVertexShader("toon_vp","..\\..\\src\\toon_vp.glsl");
		cg::FragmentShader *fs = sm->createFragmentShader("toon_fp","..\\..\\src\\toon_fp.glsl");
		cg::GeometryShader *gs = sm->createGeometryShader("toon_gp","..\\..\\src\\toon_gp.glsl");
		toon_program = sm->createShaderProgram("toon_prg");
		gs->setTypes(GL_TRIANGLES, GL_TRIANGLE_STRIP);
		toon_program->attachVertexShader(vs);
		toon_program->attachFragmentShader(fs);
		toon_program->attachGeometryShader(gs);
		toon_program->link();
		uniform_lightDir = glGetUniformLocation(toon_program->getOpenglId(), "lightDir");
		uniform_triangleScale = glGetUniformLocation(toon_program->getOpenglId(), "triangleScale");
	}
	void MyTeapot::draw() {
		toon_program->bind();
		glUniform3f(uniform_lightDir,1.0f,0.0f,-1.0f);
		glUniform1f(uniform_triangleScale,0.95f);
		glPushMatrix();
			glTranslatef(0.0f,0.75f,0.0f);
			glCallList(_modelDL);
		glPopMatrix();
		toon_program->unbind();
	}
}