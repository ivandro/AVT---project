#include "BrickWall.h"

namespace example{

BrickWall::BrickWall(std::string id):Wall("BrickWall"){}
BrickWall::~BrickWall(void){}

inline void BrickWall::makeTexture() {
	GLuint texture = loadTexture("..\\..\\src\\brick.tga");
	settextureDL(texture);
}

}