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

#include "Menu.h"


/**
* @brief gamestate used for game logic
*/
class GameStateIngame  : public YGEGame::YGEGameState, public YGEInput::YGEKeyDownListener, public YGEInput::YGEKeyUpListener{
private:
	/**
	* the Camera attached to the players gyrocopter
	*/
	Camera* cam;

	/**
	* the players gyrocopter
	*/
	GameGyrocopter* gyro;

	/**
	* the level
	*/

	GameLevel* level;

	/**
	* the hud
	*/
	GameHUD* hud;

	/**
	* if true, the gamestate considers itself as initialized, meaning all resources
	* have been loaded
	*/
	bool initialized;

	/**
	* time in microseconds since the last gamestate was updated the last time
	*/
	long timeSinceLastTimeUpdate;

	/**
	* time at which the game was started in milliseconds since ?
	*/
	long long gameStartTime;

	/**
	* time the game is running without beeing paused
	*/
	long long ingameTime;

	/**
	* vector of balls which have to be destroyed to finish the level
	*/
	std::vector<GameBall> balls;

	int ballsToDestroy;

	std::string levelFileName;

	bool levelCompleted;

	bool quitMenuIsShow;
public:

	/**
	* sets primitive variables
	*/
	GameStateIngame();

	/**
	* init this gamestate:
	* load all the needed objects: gyro, level, hud etc.
	*/
	void init();

	/**
	* deinit this gamestate:
	* unload unneeded resources
	* 
	*/
	void deinit();


	/**
	* update the gamestate
	*/
	virtual void update(long delta);


	
	virtual void keyDown(SDLKey key);
	virtual void keyUp(SDLKey key);

	virtual void processCommand(const char* command);

	/**
	 * @deprecated
	 */
	void setLevel(int level);
	
	/**
	 * after completing the level or crashing, the game should
	 * not immediatly stop. this is a couter counting down for this.
	 */
	double timeToQuit;

	/**
	 * @brief set the level to load
	 */ 
	void setLevelFileName(std::string filename){
		levelFileName = filename;
	}

	/**
	 * @deprecated
	 */
	bool getLevelCompleted();

};



#endif
