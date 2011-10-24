#include "MyApp.h"

namespace lab4 {

	MyApp::MyApp() {
		_windowInfo.caption = "Lab2";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		addEntity(new MyFrontCamera());
		addEntity(new MyController());
		addEntity(new MyWorld());
		addEntity(new MyTeapot("Teapot1"));
	}
	void MyApp::createViews() {
		cg::View* v = createView("view");
		v->linkEntityAtEnd("Camera");
		v->linkEntityAtEnd("World");
		v->linkEntityAtEnd("Teapot1");
		v->linkEntityAtEnd("Controller");
	}
}