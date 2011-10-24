#include "MyTeapot.h"

namespace lab4 {

	MyTeapot::MyTeapot(std::string id) : cg::Entity(id) {
	}
	MyTeapot::~MyTeapot() {
	}
	void MyTeapot::makeModel() {
		_modelDL = glGenLists(1);
		assert(_modelDL != 0);
		glNewList(_modelDL,GL_COMPILE);
			glColor3f(0.7f,0.7f,0.3f);
			glutWireTeapot(1.0);
		glEndList();
	}
	void MyTeapot::init() {
		_physics.setPosition(0,0.5,0);
		_physics.setLinearVelocity(5.0);
		_physics.setAngularVelocity(100.0);
		_physics.setAxesScale(3.0);
		makeModel();
		_debugMode = false;
	}
	void MyTeapot::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / (double)1000;
		if(cg::KeyBuffer::instance()->isKeyDown('w')) {
			_physics.goAhead();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('s')) {
			_physics.goBack();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('a')) {
			_physics.yawLeft();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('d')) {
			_physics.yawRight();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('z')) {
			_physics.pitchUp();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('q')) {
			_physics.pitchDown();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('x')) {
			_physics.rollLeft();
		}
		if(cg::KeyBuffer::instance()->isKeyDown('c')) {
			_physics.rollRight();
		}
		_physics.step(elapsed_seconds);
	}
	void MyTeapot::draw() {
		if(_debugMode) {
			_physics.drawAxes();
		}
        glPushMatrix();
			_physics.applyTransforms();
			glCallList(_modelDL);
		glPopMatrix();
	}
	void MyTeapot::toggleDebugMode() {
		_debugMode = !_debugMode;
	}
}