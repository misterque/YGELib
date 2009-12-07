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

	bool enabled;

public:
	virtual AssetType getAssetType(){
		return Standard;
	}

	virtual void setParent(YGEEntity* entity){
		parent = entity;
	}

	
	YGEEntityAsset();

	YGEEntity* getParent(){
		return parent;
	}

	virtual void enable(){
		enabled = true;
	}

	virtual void disable(){
		enabled = false;
	}
	virtual void tick(long delta) {};

};



}
#endif