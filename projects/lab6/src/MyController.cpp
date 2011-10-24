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

#include "MyController.h"

namespace lab6 {

	MyController::MyController() : cg::Entity("Controller") {
	}
	MyController::~MyController() {
	}
	void MyController::init() {
	}
	void MyController::onKeyPressed(unsigned char key) {
        if (key == 27) {
			cg::Manager::instance()->shutdownApp();
        }
	}
	void MyController::onKeyReleased(unsigned char key) {
	}
	void MyController::onSpecialKeyPressed(int key) {
	}
	void MyController::onSpecialKeyReleased(int key) {
        if (key == GLUT_KEY_F1) {
			cg::Manager::instance()->getApp()->dump();
        }
        if (key == GLUT_KEY_F2) {
			MyTeapot *box = (MyTeapot*)cg::Registry::instance()->get("Teapot1");
			if(box) {
				box->toggleDebugMode();
			}
			MyLight *light = (MyLight*)cg::Registry::instance()->get("Light1");
			if(light) {
				light->toggleDebugMode();
			}
        }
	}
	void MyController::drawOverlay() {
		glColor3f(0.3f,0.3f,0.3f);
		cg::Util::instance()->drawBitmapString("Press [ESC] to exit.",10,52);
		cg::Util::instance()->drawBitmapString("Press [F1] to dump registry to logfile.",10,38);
		cg::Util::instance()->drawBitmapString("Press [F2] to toggle debug mode.",10,24);
		cg::Util::instance()->drawBitmapString("Press [MOUSE LEFT] to rotate and [MOUSE RIGHT] to roll camera.",10,10);
	}
}