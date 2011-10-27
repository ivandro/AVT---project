#ifndef MATERIAL_BANK
#define MATERIAL_BANK

#include "cg/cg.h"
#include "Material.h"

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

	MaterialBank(void);
	~MaterialBank(void);

	static Material getMaterial(materialType type);
};

}
#endif