#ifndef MATERIAL_H
#define MATERIAL_H

#include "cg/cg.h"

namespace example {
		
		class Material {
			private:
				
				float _ambient_R, _ambient_G, _ambient_B;
				float _diffuse_R, _diffuse_G, _diffuse_B;
				float _specular_R, _specular_G, _specular_B;
				float _shininess;

			
		
			public:

				Material();
				Material(float ambientR,float ambientG,float ambientB,
						float diffuseR, float diffuseG, float diffuseB,
						float specularR, float specularG, float specularB,
						float shine);
				~Material();
				void shade(GLenum face);
				void shade(GLenum face, float param);

			};


}


#endif