#include "GrassWall.h"

namespace example{

GrassWall::GrassWall(std::string id):Wall("GrassWall"){}
GrassWall::~GrassWall(void){}

inline void GrassWall::makeTexture() {
	GLuint texture = loadTexture("..\\..\\src\\grass.tga");
	settextureDL(texture);
}

}