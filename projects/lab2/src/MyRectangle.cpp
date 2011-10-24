#include "MyRectangle.h"

namespace lab2 {

	MyRectangle::MyRectangle(std::string id) : cg::Entity(id) {
	}
	MyRectangle::~MyRectangle() {
	}
	void MyRectangle::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_position.set(win.width/2.0f, win.height/2.0f);
		_direction.set(1.0, 0.0);
		_velocity = 0.0;
		_acceleration = 100.0;
		_angle = 0.0;
		_angularVelocity = 100.0;
	}
	void MyRectangle::update(unsigned long elapsed_millis) {
		double elapsed_seconds = elapsed_millis / (double)1000;
		if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_DOWN)) {
			_velocity -= _acceleration * elapsed_seconds;
		}
		if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_UP)) {
			_velocity += _acceleration * elapsed_seconds;
		}
		if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_RIGHT)) {
			double delta = -_angularVelocity * elapsed_seconds;
			if(_velocity < 0 ) {
				delta *= -1;
			}
			_direction = rotateDeg(_direction, delta);
			_angle += delta;
		}
		if(cg::KeyBuffer::instance()->isSpecialKeyDown(GLUT_KEY_LEFT)) {
			double delta = _angularVelocity * elapsed_seconds;
			if(_velocity < 0 ) {
				delta *= -1;
			}
			_direction = rotateDeg(_direction, delta);
			_angle += delta;
		}
		_position += _direction * _velocity * elapsed_seconds;
	}
	void MyRectangle::draw() {
        glPushMatrix();
        glTranslated(_position[0],_position[1],0);
        glRotated(_angle,0,0,1);
        glColor3f(0.8f,0.8f,0.2f);
		glRectf(-20.0f,-10.0f,15.0f,10.0f);
        glColor3f(0.5f,0.5f,0.2f);
		glRectf(15.0f,-10.0f,20.0f,10.0f);
        glPopMatrix();
	}

}