#include "MyWorld.h"

namespace lab2 {

	MyWorld::MyWorld(const std::string& id) : cg::Entity(id) {
	}
	MyWorld::~MyWorld() {
	}
	void MyWorld::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winWidth = win.width;
		_winHeight = win.height;
		_border = 10;
	}
	void MyWorld::draw() {
        glPushMatrix();
		glTranslatef(0.0f,0.0f,10.0f);
        glColor3f(0.1f,0.1f,0.3f);
        glRecti(_border,_border,_winWidth-_border,_winHeight-_border);
        glPopMatrix();
	}

}