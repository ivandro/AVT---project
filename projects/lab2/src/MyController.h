#ifndef MY_CONTROLLER_H
#define MY_CONTROLLER_H

#include "cg/cg.h"
#include "MyRectangle.h"

namespace lab2 {

	class MyController : public cg::Entity,
		public cg::IKeyboardEventListener
	{
	public:
		MyController(const std::string& id);
		~MyController();
		void init();
        void onKeyPressed(unsigned char key);
        void onKeyReleased(unsigned char key);
        void onSpecialKeyReleased(int key);
	};
}

#endif