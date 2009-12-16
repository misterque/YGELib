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
#include <vector>

/**
 * holds all GameState independant information
 * and all the GameStates as well. 
 * @todo make singleton
 */
class GameManager : public YGEGame::YGEGameState, public YGEInput::YGEKeyDownListener, public YGEInput::YGEKeyUpListener{
private:

	GameManager();

	static GameManager* instance;


	YGECore::YGEEngineCore* engineCore;

	YGEGameState* ingame;
	YGEGameState* mainmenu;
	YGEGameState* splashscreen;
	

	std::stack<YGEGameState*> gameStateStack;

	std::vector<std::string> levelFiles;
	/**
	 * init the game engine
	 */
	void startEngine();

	void loadSaveGame();

	void loadLevelList();

	int reachedLevel;

	bool latest;


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

	void update(long delta);

	void startGame(std::string filename);
	void stopGame();

	YGECore::YGEEngineCore* getCore(){
		return engineCore;
	}

	virtual void processCommand(const char* command) {
	};

	std::vector<std::string>* getLevelList(){
		return &levelFiles;
	}

	int getReachedLevel(){
		return reachedLevel;
	}

	
	virtual void keyDown(SDLKey key);
	
	virtual void keyUp(SDLKey key);

};

#endif
