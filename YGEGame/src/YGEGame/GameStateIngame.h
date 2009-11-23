/**
 * @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 */

#ifndef _GAME_STATE_INGAME_H_
#define _GAME_STATE_INGAME_H_

#include "YGEGameState.h"
#include "YGESpace.h"
#include "YGEKeyDownListener.h"
#include "GameManager.h"

#include "GameGyrocopter.h"
#include "GameLevel.h"

#include "Camera.h"

class GameStateIngame  : public YGEGame::YGEGameState, public YGEKeyDownListener{
private:

	Camera* cam;

	/**
	 * the player
	 */
	GameGyrocopter* gyro;

	/**
	 * the level
	 */

	GameLevel* level;

	//GameHUD* hud;

	bool initialized;

public:

	GameStateIngame();

	/**
	 * init this gamestate:
	 * load all the needed objects: gyro, level, hud etc.
	 */
	void init();

	/** deinit this gamestate:
	 ...
	 */

	void deinit();

	void update();


		// check if ESC was pressed and if so tell the gamemangager to switch the gamestate to GameStateIngameOptionsMenu
	void keyDown(SDLKey key);


};



#endif
