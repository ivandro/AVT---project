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

#ifndef MY_QUADRIC_H
#define MY_QUADRIC_H

#include "cg/cg.h"
#include <string>
#include "MyPhysics.h"

namespace example {

	class MyQuadric : public cg::Entity,
		public cg::IUpdateListener,
		public cg::IDrawListener 
	{
	private:
		MyPhysics _physics;
		GLUquadricObj *_quadricObj;
		int _modelDL;
		int _materialDL;
		void makeQuadric();
		void makeModel();
		void makeMaterial();
	public:
		MyQuadric(std::string id);
		~MyQuadric();
		void init();
		void update(unsigned long elapsed_millis);
		void draw();
	};

}

#endif