#ifndef NIGHTWORLDFACTORY_H
#define NIGHTWORLDFACTORY_H

#include "cg/cg.h"
#include "WorldFactory.h"
#include "BrickWall.h"

namespace example {

class NightWorldFactory:WorldFactory
{
public:
	NightWorldFactory(void);
	~NightWorldFactory(void);
	void createSky();
	void createWall();

};

}

#endif