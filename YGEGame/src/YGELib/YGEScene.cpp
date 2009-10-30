#include "YGEScene.h"

void YGEScene::render(){
	renderEntity(&rootNode);

};


void YGEScene::renderEntity(YGEEntity* entity){

	// get every graphical asset and render it
	std::list<YGEGraphicsAsset*> assets = entity->getGraphicsAssets();
	for(std::list<YGEGraphicsAsset*>::iterator iter = assets.begin();
		iter != assets.end();
		iter++){

			(*iter)->draw();

	}

	// recursive call on all children
	std::list<YGEEntity*> children = entity->getChildren();
	for(std::list<YGEEntity*>::iterator iter = children.begin();
		iter != children.end();
		iter++){
			renderEntity(*iter);

	}
};

YGEScene::YGEScene(){
	//rootNode.p
}