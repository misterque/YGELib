#include "GameStates.h"

GameStateY::GameStateY(){

	pitch = 0;
	yaw = 0;
	
	scene = new YGEEntity();

	YGEMath::Vector3 pos;
	pos.x = 20;
	pos.y = 20;
	pos.z = 140;


	camera = new YGEObserver();

	camera->setPosition(pos);

	YGEHeightmap* heightmap = new YGEHeightmap();
	heightmap->create("heightmaps/simple.bmp");

	scene->addAsset(heightmap);

	scene->addChild(camera);

}

YGESceneList GameStateY::getScenesToRender(){
	YGEScene s;
	s.first = scene;
	s.second = camera;
	YGESceneList list;
	list.push_back(s);
	return list;
}

void GameStateY::update() {
	YGECore::YGELogger::getInstance()->log("Updating Gamestate Y");

	YGEMath::Quaternion q;
	q.w = cos(yaw);
	q.x = 0;
	q.y = sin(yaw);
	q.z = 0;

	//YGEMath::Quaternion p = smallBoxPos->getOrientation();

	camera->setOrientation(q);

}

void GameStateY::draw(YGECore::YGEEngineCore* core) {
}

void GameStateY::keyDown(SDLKey key){
	switch(key){
			case SDLK_LEFT:
				yaw += 0.1;
				break;
			case SDLK_RIGHT:
				yaw -= 0.1;
				break;

			case SDLK_UP:
				YGEMath::Vector3 pos = camera->getPosition();
				pos.z+=1;
				camera->setPosition(pos);
				break;
	}

}

void GameStateY::mouseMoved(int x, int y){
	yaw += x / 100.0f;
}