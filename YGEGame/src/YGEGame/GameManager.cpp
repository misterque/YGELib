#include "GameManager.h"
#include "YGEEngineCoreSingleThreaded.h"

#include "GameStateIngame.h"
#include "GameStateSplashscreen.h"

#include <tchar.h>

GameManager* GameManager::instance = NULL;

GameManager::GameManager(){

}

void GameManager::startEngine(){


	engineCore->run();
}

void GameManager::initAndStartGame(){
	engineCore = new YGECore::YGEEngineCoreSingleThreaded();
		engineCore->init();

	ingame = new GameStateIngame();
	
	splashscreen = new GameStateSplashscreen();
	
	this->pushGameState(ingame);
	engineCore->getInputManager()->addKeyDownListener((GameStateIngame*)ingame);
	engineCore->getInputManager()->addKeyUpListener((GameStateIngame*)ingame);


	this->pushGameState(splashscreen);
	
	startEngine();
}
	
void GameManager::pushGameState(YGEGame::YGEGameState* gamestate){
	gameStateStack.push(gamestate);
	engineCore->setGameState(gamestate);

}

void GameManager::popGameState(){
	gameStateStack.pop();
	if(gameStateStack.empty()) {
		engineCore->setGameState(this);
	} else {
		engineCore->setGameState(gameStateStack.top());
	}

}

void GameManager::update(long delta){
	// if this point is reached, the gamestatestack is empty
	// and the game may exit
	engineCore->shutdown();

}




int _tmain(int argc, _TCHAR* argv[])
{

	GameManager::getInstance()->initAndStartGame();
	return 0;
}