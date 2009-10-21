#include "YGEGameState.h"
#include "YGELogger.h"

class GameStateX : YGEGame::YGEGameState {

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Draw a quad");
	}

};


class GameStateY : YGEGame::YGEGameState {

	virtual void update() {
		YGECore::YGELogger::getInstance()->log("Draw a tri");
	}

};