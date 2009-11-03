#include "YGEEngineCore.h"
#include "GameStates.h"
#include <iostream>

using namespace std;
using namespace YGECore;


class GameClass : public YGEKeyDownListener{
private:
		GameStateX* x;
		GameStateY* y;
		YGEEngineCore core;

public:

	virtual void keyDown(SDLKey key){
		switch(key){
			case SDLK_x:
		core.setGameState(x);
				break;
			case SDLK_y:
		core.setGameState(y);
				break;
			case SDLK_ESCAPE:
				core.shutdown();
				break;
				break;
		}
		
	}

	void run(){

		


		core.init();

		x = new GameStateX();
		y = new GameStateY();

		core.setGameState(x);
		core.getInputManager()->addKeyDownListener(this);
		core.run();
		core.shutdown();



	}


};