/** @file
 * @author Dirk Fortmeier
 * @date 19.11.2009
 */

#ifndef _YGE_PHYSICS_ASSET_H_
#define _YGE_PHYSICS_ASSET_H_

#include "YGEEntityAsset.h"

namespace YGEPhysics {
class YGEPhysicsAsset : public YGETimeSpace::YGEEntityAsset {
public:
	/**
	 * gets the position from the physics engine, interpolates
	 * and updates the parent entity
	 */
	virtual void update() = 0;
	
	virtual YGETimeSpace::AssetType getAssetType(){
		return YGETimeSpace::Physics;
	}
};

}


#include "YGEEntityAsset.h"


#endif