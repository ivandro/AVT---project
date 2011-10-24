#ifndef MY_WORLD_H
#define MY_WORLD_H

#include <string>
#include "cg/cg.h"

namespace lab4 {

	class MyWorld : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		cg::Vector2d _size;
		int _modelDL;
		void makeModel();

	public:
		MyWorld();
		~MyWorld();
		
		void init();
		void draw();
	};
}

#endif