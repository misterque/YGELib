/**
 * @file
 * @author Dirk Fortmeier
 * @date 16.11.2009
 *
 */

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_



#include "YGEGameState.h"
#include "YGEEngineCore.h"

#include <stack>
/**
 * holds all GameState independant information
 * and all the GameStates as well. 
 * @todo make singleton
 */
class GameManager : public YGEGame::YGEGameState{
private:

	GameManager();

	static GameManager* instance;


	YGECore::YGEEngineCore* engineCore;

	YGEGameState* ingame;
	YGEGameState* splashscreen;
	

	std::stack<YGEGameState*> gameStateStack;
	/**
	 * init the game engine
	 */
	void startEngine();


public:
	static GameManager* getInstance(){
		if(instance == NULL) {
			instance = new GameManager();
		}
		return instance;
	}
	//
	void initAndStartGame();
	
	void pushGameState(YGEGame::YGEGameState* gamestate);

	void popGameState();

	void update();

};

#endif
