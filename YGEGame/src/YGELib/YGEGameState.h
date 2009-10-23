#ifndef _YGE_GAME_STATE_
#define _YGE_GAME_STATE_

#include "YGEEngineCore.h"


namespace YGEGame {
class YGEGameState {
public:
	YGECore::YGEEngineCore s;
	virtual void update() = 0;
	virtual void draw(YGEEngineCore* core) = 0;
	
};
}


#endif