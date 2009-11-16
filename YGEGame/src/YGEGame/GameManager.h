/**
 * @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 *
 */

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "GameStateIngame.h"

/**
 * holds all GameState independant information
 * and all the GameStates as well. 
 * @todo make singleton
 */
class GameManager {
private:

	GameStateIngame* ingame;
	

	/**
	 * init the game engine
	 */
	void startEngine();


public:
	//
	void initAndStartGame(){


		//init the gamestates
		// @todo add GameStateIngame keydownlistenable

	}
	


};

#endif
