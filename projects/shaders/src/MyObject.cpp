#include "MyObject.h"

#define N_BFO 2
#define VTX 0
#define IDX 1

namespace shaders {

	static GLuint buffers[N_BFO];

	static GLfloat vertices[][3] = {
		{ -1.0, -1.0, -1.0 },
		{ 1.0, -1.0, -1.0 },
		{ 1.0, 1.0, -1.0 },
		{ -1.0, 1.0, -1.0 },
		{ -1.0, -1.0, 1.0 },
		{ 1.0, -1.0, 1.0 },
		{ 1.0, 1.0, 1.0 },
		{ -1.0, 1.0, 1.0 }
	};
	static GLubyte indices[][4] = {
		{ 0, 1, 2, 3 },
		{ 4, 7, 6, 5 },
		{ 0, 4, 5, 1 },
		{ 3, 2, 6, 7 },
		{ 0, 3, 7, 4 },
		{ 1, 5, 6, 2 }
	};

	MyObject::MyObject(std::string id) : cg::Entity(id) {
		_modelDL = -1;
	}
	MyObject::~MyObject() {
	}
	void MyObject::initVertexArray() {
		// Vertex Array (v1.5) because of glDrawElements - otherwise 1.1
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, &indices[0]);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void MyObject::initVertexArrayDisplayList() {
		// Vertex Array with Display List (v1.5) becasue of glDrawElements - otherwise 1.1
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glNewList(_modelDL,GL_COMPILE);
			glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, &indices[0]);
		glEndList();
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void MyObject::initBufferObject() {
		// Buffer Object (v3.1)
		glGenBuffers(N_BFO, buffers);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[VTX]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[IDX]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	void MyObject::init() {
		//initVertexArray();
		//initVertexArrayDisplayList();
		initBufferObject();
	}
	void MyObject::drawVertexArray() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);			
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void MyObject::drawVertexArrayDisplayList() {
		glCallList(_modelDL);
	}
	void MyObject::drawBufferObject() {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, 0);		
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	void MyObject::draw() {
		glPushMatrix();
			//drawVertexArray();
			//drawVertexArrayDisplayList();
			drawBufferObject();
		glPopMatrix();
	}
}