#ifndef GRASSWALL_H
#define GRASSWALL_H

#include "cg/cg.h"
#include "Wall.h"

namespace example{

class GrassWall:Wall
{
public:
	GrassWall(std::string id);
	~GrassWall(void);
	void makeTexture();
};

}
#endif
