#include "GameStateIngame.h"

#include "YGELogger.h"

GameStateIngame::GameStateIngame(){
	
	
}


void GameStateIngame::init(){

	// setting up the level
	level = new GameLevel();
	level->loadFromFile("");


	// setting up the gyrocopter
	gyro = new GameGyrocopter();
	level->addEntity(gyro);
	gyro->setPosition(level->getPlayerStartPosition());

	// setting up the camera
	cam = new Camera();

	gyro->addChild(cam);


	// setting up the render and update lists
	YGETimeSpace::YGEScene s;
	s.first = level->getSpace();
	s.second = cam->getObserver();
	
	sceneList.push_back(s);

	spaceList.push_back(level->getSpace());




}




void GameStateIngame::deinit(){
	delete cam;
	delete gyro;
	delete level;
}

void GameStateIngame::update(){


}


void GameStateIngame::keyDown(SDLKey key){


}
	