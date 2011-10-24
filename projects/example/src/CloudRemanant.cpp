#include "CloudRemanant.h"


namespace example {

	CloudRemanant::CloudRemanant(std::string id) : cg::Entity(id)
	{
			this->state.disable();
	}


	CloudRemanant::~CloudRemanant(void)
	{
	}

		void CloudRemanant::init(){
			_shrinkVal = 1.0f;
		}
		void CloudRemanant::update(unsigned long elapsed_millis){
			_shrinkVal -=0.05f;
			std::cout << "Shrinkval: " <<_shrinkVal << std::endl;

			if(_shrinkVal <= 0.0f){
				cg::Registry::instance()->get("ResidualCloud")->state.disable();
				_shrinkVal = 1.0f;
			}
		}
		void CloudRemanant::draw(){

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialBank::getAmbientVec(MaterialBank::MATERIAL_PEARL));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialBank::getDiffuseVec(MaterialBank::MATERIAL_PEARL));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MaterialBank::getSpecularVec(MaterialBank::MATERIAL_PEARL));
	    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MaterialBank::getShininess(MaterialBank::MATERIAL_PEARL));

		glPushMatrix();
		glTranslated(_pos[0],_pos[1],_pos[2]);
		glScaled(_shrinkVal,0.6*_shrinkVal,0.7*_shrinkVal);
		glutSolidSphere(0.5,5,10);
		glPopMatrix();
	   }
		void CloudRemanant::setPos(cg::Vector3d pos){
			_pos=pos;
		}
}
