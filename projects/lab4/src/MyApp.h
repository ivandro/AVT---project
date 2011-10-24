#ifndef MY_APP_H
#define MY_APP_H

#include "cg/cg.h"
#include "MyFrontCamera.h"
#include "MyController.h"
#include "MyTeapot.h"
#include "MyWorld.h"

namespace lab4 {

	class MyApp : public cg::Application {
	public:
		MyApp();
		~MyApp();
		void createEntities();
		void createViews();
	};
}

#endif