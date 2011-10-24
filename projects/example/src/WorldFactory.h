#ifndef WORLDFACTORY_H
#define WORLDFACTORY_H

#include <string>
#include "cg/cg.h"

namespace example {

class WorldFactory
{
public:
	WorldFactory(void);
	~WorldFactory(void);

	virtual void createSky() const = 0;
	virtual void createWall() const = 0;
};

}

#endif


/*
for(x)
for(y)
 if (color ==black)
		Factory.createwall(x,y);
 if(player)

 if(ground)

 if(enemies)

 if(water)

 if(decoration)

 if(lamp)



*/