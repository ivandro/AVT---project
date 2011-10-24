#include "MyController.h"

namespace lab4 {

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
			box->toggleDebugMode();
        }
	}
	void MyController::drawOverlay() {
		glColor3f(0.3f,0.3f,0.3f);
		cg::Util::instance()->drawBitmapString("Press [ESC] to exit.",10,38);
		cg::Util::instance()->drawBitmapString("Press [F1] to dump registry to logfile.",10,24);
		cg::Util::instance()->drawBitmapString("Press [F2] to toggle debug mode.",10,10);
	}
}