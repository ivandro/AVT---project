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
// Copyright 2007-2011 Carlos Martinho

#ifndef TEXTURED_BOX_H
#define TEXTURED_BOX_H

#include "cg/cg.h"
#include "FreeImage.h"
#include "MyPhysics.h"

namespace example {
	class MyTexturedBox : public cg::Entity,
		public cg::IUpdateListener,
		public cg::IDrawListener
	{
	private:
		int _modelDL;
		int _materialDL;
		GLuint _textureDL;
		void makeModel();
		void makeMaterial();
		void makeTexture();
		void MyTexturedBox::dividedPlane(int n, 
			double x0, double y0, double x1, double y1,
			double nx, double ny, double nz,
			double tx0, double ty0, double tx1, double ty1);
		MyPhysics _physics;

	public:
		MyTexturedBox(std::string id);
		~MyTexturedBox();

        void init();
        void update(unsigned long elapsed_millis);
        void draw();
	};
}

#endif