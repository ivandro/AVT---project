#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <string>
#include "cg/cg.h"

namespace lab2 {

    class MyTopCamera : public cg::Entity, 
		public cg::IDrawListener,
		public cg::IReshapeEventListener
	{
    private:
		double _winWidth, _winHeight;

    public:
		MyTopCamera(const std::string& id);
        virtual ~MyTopCamera();
        void init();
        void draw();
        void onReshape(int width, int height);
	};
}

#endif
