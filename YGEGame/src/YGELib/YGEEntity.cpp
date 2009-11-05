#include <SDL_opengl.h>

#include "YGEEntity.h"


namespace YGETimeSpace{

	void YGEEntity::render(){

	YGEMath::Vector3 pos = this->getPosition();
	YGEMath::Vector3 scale = this->getScale();

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale.x, scale.y, scale.z);

	// get every graphical asset and render it
	std::list<YGEGraphics::YGEGraphicsAsset*> assets = this->getGraphicsAssets();
	for(std::list<YGEGraphics::YGEGraphicsAsset*>::iterator iter = assets.begin();
		iter != assets.end();
		iter++){

			

			(*iter)->draw(NULL);

	}

	// recursive call on all children
	std::list<YGEEntity*> children = this->getChildren();
	for(std::list<YGEEntity*>::iterator iter = children.begin();
		iter != children.end();
		iter++){
			(*iter)->render();

	}
	glPopMatrix();
};

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