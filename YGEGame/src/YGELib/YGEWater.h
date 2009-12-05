/**
 * @file
 * @author Dirk Fortmeier
 * @date 24.11.2009
 */

#ifndef _YGE_WATER_H_
#define _YGE_WATER_H_

#include "YGEGraphicsAsset.h"
#include "YGERessourceManager.h"
#include "YGEHeightmap.h"

namespace YGEGraphics {


class YGEWater : public YGEGraphicsAsset {
private:
	YGEVbo* mesh;
	Mesh* map;
	YGECore::YGETexture *texture;

	bool allLessThan(YGEHeightmap* hmap, int x, int y, int w, int h, double waterheight);
	bool buildMeshRecursive(YGEHeightmap* hmap, int x, int y, int w, int h, double waterheight);

public:

	YGEWater(YGEHeightmap* hmap, double h);

	virtual void draw(YGEGraphicsContext* context);
};

}
#endif