#ifndef GRASSWORLDFACTORY_H
#define GRASSWORLDFACTORY_H

#include "cg/cg.h"
#include "WorldFactory.h"
#include "GrassWall.h"

namespace example {

class GrassWorldFactory:WorldFactory
{
public:
	GrassWorldFactory(void);
	~GrassWorldFactory(void);

	void createSky();
	void createWall();


};

}

#endif