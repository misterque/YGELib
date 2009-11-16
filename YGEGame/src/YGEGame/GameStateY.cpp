#include "GameStates.h"

GameStateY::GameStateY(){

	
	scene = new YGEEntity();

	YGEMath::Vector3 pos;
	pos.x = 20;
	pos.y = 20;
	pos.z = 140;


	camera = new Camera();

	camera->setPosition(pos);

	YGEHeightmap* heightmap = new YGEHeightmap();
	heightmap->create("images/hmap2.bmp");

	scene->addAsset(heightmap);

	scene->addChild(camera);

}

YGESceneList GameStateY::getScenesToRender(){
	YGEScene s;
	s.first = scene;
	s.second = camera->getObserver();
	YGESceneList list;
	list.push_back(s);
	return list;
}

void GameStateY::update() {
	YGECore::YGELogger::getInstance()->log("Updating Gamestate Y");
}

void GameStateY::draw(YGECore::YGEEngineCore* core) {
}

void GameStateY::keyDown(SDLKey key){
	switch(key){

			case SDLK_UP:
				YGEMath::Vector3 pos = camera->getPosition();
				pos.z+=1;
				camera->setPosition(pos);
				break;
	}

}

void GameStateY::mouseMoved(int x, int y){
	camera->rotate(x / 100.0f, y / 100.0f);
}