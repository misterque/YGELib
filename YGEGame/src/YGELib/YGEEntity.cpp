#include "YGEEntity.h"


namespace YGETimeSpace{
	void YGEEntity::addChild( YGEEntity* entity ){

		//@todo check for double insertion
		
		entity->parent = this;
		children.push_back(entity);

	}

	void YGEEntity::addAsset( YGEEntityAsset* asset ){

		//@todo check for double insertion

		assets.push_back(asset);

		// if it is a graphical asset put it in the list of graphicals
		if(asset->getAssetType() == Graphical) {
			graphicAssets.push_back((YGEGraphics::YGEGraphicsAsset*)asset);
		}

	}


	YGEEntity::YGEEntity(){
		scale.x = 1 ;
		scale.y = 1;
		scale.z = 1;

		assets.clear();
		children.clear();
		parent = NULL;

	}

}