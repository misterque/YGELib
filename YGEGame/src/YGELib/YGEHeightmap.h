/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_HEIGHTMAP_H_
#define _YGE_HEIGHTMAP_H_

#include "YGEGraphicsAsset.h"
#include "YGEVbo.h"
#include "YGERessourceManager.h"

namespace YGEGraphics {

class YGEHeightmap : public YGEGraphicsAsset { // , YGEPhysicsAsset
private:
	YGEVbo* mesh;

	YGECore::Texture* texture;

	int w;
	int h;

	dHeightfieldDataID heightfieldId;
	double* pHeightData;
public:

	/**
	 * draw method to render visual representation
	 * of the heightmap
	 */
	virtual void draw(YGEGraphicsContext* context);

	/** 
	 * creates a heightmap using a monocromatic texture.
	 */
	void create(char *filename);

	void makeSolid();

	int getW() {
		return w;
	}
	int getH() {
		return h;
	}

	double getZ(int x, int y);

};

}


#endif