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

class YGEEntityAsset {

public:
	virtual AssetType getAssetType(){
		return Standard;
	}

};



}
#endif