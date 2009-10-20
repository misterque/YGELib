#ifndef _YGE_SDL_INPUT_MANAGER_
#define _YGE_SDL_INPUT_MANAGER_


class YGEInputManager {
public:
	virtual void update() = 0;
	virtual void init() = 0;
};


#endif