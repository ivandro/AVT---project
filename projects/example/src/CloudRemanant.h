#ifndef CLOUD_REMANANT_H
#define CLOUD_REMANANT_H

#include "cg/cg.h"
#include "MaterialBank.h"

namespace example {
	class CloudRemanant : public cg::Entity,
				public cg::IUpdateListener,
				public cg::IDrawListener
	{
		private:
			float _shrinkVal;
			cg::Vector3d _pos;

		public:
			CloudRemanant(std::string id);
			~CloudRemanant(void);
			void init();
			void update(unsigned long elapsed_millis);
			void draw();
			void setPos(cg::Vector3d pos);
	};
}
#endif