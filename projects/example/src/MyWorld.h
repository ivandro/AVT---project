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

#ifndef MY_WORLD_H
#define MY_WORLD_H

#include <string>
#include "cg/cg.h"

namespace example {

	class MyWorld : public cg::Entity,
		public cg::IDrawListener
	{
	private:
		int _n;
		cg::Vector2d _size;

		int _modelDL;
		void makeModel();

		int _materialDL;
		void makeMaterial();

	public:
		MyWorld();
		~MyWorld();
		
		void init();
		void draw();
	};
}

#endif