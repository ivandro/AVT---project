#ifndef MY_APP_H
#define MY_APP_H

#include "cg/cg.h"
#include "MyTopCamera.h"
#include "MyController.h"
#include "MyRectangle.h"
#include "MyWorld.h"

namespace lab2 {

	class MyApp : public cg::Application {
	public:
		MyApp();
		~MyApp();
		void createEntities();
		void createViews();
	};
}

#endif