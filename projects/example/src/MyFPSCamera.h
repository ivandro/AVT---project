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

#ifndef MY_FPS_CAMERA_H
#define MY_FPS_CAMERA_H

#include <string>
#include "cg/cg.h"
#include "MyPhysics.h"

namespace example {

    class MyFPSCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		cg::Vector2d _winSize;
		cg::Vector3d _position;
		cg::Vector3d _up,_front,_right;
		cg::Quaterniond _orientation, _q;
		cg::Vector2d _lastMousePosition;
		bool _isRoll, _isFPSMode, _isFirst;

    public:
		MyFPSCamera();
        virtual ~MyFPSCamera();
        void init();
        void draw();
        void onReshape(int width, int height);
		void toggleFPSMode();
		bool isActive();
		void setPosition(cg::Vector3d position);
	};
}

#endif
