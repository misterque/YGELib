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
	cam->translate3d(0, 6, 0);

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

	switch(key){
			case SDLK_a:
				gyro->setThrottle(0.0f);
				break;
			case SDLK_q:
				gyro->setThrottle(100.0f);
				break;
			case SDLK_LEFT:
				gyro->setTailV(-100.0f);
				break;
			case SDLK_RIGHT:
				gyro->setTailV(100.0f);
				break;
			case SDLK_UP:
				gyro->setTailH(100.0f);
				break;
			case SDLK_DOWN:
				gyro->setTailH(-100.0f);
				break;


	}
}


void GameStateIngame::keyUp(SDLKey key){

		switch(key){
			case SDLK_a:
				gyro->setThrottle(50.0f);
				break;
			case SDLK_q:
				gyro->setThrottle(50.0f);
				break;
			case SDLK_LEFT:
				gyro->setTailV(0.0f);
				break;
			case SDLK_RIGHT:
				gyro->setTailV(0.0f);
				break;
			case SDLK_UP:
				gyro->setTailH(0.0f);
				break;
			case SDLK_DOWN:
				gyro->setTailH(0.0f);
				break;


	}

}
