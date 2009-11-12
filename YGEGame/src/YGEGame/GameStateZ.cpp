#include "GameStates.h"

GameStateZ::GameStateZ(){

	scene = new YGEEntity();

	YGEMath::Vector3 pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 10;

	camera = new YGEObserver();

	camera->setPosition(pos);

	ps = new YGEParticleSystem();
	scene->addAsset(ps);

	scene->addChild(camera);

}

YGESceneList GameStateZ::getScenesToRender(){
	YGEScene s;
	s.first = scene;
	s.second = camera;
	YGESceneList list;
	list.push_back(s);
	return list;
}

void GameStateZ::update() {
	ps->update();
	YGECore::YGELogger::getInstance()->log("Updating Gamestate Z");


}

void GameStateZ::draw(YGECore::YGEEngineCore* core) {
}

void GameStateZ::keyDown(SDLKey key){
	switch(key){
			case SDLK_UP:
				YGEMath::Vector3 pos = camera->getPosition();
				pos.z+=1;
				camera->setPosition(pos);
				break;
	}

}