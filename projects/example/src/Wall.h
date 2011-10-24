#ifndef WALL_H
#define WALL_H

#include "cg/cg.h"
#include "FreeImage.h"
#include "MyPhysics.h"

namespace example{

class Wall: public cg::Entity,
		public cg::IDrawListener
{

private:
		int _modelDL;	
		void makeModel();
		void Wall::dividedPlane(int n, 
			double x0, double y0, double x1, double y1,
			double nx, double ny, double nz,
			double tx0, double ty0, double tx1, double ty1);
		MyPhysics _physics;

public:
	Wall(std::string id);
	~Wall(void);

	GLuint _textureDL;
	virtual void makeTexture() const = 0;
	GLuint loadTexture(const char *filename);
	void settextureDL(GLuint textureDL);

	void init();
    void draw();
};

}
#endif