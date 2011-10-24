#ifndef MY_WORLD_H
#define MY_WORLD_H

#include <string>
#include "cg/cg.h"

namespace lab2 {

	class MyWorld : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		unsigned int _winWidth, _winHeight, _border;

	public:
		MyWorld(const std::string& id);
		~MyWorld();
		
		void init();
		void draw();
	};
}

#endif