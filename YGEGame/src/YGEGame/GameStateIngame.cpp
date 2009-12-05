#include "GameStateIngame.h"

#include "YGELogger.h"
#include "GameManager.h"

GameStateIngame::GameStateIngame() : timeSinceLastTimeUpdate(0) , gameStartTime(-1){


}


void GameStateIngame::init()  {
	// setting up the HUD
	hud = new GameHUD();

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

	s.first = hud->getSpace();
	s.second = hud->getObserver();

	sceneList.push_back(s);
	spaceList.push_back(hud->getSpace());

	gameStartTime = GameManager::getInstance()->getCore()->getTimeSinceGameStarted();

}




void GameStateIngame::deinit(){
	delete cam;
	delete gyro;
	delete level;
}

void GameStateIngame::update(long delta){
	if(gameStartTime == -1) init();

	timeSinceLastTimeUpdate += delta;
	if(timeSinceLastTimeUpdate > 1000000) {
		timeSinceLastTimeUpdate = 0;
		long long timePassed = GameManager::getInstance()->getCore()->getTimeSinceGameStarted() - gameStartTime;

		hud->setTime((int)(timePassed / 1000000));
	}
}


void GameStateIngame::keyDown(SDLKey key){

	switch(key){
			case SDLK_s:
				gyro->setThrottle(0.0f);
				break;
			case SDLK_w:
				gyro->setThrottle(100.0f);
				break;
			case SDLK_a:
				gyro->setTailX(-100.0f);
				break;
			case SDLK_d:
				gyro->setTailX(100.0f);
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
			case SDLK_SPACE:
				gyro->fireRocket();
				break;


	}
}


void GameStateIngame::keyUp(SDLKey key){

		switch(key){
			case SDLK_w:
				gyro->setThrottle(50.0f);
				break;
			case SDLK_s:
				gyro->setThrottle(50.0f);
				break;
				case SDLK_a:
				gyro->setTailX(0.0f);
				break;
							case SDLK_d:
				gyro->setTailX(0.0f);
				break;			case SDLK_LEFT:
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


void  GameStateIngame::processCommand(const char* command) {
	if(command == "stopgame") {
		GameManager::getInstance()->stopGame();
	}
}