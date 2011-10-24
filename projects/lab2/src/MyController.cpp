#include "MyController.h"

namespace lab2 {

	MyController::MyController(const std::string& id) : cg::Entity(id) {
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
		if(key == 'a') {
			if(cg::Registry::instance()->exists("Rectangle1") == false) {
				MyRectangle* r = new MyRectangle("Rectangle1");
				cg::Registry::instance()->add(r);
				cg::View *v = (cg::View *)cg::Registry::instance()->get("view1");
				v->linkEntityAtEnd("Rectangle1");
				r->init();
			}
		} else if(key == 'r') {
			if(cg::Registry::instance()->exists("Rectangle1")) {
				cg::View *v = (cg::View *)cg::Registry::instance()->get("view1");
				v->unlinkEntity("Rectangle1");
				MyRectangle *r = (MyRectangle *)cg::Registry::instance()->get("Rectangle1");
				cg::Registry::instance()->remove("Rectangle1");
				delete r;
			}
		}
	}
	void MyController::onSpecialKeyReleased(int key) {
        if (key == GLUT_KEY_F1) {
			cg::Manager::instance()->getApp()->dump();
        }
	}

}