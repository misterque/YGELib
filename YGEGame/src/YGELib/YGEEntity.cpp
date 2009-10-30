#include "YGEEntity.h"

void YGEEntity::addChild( YGEEntity* entity ){

	//@todo check for double insertion

	children.push_back(entity);

}

void YGEEntity::addAsset( YGEEntityAsset* asset ){

	//@todo check for double insertion

	assets.push_back(asset);

}