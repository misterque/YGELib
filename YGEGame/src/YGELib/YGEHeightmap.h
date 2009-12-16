/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_HEIGHTMAP_H_
#define _YGE_HEIGHTMAP_H_

#include "YGEGraphicsAsset.h"
#include "YGEVbo.h"
#include "YGEResourceManager.h"

#include "YGEVector.h"

namespace YGEGraphics {


/**
 * @brief heightmap class for terrain rendering and collsion
 */
class YGEHeightmap : public YGEGraphicsAsset { 
private:
	YGEVbo* mesh;

	YGECore::YGETexture* texture;

	int w;
	int h;

	double scalex;
	double scalez;
	double scaley;

	dHeightfieldDataID heightfieldId;
	double* pHeightData;

	YGEMath::Vector3 corners[4];
public:

	YGEHeightmap();
	~YGEHeightmap();


	/**
	 * draw method to render visual representation
	 * of the heightmap
	 */
	virtual void draw(YGEGraphicsContext* context);

	/** 
	 a* creates a heightmap using a monocromatic texture.
	 
	 */
	void create(const char *filename, const char* texturefilename, double width, double depth, double height);


	/**
	 * @brief make the heightmap solid
	 *
	 * i.e. create a static geom for the physics engine
	 * @note heightmap must be child of a YGETimeSpace::YGESpace
	 * and this space must have time enabled
	 */
	void makeSolid();

	/**
	 * @brief get the width of the heightmap
	 */

	int getW() {
		return w;
	}
	/**
	 * @brief get the height/depth of the heightmap
	 */
	int getH() {
		return h;
	}

	/**
	 * @brief get the height of the heightmap at position x, y
	 */
	double getZ(int x, int y);

};

}


#endif