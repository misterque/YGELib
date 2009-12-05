#include "GameLevel.h"



void GameLevel::loadFromFile(const char* filename){
//@todo parse from file

	// create a space
	space = new YGETimeSpace::YGESpace();
	space->initTime();
	space->setSoundEnabled(true);

	// create the heightmap
	heightmap = new YGEGraphics::YGEHeightmap();
	heightmap->create("images/hmap.bmp"); 
	space->getRootEntity()->addAsset(heightmap);

	heightmap->makeSolid();

	//water = new YGEGraphics::YGEWater(heightmap, 10);
	//space->getRootEntity()->addAsset(water);

	skybox = new YGEGraphics::YGESkybox();
	skybox->loadTextures();
	space->setSkybox(skybox);

	GameBall* ball = new GameBall();
	space->getRootEntity()->addChild(ball);
	ball->setPosition(YGEMath::Vector3(172-128, 27, 154-128-60));

}

YGEMath::Vector3 GameLevel::getPlayerStartPosition(){
	return YGEMath::Vector3(172-128, 25, 154-128);
}

void GameLevel::addEntity(YGETimeSpace::YGEEntity* entity){
	space->getRootEntity()->addChild(entity);

}