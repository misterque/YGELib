#include "GameStateIngame.h"

#include "YGELogger.h"
#include "GameManager.h"

GameStateIngame::GameStateIngame() : timeSinceLastTimeUpdate(0) , gameStartTime(-1), ingameTime(0){


}


void GameStateIngame::init()  {
	timeSinceLastTimeUpdate= 0;
	gameStartTime = -1;
	ingameTime = 0;

	// setting up the HUD
	hud = new GameHUD();

	// setting up the level
	level = new GameLevel();

	// @todo create level from file
	level->createFromFile(levelFileName.c_str());

	ballsToDestroy = level->getNumberOfBalls();


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

	hasBeenInitialised = true;

	timeToQuit=999999999;

	levelCompleted = false;



	quitMenuIsShow = false;
}




void GameStateIngame::deinit(){
	hasBeenInitialised = false;
	level->getSpace()->getRootEntity()->disable();
	sceneList.clear();
	spaceList.clear();
}

void GameStateIngame::update(long delta){
	/*if(gameStartTime == -1) {
	init();
	return;
	}*/

	int timeLeft = level->getTimeToComplete() - (ingameTime / 1000000);
	timeSinceLastTimeUpdate += delta;

	if( level->getSpace()->getTimeIsRunning() ) {
		ingameTime += delta;
	} 
	if(timeSinceLastTimeUpdate > 1000000) {
		timeSinceLastTimeUpdate = 0;
		//long long timePassed = GameManager::getInstance()->getCore()->getTimeSinceGameStarted() - gameStartTime;

		hud->setTime(timeLeft);
		hud->setFramesPerSecond(GameManager::getInstance()->getCore()->getFramesPerSecond());

	}



	if(ballsToDestroy > 0 && timeLeft < 0) {
		hud->setInfoText("timeout!!!");
		timeToQuit = 3.0f;
		ballsToDestroy = -1;
	}
	if(ballsToDestroy == 0) {


		hud->setInfoText("all balls destroyed!!!");
		timeToQuit = 3.0f;
		ballsToDestroy--;

		levelCompleted = true;



	}
	if(ballsToDestroy == -1) {
		timeToQuit -= delta / 1000000.0f;
	}
	if(ballsToDestroy == -2) {
		hud->setInfoText("collision!!!");
		timeToQuit = 3.0f;
		ballsToDestroy = -1;
		level->addEntity(cam);
		cam->setPosition(cam->getAbsPosition());
		cam->setOrientation(cam->getAbsOrientation());
	}

	if(timeToQuit < 0) {
		GameManager::getInstance()->getCore()->processCommand("stopgame");
	}
}


void GameStateIngame::keyDown(SDLKey key){

	if(	key == SDLK_ESCAPE) {
		if(!quitMenuIsShow) {
			level->getSpace()->stopTime();
			hud->showQuitMenu(true);
			quitMenuIsShow = true;
		} else {
			level->getSpace()->startTime();
			hud->showQuitMenu(false);
			quitMenuIsShow = false;
		}
	}

	if(quitMenuIsShow) {
		hud->keyDown(key);
	} else {

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
			case SDLK_EQUALS:
			case SDLK_PLUS:
				GameManager::getInstance()->getCore()->processCommand("volumeUp");
				break;
			case SDLK_MINUS:
				GameManager::getInstance()->getCore()->processCommand("volumeDown");
				break;

			case SDLK_p:
				if(level->getSpace()->getTimeIsRunning()) {
					level->getSpace()->stopTime();
					hud->setInfoText("PAUSE - press 'p' to continue");
				} else {
					level->getSpace()->startTime();
					hud->setInfoText("");
				}
				break;




		}
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
	if(command == "balldestroyed") {
		ballsToDestroy--;
	}

	if(command == "collision" && ballsToDestroy >= 0) {
		ballsToDestroy = -2;

	}

}

void GameStateIngame::setLevel(int level){

}

bool GameStateIngame::getLevelCompleted(){
	return levelCompleted;
}