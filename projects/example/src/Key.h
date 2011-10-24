// This file is an example for CGLib.
//
// CGLib is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// CGLib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CGLib; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
// Copyright 2007 Carlos Martinho

#ifndef KEY_H
#define KEY_H

#include "cg/cg.h"
#include <string>
#include "MyPhysics.h"

namespace example {

	class Key : public cg::Entity,
		public cg::IUpdateListener,
		public cg::IDrawListener 
	{
	private:
		MyPhysics _physics;
		GLUquadricObj *_quadricObj;
		int _modelDL, _modelFront;
		int _materialDL;
		void makeQuadric();
		void makeModel();
		void makeFront();
		void createBox(int n, 
		double x0, double y0, double x1, double y1,
		double nx, double ny, double nz);
		void drawCube();
		void makeMaterial();
	public:
		Key(std::string id);
		~Key();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
	};

}

#endif