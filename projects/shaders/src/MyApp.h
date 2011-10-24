#ifndef MY_APP_H
#define MY_APP_H

#include "cg/cg.h"
#include "MyCamera.h"
#include "MyTeapot.h"
#include "MyObject.h"
#include "MyWorld.h"

namespace shaders {

	class MyApp : public cg::Application {
	public:
		MyApp();
		~MyApp();
		void createEntities();
		void createViews();
	};
}

#endif