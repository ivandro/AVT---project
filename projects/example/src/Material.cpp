#include "Material.h"

namespace example{

				Material::Material() {
					_ambient_R=0.0f; 
					_ambient_G=0.0f;
					_ambient_B=0.0f;
					_diffuse_R=0.0f;
					_diffuse_G=0.0f;
					_diffuse_B=0.0f;
					_specular_R=0.0f;
					_specular_G=0.0f;
					_specular_B=0.0f;
					_shininess=0.0f;
				}

				Material::Material(float ambientR,float ambientG,float ambientB,
						float diffuseR, float diffuseG, float diffuseB,
						float specularR, float specularG, float specularB,
						float shine){
					_ambient_R = ambientR;
					_ambient_G = ambientG;
					_ambient_B = ambientB;
					_diffuse_R = diffuseR;
					_diffuse_G = diffuseG;
					_diffuse_B = diffuseB;
					_specular_R = specularR;
					_specular_G = specularG;
					_specular_B = specularB;
					_shininess = shine;

				}
				Material::~Material(){}

				void Material::shade(GLenum face){
					float mat[4] = {_ambient_R, _ambient_G, _ambient_B, 1.0f};
					glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
					
					mat[0] = _diffuse_R;
					mat[1] = _diffuse_G;
					mat[2] = _diffuse_B;
					glMaterialfv(face, GL_DIFFUSE, mat);
					
					mat[0] = _specular_R;
					mat[1] = _specular_G;
					mat[2] = _specular_B;
					glMaterialfv(face, GL_SPECULAR, mat);

					glMaterialf(face, GL_SHININESS, _shininess);
				}

				void Material::shade(GLenum face,float param){
					float mat[4] = {_ambient_R, _ambient_G, _ambient_B, param};
					glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
					
					mat[0] = _diffuse_R;
					mat[1] = _diffuse_G;
					mat[2] = _diffuse_B;
					mat[3] = param;
					glMaterialfv(face, GL_DIFFUSE, mat);
					
					mat[0] = _specular_R;
					mat[1] = _specular_G;
					mat[2] = _specular_B;
					mat[3] = param;
					glMaterialfv(face, GL_SPECULAR, mat);

					glMaterialf(face, GL_SHININESS, _shininess);
				}


}