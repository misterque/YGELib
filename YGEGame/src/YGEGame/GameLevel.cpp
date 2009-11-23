#include "GameLevel.h"


void GameLevel::loadFromFile(const char* filename){
//@todo parse from file

	// create a space
	space = new YGETimeSpace::YGESpace();
	space->initTime();
	

	// create the heightmap
	heightmap = new YGEGraphics::YGEHeightmap();
	heightmap->create("images/hmap.bmp");
	space->getRootEntity()->addAsset(heightmap);

	heightmap->makeSolid();

}

YGEMath::Vector3 GameLevel::getPlayerStartPosition(){
	return YGEMath::Vector3(0, 60, 0);
}

void GameLevel::addEntity(YGETimeSpace::YGEEntity* entity){
	space->getRootEntity()->addChild(entity);

}