/** @file
 * @author Dirk Fortmeier
 * @date 3.11.2009
 */

#ifndef _YGE_HEIGHTMAP_H_
#define _YGE_HEIGHTMAP_H_

#include "YGEGraphicsAsset.h"
#include "YGEVbo.h"

namespace YGEGraphics {

class YGEHeightmap : public YGEGraphicsAsset { // , YGEPhysicsAsset
private:
	YGEVbo* mesh;

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
};

}


#endif