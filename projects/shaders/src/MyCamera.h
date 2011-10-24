#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include "cg/cg.h"

namespace shaders {

    class MyCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener,
		public cg::IMouseEventListener
	{
    private:
		cg::Vector2d _winSize;
		cg::Vector3d _position;
		cg::Vector3d _up,_front,_right;
		cg::Quaterniond _orientation, _q;
		cg::Vector2d _lastMousePosition;
		float _scale;
		bool _isRoll;

    public:
        MyCamera(const std::string id);
        virtual ~MyCamera();
        void init();
        void draw();
        void onReshape(int width, int height);
        void onMouse(int button, int state, int x, int y);
        void onMouseMotion(int x, int y);
        void onMousePassiveMotion(int x, int y);
	};
}

#endif
