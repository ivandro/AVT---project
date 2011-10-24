#include "MyTopCamera.h"

namespace lab2 {

	MyTopCamera::MyTopCamera(const std::string& id) : Entity(id) {
	}
    MyTopCamera::~MyTopCamera() {
	}
    void MyTopCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
    }
    void MyTopCamera::draw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,_winWidth,0,_winHeight,0,-100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
	void MyTopCamera::onReshape(int width, int height) {
		_winWidth = width;
		_winHeight = height;
	}
}
