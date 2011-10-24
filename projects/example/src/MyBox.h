#ifndef BOX_H
#define BOX_H

#include "cg/cg.h"
#include "MyPhysics.h"
#include "MyFPSCamera.h"
#include "MaterialBank.h"

namespace example {
	class MyBox : public cg::Entity,
		public cg::IUpdateListener,
		public cg::IDrawListener,
		public cg::IMouseEventListener
	{
	private:
		int _modelDL;
		cg::Vector3d m_lastMousePosition;
		cg::Vector3d _lastposition;
		bool _movable, _isDebug;
		void makeModel();
		void MyBox::dividedPlane(int n, 
			double x0, double y0, double x1, double y1,
			double nx, double ny, double nz);
		

	public:
		
		MyPhysics _physics;

		MyBox(std::string id);
		~MyBox();

        void init();
        void update(unsigned long elapsed_millis);
		void onMousePassiveMotion(int x, int y);
        void draw();
		void togglemovable();
		void toggleDebugMode();
	};
}

#endif