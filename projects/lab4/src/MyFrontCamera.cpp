#include "MyFrontCamera.h"

namespace lab4 {

    MyFrontCamera::MyFrontCamera() : Entity("Camera") {
	}
    MyFrontCamera::~MyFrontCamera() {
	}
    void MyFrontCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
		_position.set(0,10,-15);
    }
    void MyFrontCamera::draw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		gluPerspective(60,_winWidth/(double)_winHeight,1.0,100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		gluLookAt(_position[0],_position[1],_position[2],0,0,0,0,1,0);
    }
	void MyFrontCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
