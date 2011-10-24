#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include "cg/cg.h"

namespace lab4 {

    class MyFrontCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		double _winWidth, _winHeight;
		cg::Vector3d _position;

    public:
        MyFrontCamera();
        virtual ~MyFrontCamera();
        void init();
        void draw();
        void onReshape(int width, int height);

	};
}

#endif
