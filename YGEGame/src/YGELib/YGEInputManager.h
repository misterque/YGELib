#ifndef _YGE_SDL_INPUT_MANAGER_
#define _YGE_SDL_INPUT_MANAGER_

#include "YGEKeyDownListener.h"

#include <vector>

class YGEInputManager {
protected:
	std::vector<YGEKeyDownListener*> keydownlisteners;
public:
	virtual void update() = 0;
	virtual void init() = 0;

	void addKeyDownListener(YGEKeyDownListener* listener){
		keydownlisteners.push_back(listener);
	}
};


#endif