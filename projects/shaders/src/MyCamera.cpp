#include "MyCamera.h"

namespace shaders {

	MyCamera::MyCamera(const std::string id) : Entity(id) {
	}
    MyCamera::~MyCamera() {
	}
    void MyCamera::init() {
		cg::tWindowInfo win = cg::Manager::instance()->getApp()->getWindowInfo();
		_winSize.set(win.width,win.height);
		_orientation.setRotationDeg(0,cg::Vector3d::ny);
		_up.set(0,1,0);
		_front.set(1,0,0);
		_right.set(0,0,1);
		_isRoll = false;
		_scale = 5.0f;
    }
    void MyCamera::draw() {
		_position = _front * _scale;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		gluPerspective(60,_winSize[0]/(double)( 2 *_winSize[1]),1.0,100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
		gluLookAt(_position[0],_position[1],_position[2],0,0,0,_up[0],_up[1],_up[2]);
    }
	void MyCamera::onReshape(int width, int height) {
		_winSize.set(width,height);
	}
#if !defined(GLUT_WHEEL_UP)
# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4
#endif
	void MyCamera::onMouse(int button, int state, int x, int y) {
		_isRoll = (button == GLUT_RIGHT_BUTTON);
		_lastMousePosition.set(x,y);

		if (state == GLUT_UP) {
			if ( button == GLUT_WHEEL_UP ) {
				_scale += 0.5f;
			} else if( button == GLUT_WHEEL_DOWN ) {
				if(_scale > 0.5f)
					_scale -= 0.5f;
			}
		}
	}
	void MyCamera::onMouseMotion(int x, int y) {
		if(_isRoll) {
			double anglez = (_lastMousePosition[0] - x) / (double)5;
				_q.setRotationDeg(anglez,_front);
				_up = apply(_q,_up);
				_right = apply(_q,_right);
				_orientation = _q * _orientation;
		} else {
			double anglex = (_lastMousePosition[0] - x) / (double)5;
				_q.setRotationDeg(anglex,_up);
				_front = apply(_q,_front);
				_right = apply(_q,_right);
				_orientation = _q * _orientation;
			double angley = (y - _lastMousePosition[1]) / (double)5;
				_q.setRotationDeg(angley, _right);
				_up = apply(_q,_up);
				_front = apply(_q,_front);
				_orientation = _q * _orientation;
		}
		_lastMousePosition.set(x,y);
	}
	void MyCamera::onMousePassiveMotion(int x, int y) {
	}
}
