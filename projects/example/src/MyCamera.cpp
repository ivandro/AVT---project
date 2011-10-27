
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

#include "MyCamera.h"

namespace example {

    MyCamera::MyCamera() : Entity("Camera") {
	}
    MyCamera::~MyCamera() {
	}
    void MyCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winSize.set(win.width,win.height);
		_orientation.setRotationDeg(0,cg::Vector3d::ny);
		_up.set(0,1,0);
		_front.set(1,0,0);
		_right.set(0,0,1);
		_isRoll = false;
		_isTopMode = false;
    }
    void MyCamera::draw() {
		if(_isTopMode){
			_position = _front * 15.0;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60,_winSize[0]/(double)_winSize[1],1.0,100.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(_position[0],_position[1],_position[2],0,0,0,_up[0],_up[1],_up[2]);
		}
    }
	void MyCamera::onReshape(int width, int height) {
		_winSize.set(width,height);
	}
	void MyCamera::onMouse(int button, int state, int x, int y) {
		_isRoll = (button == GLUT_RIGHT_BUTTON);
		_lastMousePosition.set(x,y);
	}
	void MyCamera::onMouseMotion(int x, int y) {
		if(_isRoll) {
			double anglez = (_lastMousePosition[0] - x) / (double)5;
				_q.setRotationDeg(anglez,_front);
				_up = apply(_q,_up);
				_right = apply(_q,_right);
				_orientation = _q * _orientation;
		} else {
			double anglex = (_lastMousePosition[0] - x) / (double)5;
				_q.setRotationDeg(anglex,_up);
				_front = apply(_q,_front);
				_right = apply(_q,_right);
				_orientation = _q * _orientation;
			double angley = (y - _lastMousePosition[1]) / (double)5;
				_q.setRotationDeg(angley, _right);
				_up = apply(_q,_up);
				_front = apply(_q,_front);
				_orientation = _q * _orientation;
		}
		_lastMousePosition.set(x,y);
	}
	void MyCamera::onMousePassiveMotion(int x, int y) {
	}
	void MyCamera::toggleTopMode() {
		_isTopMode = !_isTopMode;

	}

		void MyCamera::setPosition(cg::Vector3d position){
		_position.set(position);

	}
}
