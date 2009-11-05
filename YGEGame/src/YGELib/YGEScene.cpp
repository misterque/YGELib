/*#include <SDL_opengl.h>
#include "YGEScene.h"

namespace YGETimeSpace{
void YGEScene::render(){
	renderEntity(&rootNode);

};


void YGEScene::renderEntity(YGEEntity* entity){

	YGEMath::Vector3 pos = entity->getPosition();
	YGEMath::Vector3 scale = entity->getScale();

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale.x, scale.y, scale.z);

	// get every graphical asset and render it
	std::list<YGEGraphics::YGEGraphicsAsset*> assets = entity->getGraphicsAssets();
	for(std::list<YGEGraphics::YGEGraphicsAsset*>::iterator iter = assets.begin();
		iter != assets.end();
		iter++){

			

			(*iter)->draw(NULL);

	}

	// recursive call on all children
	std::list<YGEEntity*> children = entity->getChildren();
	for(std::list<YGEEntity*>::iterator iter = children.begin();
		iter != children.end();
		iter++){
			renderEntity(*iter);

	}
	glPopMatrix();
};

YGEScene::YGEScene(){
	//rootNode.p
}

}*/