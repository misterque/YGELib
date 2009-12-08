/**
 * @file
 * @author Dirk Fortmeier
 * @date 19.11.2009
 */

#ifndef _YGE_BOX_HULL_ASSET_H_
#define _YGE_BOX_HULL_ASSET_H_

#include "YGEPhysicsAsset.h"
#include "YGEVector.h"
class YGEBoxHullAsset : public YGEPhysicsAsset {
private:
	YGEMath::Vector3 dimension;
public:

	void setDimension(const YGEMath::Vector3 &dim);

};



#endif