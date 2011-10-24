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

#include "MyPhysics.h"

namespace lab6 {

	MyPhysics::MyPhysics() {
		_axesScale = 1.0;
		_position.set(0,0,0);
		_orientation.setRotationDeg(0,cg::Vector3d(0,1,0));
		_orientation.getGLMatrix(_rotationMatrix);
		_front.set(1,0,0);
		_up.set(0,1,0);
		_right.set(0,0,1);
		_linearVelocity = 0;
		_angularVelocity = 0;
		_isGoAhead = false;
		_isGoBack = false;
		_isYawLeft = false;
		_isYawRight = false;
		_isPitchUp = false;
		_isPitchDown = false;
		_isRollLeft = false;
		_isRollRight = false;
	}
	MyPhysics::~MyPhysics() {
	}
	void MyPhysics::setPosition(double x, double y, double z) {
		_position.set(x,y,z);
	}
	void MyPhysics::setLinearVelocity(double value) {
		_linearVelocity = value;
	}
	void MyPhysics::setAngularVelocity(double value) {
		_angularVelocity = value;
	}
	void MyPhysics::goAhead() { _isGoAhead = true; }
	void MyPhysics::goBack() { _isGoBack = true; }
	void MyPhysics::yawLeft() { _isYawLeft = true; }
	void MyPhysics::yawRight() { _isYawRight = true; }
	void MyPhysics::pitchUp() { _isPitchUp = true; }
	void MyPhysics::pitchDown() { _isPitchDown = true; }
	void MyPhysics::rollLeft() { _isRollLeft = true; }
	void MyPhysics::rollRight() { _isRollRight = true; }

	inline
	void MyPhysics::rotate(double elapsed_seconds, int direction, 
						   cg::Vector3d axis, cg::Vector3d& v1, cg::Vector3d& v2) 
	{
		_q.setRotationDeg(direction * _angularVelocity * elapsed_seconds,axis);
		v1 = apply(_q,v1);
		v2 = apply(_q,v2);
		_orientation = _q * _orientation;
	}
	void MyPhysics::step(double elapsed_seconds) {
		if(_isGoAhead) {
			_position += _front * _linearVelocity * elapsed_seconds;
			_isGoAhead = false;
		}
		if(_isGoBack) {
			_position -= _front * _linearVelocity * elapsed_seconds;
			_isGoBack = false;
		}
		if(_isYawLeft) {
			rotate(elapsed_seconds,1,_up,_front,_right);
			_isYawLeft = false;
		}
		if(_isYawRight) {
			rotate(elapsed_seconds,-1,_up,_front,_right);
			_isYawRight = false;
		}
		if(_isPitchUp) {
			rotate(elapsed_seconds,1,_right,_up,_front);
			_isPitchUp = false;
		}
		if(_isPitchDown) {
			rotate(elapsed_seconds,-1,_right,_up,_front);
			_isPitchDown = false;
		}
		if(_isRollLeft) {
			rotate(elapsed_seconds,1,_front,_right,_up);
			_isRollLeft = false;
		}
		if(_isRollRight) {
			rotate(elapsed_seconds,-1,_front,_right,_up);
			_isRollRight = false;
		}
		_orientation.getGLMatrix(_rotationMatrix);
	}
	void MyPhysics::applyTransforms() {
        glTranslated(_position[0],_position[1],_position[2]);
		glMultMatrixd(_rotationMatrix);
	}
	void MyPhysics::setAxesScale(double scale) {
		_axesScale = scale;
	}
	void MyPhysics::drawAxes() {
		glPushMatrix();
			glTranslated(_position[0],_position[1],_position[2]);
			glScaled(_axesScale,_axesScale,_axesScale);
			glColor3f(1.0f,0.0f,0.0f);
			glBegin(GL_LINES);
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(_front[0],_front[1],_front[2]);
			glEnd();
			glColor3f(0.0f,1.0f,0.0f);
			glBegin(GL_LINES);
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(_up[0],_up[1],_up[2]);
			glEnd();
			glColor3f(0.0f,0.0f,1.0f);
			glBegin(GL_LINES);
				glVertex3d(0.0,0.0,0.0);
				glVertex3d(_right[0],_right[1],_right[2]);
			glEnd();
		glPopMatrix();
	}
}