#ifndef MY_PHYSICS_H
#define MY_PHYSICS_H

#include "cg/cg.h"

namespace lab4 {

	class MyPhysics {
	private:
		cg::Vector3d _position;
		cg::Vector3d _front, _up, _right;

		double _linearVelocity;
		double _angularVelocity;

		cg::Quaterniond _orientation;
		cg::Quaterniond _q;
		double _rotationMatrix[16];

		bool _isGoAhead, _isGoBack;
		bool _isYawLeft, _isYawRight;
		bool _isPitchUp, _isPitchDown;
		bool _isRollLeft, _isRollRight;
		void rotate(double elapsed_seconds,int direction, cg::Vector3d axis, cg::Vector3d& v1, cg::Vector3d& v2);

		double _axesScale;

	public:

		MyPhysics();
		~MyPhysics();

		void goAhead();
		void goBack();
		void yawLeft();
		void yawRight();
		void pitchUp();
		void pitchDown();
		void rollLeft();
		void rollRight();

		void setPosition(double x, double y, double z);
		void setLinearVelocity(double value);
		void setAngularVelocity(double value);

		void step(double elapsed_seconds);
		void applyTransforms();

		void setAxesScale(double scale);
		void drawAxes();
	};

}

#endif