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

	water = new YGEGraphics::YGEWater();
	space->getRootEntity()->addAsset(water);

}

YGEMath::Vector3 GameLevel::getPlayerStartPosition(){
	return YGEMath::Vector3(172-128, 40, 154-128);
}

void GameLevel::addEntity(YGETimeSpace::YGEEntity* entity){
	space->getRootEntity()->addChild(entity);

}