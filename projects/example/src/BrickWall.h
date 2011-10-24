#ifndef BRICKWALL_H
#define BRICKWALL_H

#include "cg/cg.h"
#include "Wall.h"

namespace example{

class BrickWall:Wall
{
public:
	BrickWall(std::string id);
	~BrickWall(void);
	void makeTexture();
};

}
#endif
