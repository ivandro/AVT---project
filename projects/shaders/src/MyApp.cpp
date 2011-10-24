#include <GL/glew.h>

#include "MyApp.h"

namespace shaders {

	MyApp::MyApp() {
		_windowInfo.caption = "Shaders";
		_windowInfo.width = 800;
		_windowInfo.height = 600;
	}
	MyApp::~MyApp() {
	}
	void MyApp::createEntities() {
		addEntity(new MyCamera("Camera"));
		addEntity(new MyTeapot("Teapot"));
		addEntity(new MyObject("Object"));
		addEntity(new MyWorld("World"));
	}
	void MyApp::createViews() {
		cg::View* v1 = createView("View1");
		v1->setViewport(0.0f,0.0f,0.5f,1.0f);
		v1->linkEntityAtEnd("Camera");
		v1->linkEntityAtEnd("Teapot");
		v1->linkEntityAtEnd("World");

		cg::View* v2 = createView("View2");
		v2->setViewport(0.5f,0.0f,0.5f,1.0f);
		v2->linkEntityAtEnd("Camera");
		v2->linkEntityAtEnd("Object");
		v2->linkEntityAtEnd("World");
	}
}