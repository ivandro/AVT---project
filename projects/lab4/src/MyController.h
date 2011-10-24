#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include "cg/cg.h"
#include "MyTeapot.h"

namespace lab4 {

	class MyController : public cg::Entity,
		public cg::IKeyboardEventListener,
		public cg::IDrawListener
	{
	public:
		MyController();
		~MyController();
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyPressed(int key);
        void onSpecialKeyReleased(int key);
		void drawOverlay();
	};
}

#endif