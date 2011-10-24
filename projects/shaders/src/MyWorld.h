#ifndef MY_WORLD_H
#define MY_WORLD_H

#include <string>
#include "cg/cg.h"
#include "FreeImage.h"

namespace shaders {

	class MyWorld : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		cg::Vector2f _size;
		int _modelDL;
		void makeModel();
		cg::ShaderProgram *tex_program;
		GLint uniform_tex;
		GLuint gl_texID;

	public:
		MyWorld(std::string id);
		~MyWorld();
		
		void init();
		void draw();
	};
}

#endif