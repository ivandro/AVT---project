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

#include "MyFPSCamera.h"

namespace example {

    MyFPSCamera::MyFPSCamera() : Entity("FPSCamera") {
	}
    MyFPSCamera::~MyFPSCamera() {
	}
    void MyFPSCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winSize.set(win.width,win.height);
		_orientation.setRotationDeg(0,cg::Vector3d::ny);
		_up.set(0,1,0);
		_front.set(1,0,0);
		_right.set(0,0,1);
		_isRoll = false;
		_isFPSMode = true;
		_isFirst = true;
		_position.set(0,0,0);
    }
    void MyFPSCamera::draw() {
		if(_isFPSMode) {
			_isFirst = false;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(80,_winSize[0]/(double)_winSize[1],1.0,100.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(_position[0],_position[1]+2.5,_position[2],_position[0]-3,_position[1],_position[2],_up[0],_up[1],_up[2]);

		}
    }

	void MyFPSCamera::onReshape(int width, int height) {
		_winSize.set(width,height);
	}

	void MyFPSCamera::toggleFPSMode() {
		_isFPSMode = !_isFPSMode;
	}

	bool MyFPSCamera::isActive(){
		return _isFPSMode;
	}


	void MyFPSCamera::setPosition(cg::Vector3d position){
		_position.set(position);
	}

}
