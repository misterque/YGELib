#include "GameManager.h"
#include "YGEEngineCoreSingleThreaded.h"
#include "YGEEngineCoreMultiThreaded.h"
#include "GameStateIngame.h"
#include "GameStateSplashscreen.h"
#include "GameStateMainmenu.h"

#include <tchar.h>

#include <istream>
#include <sstream>


GameManager* GameManager::instance = NULL;

GameManager::GameManager(){

}

void GameManager::loadSaveGame(){
	std::ifstream is;
	is.open("highscore");
	if(!is.is_open()) {
		
		std::ofstream os;
		os.open("highscore");
		os<<1<<std::endl;
		os.close();
		reachedLevel = 1;
		return;
	} else {
 
	while(!is.eof()){
		std::string line;
		getline(is, line);
		std::istringstream istr(line);

		istr >> reachedLevel;
	}

	}
}

void GameManager::loadLevelList(){

	std::ifstream is;
	is.open(YGECore::YGERessourceManager::getInstance()->absoluteFilename("level/levels.txt").c_str());
	if(!is.is_open()) {
		throw YGEExceptionFileNotFound("level/levels.txt");
	}

	while(!is.eof()){
		std::string line, type;
		getline(is, line);
		std::istringstream istr(line);

		std::string file;

		istr >> file;
		if(file != "") {
			levelFiles.push_back(file);
		}
	}
}

void GameManager::startEngine(){


		engineCore->run();
}

void GameManager::startGame(std::string filename){
	((GameStateIngame*)ingame)->setLevelFileName(filename);
	this->pushGameState(ingame);

	if(filename == this->getLevelList()->at(reachedLevel-1) &&
		reachedLevel != this->getLevelList()->size()){
		latest = true;
	} else {
		latest = false;
	}

}

void GameManager::stopGame(){
	this->popGameState();
	
	if( ((GameStateIngame*)ingame)->getLevelCompleted() &&
		latest) {
			reachedLevel++;
	}
	((GameStateIngame*)ingame)->deinit();
}

void GameManager::initAndStartGame(){
	engineCore = new YGECore::YGEEngineCoreSingleThreaded();
		engineCore->init();

	loadSaveGame();
	loadLevelList();
	

	ingame = new GameStateIngame();

	mainmenu = new GameStateMainmenu();
	
	splashscreen = new GameStateSplashscreen();

	this->pushGameState(mainmenu);

	this->pushGameState(splashscreen);

	engineCore->getInputManager()->addKeyDownListener(this);
	engineCore->getInputManager()->addKeyUpListener(this);


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




void GameManager::keyUp(SDLKey key){
	// pass pressed key to the gamestate if is a keylistener

	if(dynamic_cast<YGEKeyUpListener*>( gameStateStack.top()) != NULL ) {
		(dynamic_cast<YGEKeyUpListener*>(gameStateStack.top()))->keyUp(key);
	}
}

void GameManager::keyDown(SDLKey key){
	switch(key){
		case SDLK_F2:
			getCore()->processCommand("togglefullscreen");
			break;
	}

	// pass pressed key to the gamestate if is a keylistener

	if(dynamic_cast<YGEKeyDownListener*>( gameStateStack.top()) != NULL ) {
		dynamic_cast<YGEKeyDownListener*>(gameStateStack.top())->keyDown(key);
	}

}


int _tmain(int argc, _TCHAR* argv[])
{

	GameManager::getInstance()->initAndStartGame();
	return 0;
}