#ifndef MY_RECTANGLE_H
#define MY_RECTANGLE_H

#include <string>
#include "cg/cg.h"

namespace lab2 {

	class MyRectangle : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener
	{
	private:
		cg::Vector2d _position, _direction;
		double _velocity, _acceleration, _stopped;
		double _angle, _angularVelocity;

	public:
		MyRectangle(std::string id);
		~MyRectangle();
		
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
	};
}

#endif