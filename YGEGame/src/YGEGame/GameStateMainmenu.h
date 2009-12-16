/**
 * @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 */

#ifndef _GAME_STATE_MAINMENU_H_
#define _GAME_STATE_MAINMENU_H_

#include "YGEGameState.h"
#include "GameManager.h"

#include "YGESpace.h"
#include "YGEKeyDownListener.h"
#include "YGEKeyUpListener.h"
#include "YGEText.h"

#include "GameManager.h"

#include "GameGyrocopter.h"

#include "Camera.h"

#include "Menu.h"

class GameStateMainmenu  : public YGEGame::YGEGameState, public  YGEInput::YGEKeyDownListener{
private:
	GameGyrocopter* gyro;
	YGETimeSpace::YGEObserver* observer;
	YGETimeSpace::YGEObserver* observerText;

	YGETimeSpace::YGESpace* backgroundspace;
	YGETimeSpace::YGESpace* textspace;

	Menu* mainMenu;
	Menu* optionsMenu;
	Menu* levelMenu;

	Menu* activeMenu;

	YGETimeSpace::YGEEntity* optionsmenuEntity;

	YGEAudio::YGESoundAsset* menuSound;





public:
	GameStateMainmenu();
	
	void update(long delta);


	void keyDown(SDLKey key);

	virtual void processCommand(const char* command) ;

};



#endif
