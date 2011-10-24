#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <string>
#include "cg/cg.h"

namespace shaders {

	class MyObject : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		GLuint _modelDL;
		void initVertexArray();
		void initVertexArrayDisplayList();
		void initBufferObject();
		void drawVertexArray();
		void drawVertexArrayDisplayList();
		void drawBufferObject();

	public:
		MyObject(std::string id);
		~MyObject();
		
		void init();
		void draw();
	};
}

#endif