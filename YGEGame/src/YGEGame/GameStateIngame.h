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
#include "YGEKeyUpListener.h"

#include "GameManager.h"

#include "GameGyrocopter.h"
#include "GameBall.h"

#include "GameLevel.h"
#include "GameHUD.h"

#include "Camera.h"


class GameStateIngame  : public YGEGame::YGEGameState, public YGEKeyDownListener, public YGEKeyUpListener{
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

	GameHUD* hud;

	bool initialized;

	long timeSinceLastTimeUpdate;

	long long gameStartTime;

	std::vector<GameBall> balls;
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

	void update(long delta);


	void keyDown(SDLKey key);
	void keyUp(SDLKey key);


};



#endif
