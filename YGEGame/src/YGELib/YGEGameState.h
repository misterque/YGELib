#ifndef _YGE_GAME_STATE_
#define _YGE_GAME_STATE_


namespace YGEGame {
class YGEGameState {
	virtual void update() = 0;
	virtual void draw() = 0;
};
}


#endif