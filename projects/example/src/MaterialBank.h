#ifndef MATERIAL_BANK
#define MATERIAL_BANK

#include "cg/cg.h"

namespace example{

class MaterialBank
{
private:            

	static const GLfloat materialData[25][10];
	
public:
		

	enum materialType 
	{MATERIAL_EMERALD, 
	MATERIAL_JADE, 
	MATERIAL_OBSIDIAN,
	MATERIAL_PEARL,
	MATERIAL_RUBY,
	MATERIAL_TURQUOISE,
	MATERIAL_BRASS,
	MATERIAL_BRONZE,
	MATERIAL_CHROME,
	MATERIAL_COPPER,
	MATERIAL_SILVER,
	MATERIAL_GOLD,
	MATERIAL_PEWTER,
	MATERIAL_PLASTIC_BLACK,
	MATERIAL_PLASTIC_CYAN,
	MATERIAL_PLASTIC_GREEN,
	MATERIAL_PLASTIC_RED,
	MATERIAL_PLASTIC_WHITE,
	MATERIAL_PLASTIC_YELLOW,
	MATERIAL_RUBBER_BLACK,
	MATERIAL_RUBBER_CYAN,
	MATERIAL_RUBBER_GREEN,
	MATERIAL_RUBBER_RED,
	MATERIAL_RUBBER_WHITE,
	MATERIAL_RUBBER_YELLOW};

	enum materialParam
	{MATERIAL_AMBIENT_R,
	MATERIAL_AMBIENT_G,
	MATERIAL_AMBIENT_B,
	MATERIAL_DIFFUSE_R,
	MATERIAL_DIFFUSE_G,
	MATERIAL_DIFFUSE_B,
	MATERIAL_SPECULAR_R,
	MATERIAL_SPECULAR_G,
	MATERIAL_SPECULAR_B,
	MATERIAL_SHININESS};

	MaterialBank(void);
	~MaterialBank(void);

	static GLfloat getParam(materialType type, materialParam param);
	static GLfloat * getAmbientVec(materialType type);
	static GLfloat * getDiffuseVec(materialType type);
	static GLfloat * getSpecularVec(materialType type);
	static GLfloat * getAmbientVec(materialType type,GLfloat lastValue);
	static GLfloat * getDiffuseVec(materialType type,GLfloat lastValue);
	static GLfloat * getSpecularVec(materialType type,GLfloat lastValue);
	static GLfloat getShininess(materialType type);
};
}
#endif