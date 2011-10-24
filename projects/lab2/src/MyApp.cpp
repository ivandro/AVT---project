#include "MyApp.h"

namespace lab2 {

	MyApp::MyApp() {
		_windowInfo.caption = "Lab2";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		addEntity(new MyController("controller"));
		addEntity(new MyWorld("world"));
		addEntity(new MyRectangle("rectangle"));
		addEntity(new MyTopCamera("camera"));
	}
	void MyApp::createViews() {
		cg::View* v0 = createView("view1");
		v0->setViewport(0.1f,0.25f,0.35f,0.5f);
		v0->linkEntityAtEnd("camera");
		v0->linkEntityAtEnd("world");
		v0->linkEntityAtEnd("rectangle");

		cg::View* v1 = createView("view2");
		v1->setViewport(0.55f,0.25f,0.35f,0.5f);
		v1->linkEntityAtEnd("camera");
		v1->linkEntityAtEnd("world");
		v1->linkEntityAtEnd("rectangle");
	}
}