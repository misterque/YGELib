#include "GameStateMainmenu.h"
#include <string>

GameStateMainmenu::GameStateMainmenu(){
	gyro = new GameGyrocopter();

	observer = new YGETimeSpace::YGEObserver();
	observerText = new YGETimeSpace::YGEObserver();
	observerText->setCameraMode(CAMERA_ORTHOGONAL);

	backgroundspace = new YGETimeSpace::YGESpace();
	textspace = new YGETimeSpace::YGESpace();

	backgroundspace->getRootEntity()->addChild(observer);
	backgroundspace->getRootEntity()->addChild(gyro);

	observer->translate3d(0, 6, 20);
	observer->rotateDGR(YGEMath::Vector3(1,0,0), -5);


	optionsMenu = new Menu();
	optionsMenu->addItem("< Change Sound Volume >", "changevolume");
	optionsMenu->addItem("Toggle Fullscreen", "togglefullscreen");
	optionsMenu->addItem("Back", "back");

	levelMenu = new Menu();

	std::vector<std::string>* levels = GameManager::getInstance()->getLevelList();
	int i = 0;
	for(std::vector<std::string>::iterator iter = levels->begin(); iter != levels->end(); iter++){
		if(i < GameManager::getInstance()->getReachedLevel()) {
			std::stringstream s;
			s<<"start "<<(*iter);
			levelMenu->addItem((*iter), s.str());
		}
		i++;

	}

	mainMenu = new Menu();

	activeMenu = mainMenu;
	mainMenu->pos->translate3d(300, 200, 0);
	mainMenu->addSubmenu("Start Game" , levelMenu);
	mainMenu->addSubmenu("Options", optionsMenu);
	mainMenu->addItem("Exit", "quit");

	textspace->getRootEntity()->addChild(mainMenu->pos);


	// setting up the render and update lists
	YGETimeSpace::YGEScene s;
	s.first = backgroundspace;
	s.second = observer;

	sceneList.push_back(s);

	s.first = textspace;
	s.second = observerText;

	sceneList.push_back(s);

}

void GameStateMainmenu::update(long delta){
	double seconds = delta / 1000000.0f;

	gyro->rotateDGR(YGEMath::Vector3(0,1,0), seconds * 30.0f);

}
void GameStateMainmenu::keyDown(SDLKey key){

	switch(key){
			case SDLK_DOWN:
				activeMenu->down();
				break;
			case SDLK_UP:
				activeMenu->up();
				break;
			case SDLK_LEFT:
				activeMenu->left();
				break;
			case SDLK_RIGHT:
				activeMenu->right();
				break;

			case SDLK_SPACE:
			case SDLK_RETURN:
				Menu* m = activeMenu->select();
				if(m != NULL) {
					activeMenu = m;
				}
				break;
	}
}

void  GameStateMainmenu::processCommand(const char* command) {
	int i = 0;
	std::vector<std::string>* levels = GameManager::getInstance()->getLevelList();

	for(std::vector<std::string>::iterator iter = levels->begin(); iter != levels->end(); iter++){
		std::stringstream s;
		s<<"start "<<(*iter);

		if(std::string(command) == s.str()) {
			std::stringstream ss;
			ss<<"level/"<<levels->at(i);
			GameManager::getInstance()->startGame(ss.str());

			break;
		}
	i++;

	}


};