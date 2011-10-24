#ifndef CLOUD_H
#define CLOUD_H

#include "cg/cg.h"
#include "MyPhysics.h"
#include "MyCamera.h"
#include "MaterialBank.h"
#include "CloudRemanant.h"
namespace example {

	class Cloud : public cg::Entity,
			public cg::IUpdateListener,
			public cg::IDrawListener
	{
	private:
		cg::Vector3d _startPos;
	    bool _movable, _isDebug;
		float _shrinkVal,_timer;
		int _sign;
	public:
		MyPhysics _physics;

		Cloud(std::string id);
		~Cloud(void);
		void init();
	    void update(unsigned long elapsed_millis);
		void draw();
		void togglemovable();
		void shrink();
		void CreateRemanant();
		void timeRemanant();
		void toggleDebugMode();
	};
}

#endif