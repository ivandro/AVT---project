#ifndef HEART_H
#define HEART_H

#include <string>
#include "cg/cg.h"

namespace example {

	class Heart : public cg::Entity,
		public cg::IDrawListener,
		public cg::IUpdateListener
	{
	private:
		cg::Vector2d _position, _direction;
		bool _debug;
		double _angle;
		float _colorFaceB,_colorSidesB;
		int faceMod,sidesMod;


	public:

		Heart(std::string id);
		~Heart();
		void init();
		void drawHeart(float translate);
		void update(unsigned long elapsed_millis);
		void draw();
		void drawSide(float angle,float scale); 
		void setDebug(bool debug);
	};
}

#endif