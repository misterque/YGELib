/**
 * @file
 * @author Dirk Fortmeier
 * @date 24.11.2009
 */

#ifndef _YGE_WATER_H_
#define _YGE_WATER_H_

#include "YGEGraphicsAsset.h"
#include "YGERessourceManager.h"
namespace YGEGraphics {


class YGEWater : public YGEGraphicsAsset {
private:
	YGECore::Texture *texture;

public:

	YGEWater();

	virtual void draw(YGEGraphicsContext* context);
};

}
#endif