#include "YGEScene.h"

void YGEScene::render(){
	renderEntity(&rootNode);

};


void YGEScene::renderEntity(YGEEntity* entity){

	for(std::list<YGEEntityAsset*>::iterator iter = entity->getAssets().begin();
		iter != entity->getAssets().end();
		iter++){
		//	if(	dynamic_cast<YGEGraphicsAsset*> (*iter) != NULL ) {
		//		printf("found a ga \n");
		//		(*iter)->draw();
		//	}
	}

	for(std::list<YGEEntity*>::iterator iter = entity->getChildren().begin();
		iter != entity->getChildren().end();
		iter++){
			renderEntity(*iter);

	}
};
