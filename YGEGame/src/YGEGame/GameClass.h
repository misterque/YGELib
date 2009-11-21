#include "YGEEngineCoreSingleThreaded.h"
#include "GameStates.h"
#include <iostream>

using namespace std;
using namespace YGECore;


class GameClass : public YGEKeyDownListener{
private:
		GameStateX* x;
	//	GameStateY* y;
	//	GameStateZ* z;
		YGEEngineCoreSingleThreaded core;

public:

	virtual void keyDown(SDLKey key){
		switch(key){
			case SDLK_1:
		core.setGameState(x);
				break;
			case SDLK_2:
	//	core.setGameState(y);
				break;
			case SDLK_3:
	//	core.setGameState(z);
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
	//	y = new GameStateY();
	//	z = new GameStateZ();

		core.setGameState(x);
		core.getInputManager()->addKeyDownListener(this);
	//	core.getInputManager()->addKeyDownListener(y);
	//	core.getInputManager()->addMouseMoveListener(y);

		core.run();
		core.shutdown();



	}


};