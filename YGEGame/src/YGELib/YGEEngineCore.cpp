#include "YGEEngineCore.h"
#include "YGESDLDisplay.h"


namespace YGECore {


	YGEEngineCore::YGEEngineCore(){
		gamestate = 0;
		shutdownNow = false;
		consoleEnabled = false;
	}

	YGEEngineCore::~YGEEngineCore(){
		SDL_Quit();
	}

	void YGEEngineCore::setGameState(YGEGame::YGEGameState* state){
		gamestate = state;

	}

	YGESDLInputManager* YGEEngineCore::getInputManager(){
		return input;
	}

	long long YGEEngineCore::getTimeSinceGameStarted(){
		return timeSinceGameStarted->getTime();
	}

	void YGEEngineCore::toggleConsole(){
		consoleEnabled = !consoleEnabled;
		SDL_EnableUNICODE(consoleEnabled);
	}

}