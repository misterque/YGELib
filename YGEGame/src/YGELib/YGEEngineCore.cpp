#include "YGEEngineCore.h"
#include "YGEGraphicsCore.h"

#include <ode/ode.h>


namespace YGECore {


	YGEEngineCore::YGEEngineCore(){


		dInitODE();
	}

	YGEEngineCore::~YGEEngineCore(){
		SDL_Quit();
	}

	void YGEEngineCore::setGameState(YGEGame::YGEGameState* state){
		gamestate = state;

	}

	YGEInput::YGEInputManager* YGEEngineCore::getInputManager(){
		return input;
	}

	long long YGEEngineCore::getTimeSinceGameStarted(){
		return timeSinceGameStarted->getTime();
	}

	void YGEEngineCore::toggleConsole(){
		consoleEnabled = !consoleEnabled;
		SDL_EnableUNICODE(consoleEnabled);
	}

	void YGEEngineCore::processCommand(const char* command){
		if(std::string(command) == "quit") {
			shutdown();
		} else if (std::string(command) == "volumeUp") {
			int volume = YGEAudio::YGEAudioCore::getInstance()->getSoundVolume();
			volume += 10;
			YGEAudio::YGEAudioCore::getInstance()->setSoundVolume(volume);
		} else if (std::string(command) == "volumeDown") {
			int volume = YGEAudio::YGEAudioCore::getInstance()->getSoundVolume();
			volume -= 10;
			YGEAudio::YGEAudioCore::getInstance()->setSoundVolume(volume);
		} else if (std::string(command) == "togglefullscreen") {
			graphics->setFullscreen(!graphics->getFullscreen());
		} else {

			gamestate->processCommand(command);
		}

	}

}