#ifndef MY_TEAPOT_H
#define MY_TEAPOT_H

#include <string>
#include "cg/cg.h"

namespace shaders {

	class MyTeapot : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		int _modelDL;
		void makeModel();
		cg::ShaderProgram *toon_program;
		GLint uniform_lightDir;
		GLint uniform_triangleScale;

	public:
		MyTeapot(std::string id);
		~MyTeapot();
		
		void init();
		void draw();
	};
}

#endif