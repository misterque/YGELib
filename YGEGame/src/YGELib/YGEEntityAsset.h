/** @file
 * @author Dirk Fortmeier
 */


#ifndef _YGE_ENTITY_ASSET_H_
#define _YGE_ENTITY_ASSET_H_

#include "YGEGraphicsContext.h"

namespace YGETimeSpace{
enum AssetType { 
		Standard,
		Graphical,
		Sound,
		Physics,
		ETC
	};

class YGEEntity;

class YGEEntityAsset {
protected:
	YGEEntity *parent;

public:
	virtual AssetType getAssetType(){
		return Standard;
	}

	virtual void setParent(YGEEntity* entity){
		parent = entity;
	}

	

	YGEEntity* getParent(){
		return parent;
	}

	virtual void enable() = 0;

	virtual void disable() = 0;

};



}
#endif