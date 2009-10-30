#include "YGEEntity.h"

void YGEEntity::addChild( YGEEntity* entity ){

	//@todo check for double insertion

	children.push_back(entity);

}

void YGEEntity::addAsset( YGEEntityAsset* asset ){

	//@todo check for double insertion

	assets.push_back(asset);

	// if it is a graphical asset put it in the list of graphicals
	if(asset->getAssetType() == Graphical) {
		graphicAssets.push_back((YGEGraphicsAsset*)asset);
	}

}


YGEEntity::YGEEntity(){
	assets.clear();
	children.clear();
	parent = NULL;

}