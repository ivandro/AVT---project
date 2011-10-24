#ifndef MY_BOX_H
#define MY_BOX_H

#include <string>
#include "cg/cg.h"
#include "MyPhysics.h"

namespace lab4 {

	class MyTeapot : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener
	{
	private:
		int _modelDL;
		void makeModel();
		MyPhysics _physics;

		bool _debugMode;

	public:
		MyTeapot(std::string id);
		~MyTeapot();
		
		void init();
		void update(unsigned long elapsed_millis);
		void draw();

		void toggleDebugMode();
	};
}

#endif